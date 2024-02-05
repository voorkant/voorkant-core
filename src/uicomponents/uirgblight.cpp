#include "uirgblight.hpp"

UIRGBLight::UIRGBLight(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{

  auto state = entity->getJsonState();
  std::cerr << "INITIAL STATE FOR " << _entity->name << ":" << state.dump(2) << std::endl;

  if (!state.contains("attributes")) {
    throw std::runtime_error("RGBLight can't operate with a state that has no attributes");
  }

  auto attributes = state["attributes"];
  if (!attributes.contains("supported_color_modes") || !attributes["supported_color_modes"].is_array()) {
    throw std::runtime_error("RGBLight really needs to know the supported_color_modes as an array");
  }
  std::vector<std::string> supportedColorModes = attributes["supported_color_modes"].get<std::vector<string>>();

  // Based on the supported_color_modes, we need to generate a UI that works for /all/ those modes.
  // color_temp = slider with color temp (min_color_temp_kelvin ->max_color_temp_kelvin)
  // hs = brightness and color wheel. According to the HA docs, this is in HS and not RGB, but setting RGB seems to work?
  // RGB = brighthess and color wheel. So, same as HS?
  // XY = brightness and color wheel. Docs say that you have to set XY - not sure if RGB will work?
  // White = brightness and color wheel (says the docs). Additional a WHITE value can be set
  // RGBW = brightness and color wheel, but color needs to be set using rgbw_color, which is rgb and white.
  // RGBWW, same as RGBW, but uses rgbww_color.
  // there is a colormode ONOFF, which is not listed as 'supported_color_modes', i guess because it has no color? again, our demo has no instance of this.

  // TODO Entrance Color + White Light causes a crash when we switch to White Light.
  for (const auto& str : supportedColorModes) {
    std::cerr << "\tCOLOR MODE:" << str << std::endl;
  }

  // TODO: we need to get 'supported_color_modes' to render the UI properly?
  flowpanel = lv_obj_create(_parent);
  lv_obj_set_width(flowpanel, uiEntityWidth);
  lv_obj_set_height(flowpanel, 450);
  lv_obj_set_style_pad_all(flowpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(flowpanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(flowpanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

  lv_coord_t widthheight = uiEntityWidth - 50;

  lv_obj_t* label = createLabel(flowpanel, entity->name);
  lv_obj_set_width(label, LV_PCT(100));
  lv_obj_set_align(label, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  brightnessLabel = createLabel(flowpanel, "");
  lv_obj_set_width(brightnessLabel, LV_PCT(100));
  lv_obj_set_align(brightnessLabel, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(brightnessLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  tilecontainer = lv_tileview_create(flowpanel);
  lv_obj_set_height(tilecontainer, uiEntityWidth);
  lv_obj_t* brightnessTile = lv_tileview_add_tile(tilecontainer, 0, 0, LV_DIR_HOR);
  brightnessSlider = lv_slider_create(brightnessTile);
  lv_obj_set_height(brightnessSlider, widthheight);
  lv_obj_set_width(brightnessSlider, 50);
  lv_obj_set_align(brightnessSlider, LV_ALIGN_CENTER);
  lv_slider_set_range(brightnessSlider, 0, 255);
  lv_obj_add_event_cb(brightnessSlider, UIRGBLight::brightness_slide_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));

  lv_obj_t* cwTile = lv_tileview_add_tile(tilecontainer, 1, 0, LV_DIR_HOR);
  cw = lv_colorwheel_create(cwTile, true);
  lv_obj_set_size(cw, widthheight, widthheight);
  lv_obj_set_align(cw, LV_ALIGN_CENTER);
  lv_colorwheel_set_mode_fixed(cw, false);
  lv_obj_add_event_cb(cw, UIRGBLight::colorwheel_move_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(this));
  lv_obj_set_style_arc_width(cw, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(cw, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_opa(cw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_opa(cw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(cw, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(cw, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
  // TODO: when RGBW and RGBWW we need to render sliders UNDER the color wheel

  // FIXME: surely there's a nicer way to check if a string exits in a vector?!
  for (const auto& mode : supportedColorModes) {
    if (mode == "color_temp") {
      lv_obj_t* colortempTile = lv_tileview_add_tile(tilecontainer, 2, 0, LV_DIR_HOR);
      colortempSlider = lv_slider_create(colortempTile);
      lv_obj_set_height(colortempSlider, widthheight);
      lv_obj_set_width(colortempSlider, 50);
      lv_obj_set_align(colortempSlider, LV_ALIGN_CENTER);
      int min_color_temp = state["attributes"]["min_color_temp_kelvin"];
      int max_color_temp = state["attributes"]["max_color_temp_kelvin"];
      // TODO: for whatever reason we can't get this to work the oposite way around, which is what HA does
      lv_slider_set_range(colortempSlider, min_color_temp, max_color_temp);
      lv_obj_add_event_cb(colortempSlider, UIRGBLight::colortemp_slide_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
    }
  }

  lv_obj_t* btns = lv_obj_create(flowpanel);
  lv_obj_remove_style_all(btns);
  lv_obj_set_width(btns, widthheight);
  lv_obj_set_height(btns, 50);
  lv_obj_set_style_pad_all(btns, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(btns, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(btns, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(btns, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

  btnOnOff = lv_btn_create(btns);
  // lv_obj_add_event_cb(btnOnOff, UIRGBLight::btnmatrix_event_cb, LV_EVENT_ALL, reinterpret_cast<void*>(this));
  lv_obj_set_width(btnOnOff, 50);
  lv_obj_t* imgBtnOnOff = lv_img_create(btnOnOff);
  lv_img_set_src(imgBtnOnOff, LV_SYMBOL_BARS);
  // lv_obj_set_align(btnOnOff, LV_ALIGN_CENTER);

  btnBrightness
    = lv_btn_create(btns);
  lv_obj_set_width(btnOnOff, 50);
  lv_obj_t* imgBrightness = lv_img_create(btnBrightness);
  lv_img_set_src(imgBrightness, LV_SYMBOL_SETTINGS);

  btnColorTemp = lv_btn_create(btns);
  lv_obj_set_width(btnColorTemp, 50);

  btnColorWheel = lv_btn_create(btns);
  lv_obj_set_width(btnColorWheel, 50);
  lv_obj_t* imgBtnColorWheel = lv_img_create(btnColorWheel);
  lv_img_set_src(imgBtnColorWheel, &color_wheel);

  uiupdate();
};

std::string UIRGBLight::getColorMode()
{
  auto state = entity->getJsonState();
  string colormode = "";
  if (state.contains("attributes")) {
    auto attrs = state["attributes"];
    if (attrs.contains("color_mode") && !attrs["color_mode"].is_null()) {
      colormode = attrs["color_mode"].get<string>();
    }
    else {
      std::cerr << "No colormode..." << std::endl;
    }
  }
  else {
    std::cerr << "No attributes...?!" << std::endl;
  }
  return colormode;
}

void UIRGBLight::uiupdate()
{
  auto state = entity->getJsonState();
  string colormode = getColorMode();
  std::cerr << "COLOR MODE: " << colormode << std::endl;

  // TODO: we should set the color of the brightness slider like HA does...

  std::cerr << "UPDATED STATE FOR " << entity->name << ":" << state.dump(2) << std::endl;
  if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
    lv_obj_add_state(btnOnOff, LV_STATE_CHECKED);
    int brightness = state["attributes"]["brightness"].get<int>(); // brightness is NULL If the thing is off
    lv_slider_set_value(brightnessSlider, brightness, LV_ANIM_OFF);
    int brightnessPercent = static_cast<int>(brightness / 2.55);
    std::string strBrightnessPercent = std::to_string(brightnessPercent);
    lv_label_set_text(brightnessLabel, (strBrightnessPercent + "%").c_str());
    if (colormode == "hs") {

      std::vector<int> vec_hs = state["attributes"]["hs_color"];

      lv_color_hsv_t hsvVal;
      hsvVal.h = vec_hs.at(0);
      hsvVal.s = vec_hs.at(1);
      hsvVal.v = brightnessPercent;
      lv_colorwheel_set_hsv(cw, hsvVal);
    }
    else if (colormode == "color_temp") {
      int colortemp = state["attributes"]["color_temp_kelvin"].get<int>();
      lv_slider_set_value(colortempSlider, colortemp, LV_ANIM_OFF);
    }
    else if (colormode == "white") {
      std::cerr << "WHITE" << std::endl;
    }
    else {

      std::vector<int> vec_rgb = state["attributes"]["rgb_color"];

      int rgb[3];
      short cnt = 0;
      for (auto col : vec_rgb) {
        rgb[cnt] = col;
        cnt++;
      }
      lv_colorwheel_set_rgb(cw, lv_color_make(rgb[0], rgb[1], rgb[2]));
    }
  }
  else {
    lv_obj_clear_state(btnOnOff, LV_STATE_CHECKED);
    lv_slider_set_value(brightnessSlider, 0, LV_ANIM_OFF);
    lv_label_set_text(brightnessLabel, "Off");
  }
}

void UIRGBLight::btnmatrix_event_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_VALUE_CHANGED) {

    UIRGBLight* ent = (UIRGBLight*)(e->user_data);
    auto x = lv_btnmatrix_get_selected_btn(e->target);
    lv_obj_t* tilething = ent->tilecontainer;

    lv_obj_set_tile_id(tilething, x, 0, LV_ANIM_OFF);
  }
}

void UIRGBLight::sw_toggle_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(ent);
    light.toggle({});
  }
};

void UIRGBLight::brightness_slide_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    auto slidervalue = lv_slider_get_value(e->target);

    std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
    HADomains::Light light(ent);

    if (slidervalue == 0) {
      light.turn_off({});
    }
    else {
      light.turn_on({.brightness = slidervalue});
    }
  }
};

void UIRGBLight::colortemp_slide_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    auto slidervalue = lv_slider_get_value(e->target);

    std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
    HADomains::Light light(ent);

    light.turn_on({.kelvin = slidervalue});
  }
};

void UIRGBLight::colorwheel_move_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_VALUE_CHANGED) {

    lv_obj_t* colorwheel = e->target;
    lv_color_t color_rgb = lv_colorwheel_get_rgb(colorwheel);
    lv_color_hsv_t color_hsv = lv_colorwheel_get_hsv(colorwheel);
    lv_colorwheel_mode_t mode = lv_colorwheel_get_color_mode(colorwheel);

    if (mode == LV_COLORWHEEL_MODE_HUE) {
      std::cerr << "COLOR MODE: LV_COLORWHEEL_MODE_HUE" << std::endl;
    }
    else if (mode == LV_COLORWHEEL_MODE_SATURATION) {
      std::cerr << "COLOR MODE: LV_COLORWHEEL_MODE_SATURATION" << std::endl;
    }
    else if (mode == LV_COLORWHEEL_MODE_VALUE) {

      std::cerr << "COLOR MODE: LV_COLORWHEEL_MODE_VALUE" << std::endl;
    }
    else {
      std::cerr << "COLOR MODE: NULL" << std::endl;
    }
    std::cerr << "HSV (H/S/V):" << color_hsv.h << "/" << (uint16_t)color_hsv.s << "/" << (uint16_t)color_hsv.v << std::endl;
    std::cerr << "RGB (R/G/B):" << color_rgb.ch.red << "/" << color_rgb.ch.green << "/" << color_rgb.ch.blue << std::endl;

    UIRGBLight* rgbLight = (UIRGBLight*)(e->user_data);
    HADomains::Light light(rgbLight->entity);

    std::string colormode = rgbLight->getColorMode();

    std::cerr << "HA Entity color mode: " << colormode << std::endl;
    if (colormode == "hs") {
      unsigned int hs[2];
      hs[0] = color_hsv.h;
      hs[1] = color_hsv.s;
      HADomains::Light::turn_on_args args;
      args.hs_color = hs;
      args.brightness_pct = color_hsv.v;
      light.turn_on(args);
    }
    else {
      unsigned short rgb[3];
      rgb[0] = (unsigned short)color_rgb.ch.red;
      rgb[1] = (unsigned short)color_rgb.ch.green;
      rgb[2] = (unsigned short)color_rgb.ch.blue;

      light.turn_on({.rgb_color = rgb});
    }

    // FIXME: color_rgb (which is lv_color_t) depends on the LV_COLOR_DEPTH, and thus this code needs to handle the cast to uint_t
  }
}