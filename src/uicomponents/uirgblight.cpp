#include "uirgblight.hpp"
#include <stdexcept>

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

  bool showBrightness = false;
  bool showColorWheel = false;
  bool showColorTemp = false;
  bool showWhite = false;

  for (auto& mode : supportedColorModes) {
    std::cerr << "    supported color mode:" << mode << std::endl;
    std::transform(mode.begin(), mode.end(), mode.begin(), [](unsigned char c) { return std::tolower(c); }); // this needed?
    if (mode == "unknown") {
      throw std::runtime_error("support color mode is 'unknown', we really can't deal with that.");
    }
    if (mode == "brightness") {
      showBrightness = true;
    }
    if (mode == "color_temp") { // FIXME: HA docs say "and it's color temperature is present in the state".
      showBrightness = true;
      showColorTemp = true;
    }
    if (mode == "hs") {
      showColorWheel = true;
      showBrightness = true;
    }
    if (mode == "rgbw") {
      showColorWheel = true;
      showBrightness = true;
    }
    if (mode == "rgb" || mode == "rgbww") {
      showColorWheel = true;
      showBrightness = true;
      showColorTemp = true;
    }
    if (mode == "white") {
      showWhite = true;
    }
  }

  // We generate a UI based on 'supported_color_modes'. color_mode then tells us which mode to use. Color_mode should be in uiupdate()
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
  lv_obj_add_event_cb(tilecontainer, UIRGBLight::tilemove_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(this));
  lv_obj_set_height(tilecontainer, uiEntityWidth);

  if (showBrightness) {
    lv_obj_t* brightnessTile = lv_tileview_add_tile(tilecontainer, 0, 0, LV_DIR_HOR);
    brightnessSlider = lv_slider_create(brightnessTile);
    lv_obj_set_height(brightnessSlider, widthheight);
    lv_obj_set_width(brightnessSlider, 50);
    lv_obj_set_align(brightnessSlider, LV_ALIGN_CENTER);
    lv_slider_set_range(brightnessSlider, 0, 255);
    lv_obj_add_event_cb(brightnessSlider, UIRGBLight::brightness_slide_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  }

  if (showColorWheel) {
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
  }

  if (showColorTemp) {

    // TODO: RGBW and RGBWW have a few sliders underneath the color wheels
    // In white mode, the indicator on the color wheel should be removed. Not sure if we can do that.

    lv_obj_t* colortempTile = lv_tileview_add_tile(tilecontainer, 2, 0, LV_DIR_HOR);
    colortempSlider = lv_slider_create(colortempTile);
    lv_obj_set_height(colortempSlider, widthheight);
    lv_obj_set_width(colortempSlider, 50);
    lv_obj_set_align(colortempSlider, LV_ALIGN_CENTER);
    int min_color_temp = getIntAttribute("min_color_temp_kelvin", 2000);
    int max_color_temp = getIntAttribute("max_color_temp_kelvin", 6500);
    // FIRME: for whatever reason we can't get this to work the oposite way around, which is what HA does
    lv_slider_set_range(colortempSlider, min_color_temp, max_color_temp);
    lv_obj_add_event_cb(colortempSlider, UIRGBLight::colortemp_slide_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  }

  btns = lv_obj_create(flowpanel);
  lv_obj_remove_style_all(btns);
  lv_obj_set_width(btns, uiEntityWidth - 15);
  lv_obj_set_height(btns, 50);
  lv_obj_set_style_pad_all(btns, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(btns, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(btns, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(btns, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_clear_flag(btns, LV_OBJ_FLAG_SCROLLABLE);

  btnOnOff = lv_btn_create(btns);
  lv_obj_set_size(btnOnOff, 50, 40);
  lv_obj_add_flag(btnOnOff, LV_OBJ_FLAG_CHECKABLE);

  lv_obj_add_event_cb(btnOnOff, UIRGBLight::btnOnOff_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(this));
  lv_obj_t* imgBtnOnOff = lv_img_create(btnOnOff);
  lv_img_set_src(imgBtnOnOff, LV_SYMBOL_POWER);
  lv_obj_set_align(imgBtnOnOff, LV_ALIGN_CENTER);

  if (showBrightness) {
    btnBrightness = lv_btn_create(btns);
    lv_obj_set_size(btnBrightness, 50, 40);
    lv_obj_add_state(btnBrightness, LV_STATE_CHECKED);
    lv_obj_set_style_pad_all(btnBrightness, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btnBrightness, UIRGBLight::btnBrightness_cb, LV_EVENT_CLICKED, reinterpret_cast<void*>(this));
    lv_obj_t* imgBtnBrightness = lv_img_create(btnBrightness);
    lv_img_set_src(imgBtnBrightness, &brightness24);
    lv_obj_set_align(imgBtnBrightness, LV_ALIGN_CENTER);
  }

  if (showColorWheel) {
    btnColorWheel = lv_btn_create(btns);
    lv_obj_set_size(btnColorWheel, 50, 40);
    lv_obj_set_style_pad_all(btnColorWheel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btnColorWheel, UIRGBLight::btnColorWheel_cb, LV_EVENT_CLICKED, reinterpret_cast<void*>(this));
    lv_obj_t* imgBtnColorWheel = lv_img_create(btnColorWheel);
    lv_img_set_src(imgBtnColorWheel, &colorwheel24);
    lv_obj_set_align(imgBtnColorWheel, LV_ALIGN_CENTER);
  }
  if (showColorTemp) {
    btnColorTemp = lv_btn_create(btns);
    lv_obj_set_size(btnColorTemp, 50, 40);
    lv_obj_set_style_pad_all(btnColorTemp, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btnColorTemp, UIRGBLight::btnColorTemp_cb, LV_EVENT_CLICKED, reinterpret_cast<void*>(this));
    lv_obj_t* imgBtnColorTemp = lv_img_create(btnColorTemp);
    lv_img_set_src(imgBtnColorTemp, &colortemp24);
    lv_obj_set_align(imgBtnColorTemp, LV_ALIGN_CENTER);
  }

  uiupdate();
}

void UIRGBLight::uiupdate()
{
  auto state = entity->getJsonState();
  string colormode = getColorMode();
  std::cerr << "COLOR MODE: " << colormode << std::endl;
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
      std::cerr << "colormode == color temp and colortemp itself is: " << colortemp << std::endl;
      //   lv_slider_set_value(colortempSlider, colortemp, LV_ANIM_OFF);
    }
    else if (colormode == "brightness") {
      std::cerr << "BRIGHTNESS" << std::endl;
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

void UIRGBLight::btnOnOff_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  UIRGBLight* rgbLight = (UIRGBLight*)(e->user_data);
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(rgbLight->entity);
    light.toggle({}); // FIXME: probably better to check state and send turn_off() or turn_on()
  }
};

// FIXME: woody stairing into the distance: "I see copy/paste code... copy/paste code everywhere..."
void UIRGBLight::btnBrightness_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  UIRGBLight* rgbLight = (UIRGBLight*)(e->user_data);
  if (code == LV_EVENT_CLICKED) {
    lv_obj_set_tile_id(rgbLight->tilecontainer, 0, 0, LV_ANIM_OFF);
    lv_obj_add_state(rgbLight->btnBrightness, LV_STATE_CHECKED);
    lv_obj_clear_state(rgbLight->btnColorWheel, LV_STATE_CHECKED);
    lv_obj_clear_state(rgbLight->btnColorTemp, LV_STATE_CHECKED);
  }
};

void UIRGBLight::btnColorWheel_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  UIRGBLight* rgbLight = (UIRGBLight*)(e->user_data);
  if (code == LV_EVENT_CLICKED) {
    lv_obj_set_tile_id(rgbLight->tilecontainer, 1, 0, LV_ANIM_OFF);
    lv_obj_clear_state(rgbLight->btnBrightness, LV_STATE_CHECKED);
    lv_obj_add_state(rgbLight->btnColorWheel, LV_STATE_CHECKED);
    lv_obj_clear_state(rgbLight->btnColorTemp, LV_STATE_CHECKED);
  }
};

void UIRGBLight::btnColorTemp_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  UIRGBLight* rgbLight = (UIRGBLight*)(e->user_data);
  if (code == LV_EVENT_CLICKED) {
    lv_obj_set_tile_id(rgbLight->tilecontainer, 2, 0, LV_ANIM_OFF);
    lv_obj_clear_state(rgbLight->btnBrightness, LV_STATE_CHECKED);
    lv_obj_clear_state(rgbLight->btnColorWheel, LV_STATE_CHECKED);
    lv_obj_add_state(rgbLight->btnColorTemp, LV_STATE_CHECKED);
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

void UIRGBLight::tilemove_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  UIRGBLight* rgbLight = (UIRGBLight*)(e->user_data);
  if (code == LV_EVENT_VALUE_CHANGED) {
    // from https://forum.lvgl.io/t/get-current-active-tile-in-tileview/1644
    lv_obj_t* tile = lv_tileview_get_tile_act(rgbLight->tilecontainer);
    lv_coord_t tile_x = lv_obj_get_x(tile);
    int tileNr = tile_x / 236;
    lv_obj_clear_state(rgbLight->btnBrightness, LV_STATE_CHECKED);
    lv_obj_clear_state(rgbLight->btnColorWheel, LV_STATE_CHECKED);
    lv_obj_clear_state(rgbLight->btnColorTemp, LV_STATE_CHECKED);
    switch (tileNr) {
    case 0:
      lv_obj_add_state(rgbLight->btnBrightness, LV_STATE_CHECKED);
      break;
    case 1:
      lv_obj_add_state(rgbLight->btnColorWheel, LV_STATE_CHECKED);
      break;
    case 2:
      lv_obj_add_state(rgbLight->btnColorTemp, LV_STATE_CHECKED);
      break;
    default:
      break;
    }
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

int UIRGBLight::getIntAttribute(std::string attributeName, int defaultValue)
{
  if (attributeName.empty()) {
    return defaultValue;
  }
  auto state = entity->getJsonState();
  int retVal = defaultValue;
  if (state.contains("attributes")) {
    auto attrs = state["attributes"];
    if (attrs.contains(attributeName) && !attrs[attributeName].is_null()) {
      retVal = attrs[attributeName].get<int>();
    }
  }

  return retVal;
}