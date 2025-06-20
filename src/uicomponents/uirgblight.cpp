#include "uirgblight.hpp"
#include "logger.hpp"
#include "uicomponents/UIComponents.hpp"
#include "uicomponents/mdimap.hpp"
#include <src/core/lv_obj_pos.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_color.h>
#include <src/misc/lv_event.h>
#include <src/widgets/canvas/lv_canvas.h>
#include <src/widgets/image/lv_image.h>

extern const lv_image_dsc_t G_COLORTEMP24;
extern const lv_image_dsc_t G_COLORWHEEL24;
extern const lv_image_dsc_t G_BRIGHTNESS24;
extern const lv_image_dsc_t G_WHITE24;
// FIXME: we do a whole lot of json parsing in this file, that we should be doing somewhere else.

lv_obj_t* UIRGBLight::createImageButton(const void* _imgOrSymbol, lv_event_cb_t _callbackEvent, lv_event_code_t _eventCode, bool _toggle)
{
  lv_obj_t* btn = lv_button_create(btns);
  lv_obj_set_size(btn, 50, 40);
  lv_obj_set_style_pad_all(btn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_style(btn, &voorkant::lvgl::mdistyle, 0);

  if (_toggle) {
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  }
  lv_obj_add_event_cb(btn, _callbackEvent, _eventCode, reinterpret_cast<void*>(this));
  lv_obj_t* img_on_button = lv_image_create(btn);
  lv_image_set_src(img_on_button, _imgOrSymbol);
  lv_obj_set_align(img_on_button, LV_ALIGN_CENTER);
  return btn;
}

namespace
{
// assumes x,y are normalised to [-100..100]
lv_color_hsv_t nxy2hs(float _x, float _y)
{
  lv_color_hsv_t ret;

  float rangle = atan2f(_y, _x);
  int dangle = rangle * (180.0 / M_PI);

  ret.h = (dangle + 360) % 360; // normalize from [-180..180]-ish to [0..359]
  ret.s = static_cast<uint8_t>(sqrt(_x * _x + _y * _y));
  ret.v = 100;

  return ret;
}

// hs to xy in area, so usable for plotting
lv_point_t hs2xy(const lv_color_hsv_t& _hsv, const lv_area_t& _area)
{
  lv_point_t ret;

  float dangle = _hsv.h;
  float rangle = dangle / (180.0 / M_PI);
  cout << "rangle=" << rangle << ", cos=" << cos(rangle) << ", sin=" << sin(rangle);

  // [-1, -1] to [+1, +1]
  float x = cos(rangle);
  float y = sin(rangle);
  cout << ", x=" << x << ", y=" << y;

  // scale to saturation
  x *= (_hsv.s / 100.0);
  y *= (_hsv.s / 100.0);
  cout << ", x=" << x << ", y=" << y << endl;

  // [0, 0] to [2, 2]
  x += 1.0;
  y += 1.0;
  cout << ", x=" << x << ", y=" << y;

  // [0, 0] to [1, 1]
  x /= 2.0;
  y /= 2.0;
  cout << ", x=" << x << ", y=" << y;

  // [0, 0] to [xsize, ysize]
  // this puts us on the outer edge at the right angle
  x *= _area.x2;
  y *= _area.y2;
  cout << ", x=" << x << ", y=" << y << endl;

  ret.x = x;
  ret.y = y;

  return ret;
}

// input: point (0,0) is the top left corner of area
// output: point x,y are adjusted to [-100..100] in the area
lv_point_t normalisePointInArea(const lv_point_t& _point, const lv_area_t& _area)
{
  lv_point_t ret = _point;

  // move 0,0 to area center
  ret.x -= _area.x2 / 2;
  ret.y -= _area.y2 / 2;

  // multiply first - these are 32 bit ints, we have room but don't want to lose precision now
  ret.x *= 100;
  ret.y *= 100;

  // then normalise
  ret.x /= _area.x2 / 2;
  ret.y /= _area.y2 / 2;

  return ret;
}
}

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
  std::vector<std::string> supported_color_modes = attributes["supported_color_modes"].get<std::vector<string>>();

  // FIXME: we get all the supported color modes here, but we don't support all of them. Missing is RGBW, RGBWW and WHITE
  for (auto& mode : supported_color_modes) {
    std::cerr << "    supported color mode:" << mode << std::endl;
    std::transform(mode.begin(), mode.end(), mode.begin(), [](unsigned char _c) { return std::tolower(_c); }); // this needed?
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
    if (mode == "rgb" || mode == "rgbww" || mode == "xy") {
      showColorWheel = true;
      showBrightness = true;
      showColorTemp = true;
    }
    if (mode == "white") {
      showWhite = true;
    }
  }

  // We generate a UI based on 'supported_color_modes'. color_mode then tells us which mode to use. Color_mode should be in update()
  flowpanel = lv_obj_create(_parent);
  lv_obj_set_width(flowpanel, uiEntityWidth);
  lv_obj_set_height(flowpanel, LV_PCT(100));
  lv_obj_set_style_pad_all(flowpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(flowpanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(flowpanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

  lv_coord_t widthheight = uiEntityWidth - (lv_coord_t)50;

  lv_obj_t* label = createLabel(flowpanel, entity->name);
  lv_obj_set_width(label, LV_PCT(100));
  lv_obj_set_align(label, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  brightnessLabel = createLabel(flowpanel, "");
  lv_obj_set_width(brightnessLabel, LV_PCT(100));
  lv_obj_set_align(brightnessLabel, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(brightnessLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  tilecontainer = lv_tileview_create(flowpanel);
  lv_obj_add_event_cb(tilecontainer, UIRGBLight::changeTileCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(this));
  lv_obj_set_height(tilecontainer, 225);

  lv_coord_t sliderheight = 200;

  if (showBrightness) {
    lv_obj_t* brightness_tile = lv_tileview_add_tile(tilecontainer, 0, 0, LV_DIR_HOR);
    brightnessSlider = lv_slider_create(brightness_tile);
    lv_obj_set_height(brightnessSlider, sliderheight);
    lv_obj_set_width(brightnessSlider, 50);
    lv_obj_set_align(brightnessSlider, LV_ALIGN_CENTER);
    lv_slider_set_range(brightnessSlider, 0, 255);
    lv_obj_add_event_cb(brightnessSlider, UIRGBLight::slideBrightnessCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  }

  if (showColorWheel) {
    lv_obj_t* cw_tile = lv_tileview_add_tile(tilecontainer, 1, 0, LV_DIR_HOR);
    cwHSbuf.resize(sliderheight * sliderheight * 2); // FIXME 2 is only correct for 565 (which we are using now)
    cw = lv_canvas_create(cw_tile);
    lv_canvas_set_buffer(cw, cwHSbuf.data(), sliderheight, sliderheight, LV_COLOR_FORMAT_RGB565);
    lv_obj_set_size(cw, sliderheight, sliderheight);
    lv_obj_set_align(cw, LV_ALIGN_CENTER);
    // lv_image_set_src(cw, LV_SYMBOL_OK);
    lv_obj_set_size(cw, sliderheight, sliderheight);
    // lv_colorwheel_set_mode_fixed(cw, false);
    lv_canvas_fill_bg(cw, lv_color_hex(0xffffff), LV_OPA_MIN);
    // lv_canvas_set_px(cw, 25, 25, lv_palette_main(LV_PALETTE_BLUE), LV_OPA_50);
    lv_area_t area = {0, 0, sliderheight, sliderheight};

    for (int x = 0; x < sliderheight; x++) {
      for (int y = 0; y < sliderheight; y++) {
        lv_point_t xy = {x, y};
        lv_point_t nxy = normalisePointInArea(xy, area);
        lv_color_hsv_t color_hsv = nxy2hs(nxy.x, nxy.y);
        if (color_hsv.s > 100) {
          continue;
        }
        lv_color_t color_rgb = lv_color_hsv_to_rgb(color_hsv.h, color_hsv.s, color_hsv.v);
        lv_canvas_set_px(cw, x, y, color_rgb, LV_OPA_50);
      }
    }

    lv_obj_add_event_cb(cw_tile, UIRGBLight::changeColorWheelCB, LV_EVENT_CLICKED, reinterpret_cast<void*>(this));
    // lv_obj_set_style_arc_width(cw, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_color(cw, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    // lv_obj_set_style_opa(cw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_opa(cw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_width(cw, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_all(cw, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    cwCircle = lv_obj_create(cw);
    lv_obj_add_flag(cwCircle, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_set_size(cwCircle, 20, 20);
  }

  if (showColorTemp) {

    // TODO: RGBW and RGBWW have a few sliders underneath the color wheels
    // In white mode, the indicator on the color wheel should be removed. Not sure if we can do that.

    lv_obj_t* colortemp_tile = lv_tileview_add_tile(tilecontainer, 2, 0, LV_DIR_HOR);
    colortempSlider = lv_slider_create(colortemp_tile);
    lv_obj_set_height(colortempSlider, sliderheight);
    lv_obj_set_width(colortempSlider, 50);
    lv_obj_set_align(colortempSlider, LV_ALIGN_CENTER);
    int min_color_temp = getIntAttribute("min_color_temp_kelvin", 2000);
    int max_color_temp = getIntAttribute("max_color_temp_kelvin", 6500);
    lv_slider_set_range(colortempSlider, max_color_temp, min_color_temp);
    lv_obj_add_event_cb(colortempSlider, UIRGBLight::slideColorTempCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  }

  btns = lv_obj_create(flowpanel);
  lv_obj_remove_style_all(btns);
  lv_obj_set_width(btns, uiEntityWidth - 15);
  lv_obj_set_height(btns, 50);
  lv_obj_set_style_pad_all(btns, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(btns, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(btns, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(btns, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_remove_flag(btns, LV_OBJ_FLAG_SCROLLABLE);

  btnOnOff = createImageButton(voorkant::mdi::name2id("power-standby").data(), UIRGBLight::btnOnOffCB, LV_EVENT_VALUE_CHANGED, true);

  if (showBrightness) {
    btnBrightness = createImageButton(&G_BRIGHTNESS24, UIRGBLight::btnBrightnessCB, LV_EVENT_CLICKED);
    lv_obj_add_state(btnBrightness, LV_STATE_CHECKED);
  }

  if (showColorWheel) {
    btnColorWheel = createImageButton(&G_COLORWHEEL24, UIRGBLight::btnColorWheelCB, LV_EVENT_CLICKED);
  }
  if (showColorTemp) {
    btnColorTemp = createImageButton(&G_COLORTEMP24, UIRGBLight::btnColorTempCB, LV_EVENT_CLICKED);
  }

  update();
}

void UIRGBLight::update()
{
  auto state = entity->getJsonState();
  string colormode = getColorMode();
  // std::cerr << "COLOR MODE: " << colormode << std::endl;
  std::cerr << "UPDATED STATE FOR " << entity->name << ":" << state.dump(2) << std::endl;

  {
    std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
    if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
      auto attrs = state["attributes"];
      lv_obj_add_state(btnOnOff, LV_STATE_CHECKED);
      int brightness = attrs["brightness"].get<int>(); // brightness is NULL If the thing is off
      lv_slider_set_value(brightnessSlider, brightness, LV_ANIM_OFF);
      int brightness_percent = static_cast<int>(brightness / 2.55);
      std::string str_brightness_percent = std::to_string(brightness_percent);
      lv_label_set_text(brightnessLabel, (str_brightness_percent + "%").c_str());
      if (attrs.contains("hs_color")) {

        std::vector<int> vec_hs = attrs["hs_color"];

        lv_color_hsv_t hsv_val;
        hsv_val.h = vec_hs.at(0);
        hsv_val.s = vec_hs.at(1);
        hsv_val.v = brightness_percent;
        lv_area_t area;
        area.x2 = lv_obj_get_width(cw);
        area.y2 = lv_obj_get_height(cw);
        lv_point_t circlepos = hs2xy(hsv_val, area);
        cerr << "update circlepos.x=" << circlepos.x << ", .y=" << circlepos.y << endl;
        lv_obj_set_pos(cwCircle, circlepos.x - 10, circlepos.y - 10);

        // lv_colorwheel_set_hsv(cw, hsv_val);
      }
      if (attrs.contains("color_temp") && !attrs["color_temp"].is_null()) {
        int colortemp = state["attributes"]["color_temp_kelvin"].get<int>();
        std::cerr << "colormode == color temp and colortemp itself is: " << colortemp << std::endl;
        lv_slider_set_value(colortempSlider, colortemp, LV_ANIM_OFF);
      }
      // else if (colormode == "brightness") {
      //   std::cerr << "BRIGHTNESS" << std::endl;
      // }
      // else if (colormode == "white") {
      //   std::cerr << "WHITE" << std::endl;
      // }
      // else {
      //   std::cerr << " NO COLOR MODE " << colormode << " SO USING RGB" << std::endl;
      //   std::vector<int> vec_rgb = state["attributes"]["rgb_color"];

      //   int rgb[3];
      //   short cnt = 0;
      //   for (auto col : vec_rgb) {
      //     rgb[cnt] = col;
      //     cnt++;
      //   }
      //   // lv_colorwheel_set_rgb(cw, lv_color_make(rgb[0], rgb[1], rgb[2]));
      // }
    }
    else {
      lv_obj_remove_state(btnOnOff, LV_STATE_CHECKED);
      lv_slider_set_value(brightnessSlider, 0, LV_ANIM_OFF);
      lv_label_set_text(brightnessLabel, "Off");
    }
  }
}

void UIRGBLight::btnOnOffCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  UIRGBLight* rgb_light = (UIRGBLight*)(lv_event_get_user_data(_e));
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(rgb_light->entity);
    light.toggle({}); // FIXME: probably better to check state and send turn_off() or turn_on()
  }
};

// FIXME: woody stairing into the distance: "I see copy/paste code... copy/paste code everywhere..."
void UIRGBLight::btnBrightnessCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  UIRGBLight* rgb_light = (UIRGBLight*)(lv_event_get_user_data(_e));
  if (code == LV_EVENT_CLICKED) {
    lv_obj_set_tile_id(rgb_light->tilecontainer, 0, 0, LV_ANIM_OFF);
    if (rgb_light->showBrightness) {
      lv_obj_add_state(rgb_light->btnBrightness, LV_STATE_CHECKED);
    }
    if (rgb_light->showColorWheel) {
      lv_obj_remove_state(rgb_light->btnColorWheel, LV_STATE_CHECKED);
    }
    if (rgb_light->showColorTemp) {
      lv_obj_remove_state(rgb_light->btnColorTemp, LV_STATE_CHECKED);
    }
  }
};

void UIRGBLight::btnColorWheelCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  UIRGBLight* rgb_light = (UIRGBLight*)(lv_event_get_user_data(_e));
  if (code == LV_EVENT_CLICKED) {
    lv_obj_set_tile_id(rgb_light->tilecontainer, 1, 0, LV_ANIM_OFF);
    if (rgb_light->showBrightness) {
      lv_obj_remove_state(rgb_light->btnBrightness, LV_STATE_CHECKED);
    }
    if (rgb_light->showColorWheel) {
      lv_obj_add_state(rgb_light->btnColorWheel, LV_STATE_CHECKED);
    }
    if (rgb_light->showColorTemp) {
      lv_obj_remove_state(rgb_light->btnColorTemp, LV_STATE_CHECKED);
    }
  }
};

void UIRGBLight::btnColorTempCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  UIRGBLight* rgb_light = (UIRGBLight*)(lv_event_get_user_data(_e));
  if (code == LV_EVENT_CLICKED) {
    lv_obj_set_tile_id(rgb_light->tilecontainer, 2, 0, LV_ANIM_OFF);
    if (rgb_light->showBrightness) {
      lv_obj_remove_state(rgb_light->btnBrightness, LV_STATE_CHECKED);
    }
    if (rgb_light->showColorWheel) {
      lv_obj_remove_state(rgb_light->btnColorWheel, LV_STATE_CHECKED);
    }
    if (rgb_light->showColorTemp) {
      lv_obj_add_state(rgb_light->btnColorTemp, LV_STATE_CHECKED);
    }
  }
};

void UIRGBLight::slideBrightnessCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    auto slidervalue = lv_slider_get_value(lv_event_get_target_obj(_e));

    std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(lv_event_get_user_data(_e));
    HADomains::Light light(ent);

    if (slidervalue == 0) {
      light.turnOff({});
    }
    else {
      light.turnOn({.brightness = slidervalue});
    }
  }
};

void UIRGBLight::slideColorTempCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);
  if (code == LV_EVENT_VALUE_CHANGED) {
    auto slidervalue = lv_slider_get_value(lv_event_get_target_obj(_e));

    std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(lv_event_get_user_data(_e));
    HADomains::Light light(ent);

    light.turnOn({.kelvin = slidervalue});
  }
};

void UIRGBLight::changeTileCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  UIRGBLight* rgb_light = (UIRGBLight*)(lv_event_get_user_data(_e));
  if (code == LV_EVENT_VALUE_CHANGED) {
    // from https://forum.lvgl.io/t/get-current-active-tile-in-tileview/1644
    lv_obj_t* tile = lv_tileview_get_tile_act(rgb_light->tilecontainer);
    lv_coord_t tile_x = lv_obj_get_x(tile);
    int tile_nr = tile_x / 236;
    if (rgb_light->showBrightness) {
      lv_obj_remove_state(rgb_light->btnBrightness, LV_STATE_CHECKED);
    }
    if (rgb_light->showColorWheel) {
      lv_obj_remove_state(rgb_light->btnColorWheel, LV_STATE_CHECKED);
    }
    if (rgb_light->showColorTemp) {
      lv_obj_remove_state(rgb_light->btnColorTemp, LV_STATE_CHECKED);
    }
    switch (tile_nr) {
    case 0:
      lv_obj_add_state(rgb_light->btnBrightness, LV_STATE_CHECKED);
      break;
    case 1:
      lv_obj_add_state(rgb_light->btnColorWheel, LV_STATE_CHECKED);
      break;
    case 2:
      lv_obj_add_state(rgb_light->btnColorTemp, LV_STATE_CHECKED);
      break;
    default:
      break;
    }
  }
};

void UIRGBLight::changeColorWheelCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  g_log << Logger::Debug << "color wheel got event " << code << std::endl;

  if (code == LV_EVENT_CLICKED) {
    // lv_obj_t* colorwheel = lv_event_get_current_target_obj(_e);

    UIRGBLight* rgb_light = (UIRGBLight*)(lv_event_get_user_data(_e));

    g_log << Logger::Debug << "color wheel got click" << std::endl;
    lv_point_t point;
    lv_indev_get_point(lv_indev_active(), &point);
    g_log << Logger::Debug << "point(x=" << point.x << ", y=" << point.y << ")" << std::endl;
    lv_area_t area;
    lv_obj_get_coords(rgb_light->cw, &area);
    g_log << Logger::Debug << "area(";
    g_log << "x1,y1=" << area.x1 << "," << area.y1 << ", ";
    g_log << "x2,y2=" << area.x2 << "," << area.y2;
    g_log << ")" << std::endl;

    lv_area_t orig_area = area;

    point.x -= orig_area.x1;
    point.y -= orig_area.y1;

    // lv_point_t circlepos = point;

    area.x1 -= orig_area.x1;
    area.y1 -= orig_area.y1;
    area.x2 -= orig_area.x1;
    area.y2 -= orig_area.y1;

    // both point and area are now (0,0) based

    // g_log << Logger::Debug << "adjusted point(x=" << point.x << ", y=" << point.y << ")" << std::endl;
    // g_log << Logger::Debug << "adjusted area(";
    // g_log << "x1,y1=" << area.x1 << "," << area.y1 << ", ";
    // g_log << "x2,y2=" << area.x2 << "," << area.y2;
    // g_log << ")" << std::endl;

    lv_point_t nxy = normalisePointInArea(point, area);
    point.x -= area.x2 / 2;
    point.y -= area.y2 / 2;

    // g_log << Logger::Debug << "readjusted point(x=" << point.x << ", y=" << point.y << ")" << std::endl;

    // lv_color_t color_rgb = lv_colorwheel_get_rgb(colorwheel);
    // lv_color_hsv_t color_hsv = lv_colorwheel_get_hsv(colorwheel);
    // lv_color_hsv_t color_hsv = {hvalue, static_cast<uint8_t>(r), 100};
    lv_color_hsv_t color_hsv = nxy2hs(nxy.x, nxy.y);
    lv_color_t color_rgb = lv_color_hsv_to_rgb(color_hsv.h, color_hsv.s, color_hsv.v);

    std::cerr << "HSV (H/S/V):" << color_hsv.h << "/" << (uint16_t)color_hsv.s << "/" << (uint16_t)color_hsv.v << std::endl;
    std::cerr << "RGB (R/G/B):" << color_rgb.red << "/" << color_rgb.green << "/" << color_rgb.blue << std::endl;

    HADomains::Light light(rgb_light->entity);

    std::string colormode = rgb_light->getColorMode();

    std::cerr << "HA Entity color mode: " << colormode << std::endl;
    // if (colormode == "hs") {
    unsigned int hs[2];
    hs[0] = color_hsv.h;
    hs[1] = color_hsv.s;
    HADomains::Light::TurnOnArgs args;
    args.hs_color = hs;
    // args.brightness_pct = color_hsv.v;
    light.turnOn(args);
    // }
    // else {
    //   unsigned short rgb[3];
    //   rgb[0] = (unsigned short)color_rgb.red;
    //   rgb[1] = (unsigned short)color_rgb.green;
    //   rgb[2] = (unsigned short)color_rgb.blue;

    //   light.turnOn({.rgb_color = rgb});
    // }

    // FIXME: color_rgb (which is lv_color_t) depends on the LV_COLOR_DEPTH, and thus this code needs to handle the cast to uint_t

    // cerr<<"circlepos.x="<<circlepos.x<<", .y="<<circlepos.y<<endl;
    // lv_obj_set_pos(rgb_light->cwCircle, circlepos.x - 10, circlepos.y - 10);
    // lv_canvas_set_px(rgb_light->cw, circlepos.x, circlepos.y, color_rgb, LV_OPA_50);
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

int UIRGBLight::getIntAttribute(std::string _attributeName, int _defaultValue)
{
  if (_attributeName.empty()) {
    return _defaultValue;
  }
  auto state = entity->getJsonState();
  int ret_val = _defaultValue;
  if (state.contains("attributes")) {
    auto attrs = state["attributes"];
    if (attrs.contains(_attributeName) && !attrs[_attributeName].is_null()) {
      ret_val = attrs[_attributeName].get<int>();
    }
  }

  return ret_val;
}
