#include "uirgblight.hpp"

UIRGBLight::UIRGBLight(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  lv_obj_t* flowpanel = lv_obj_create(_parent);
  lv_obj_set_width(flowpanel, uiEntityWidth);
  lv_obj_set_height(flowpanel, 400);
  lv_obj_set_style_pad_all(flowpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(flowpanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(flowpanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

  cw = lv_colorwheel_create(flowpanel, true);
  auto widthheight = uiEntityWidth - 50;
  lv_obj_set_size(cw, widthheight, widthheight);
  lv_obj_set_align(cw, LV_ALIGN_CENTER);
  lv_obj_add_event_cb(cw, UIRGBLight::colorwheel_move_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));

  sw = lv_switch_create(flowpanel);
  lv_obj_set_width(sw, 50);
  lv_obj_set_align(sw, LV_ALIGN_CENTER);
  lv_obj_add_event_cb(sw, UIRGBLight::sw_toggle_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));

  brightnessSlider = lv_slider_create(flowpanel);
  lv_obj_set_width(brightnessSlider, widthheight);
  lv_obj_set_align(brightnessSlider, LV_ALIGN_CENTER);
  lv_slider_set_range(brightnessSlider, 0, 255);
  lv_obj_add_event_cb(brightnessSlider, UIRGBLight::brightness_slide_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));

  uiupdate();
};

void UIRGBLight::uiupdate()
{
  auto state = entity->getJsonState();
  std::cerr << "UIUPDATE-STATE:" << state.dump(2) << std::endl;
  if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
    lv_obj_add_state(sw, LV_STATE_CHECKED);
    int brightness = state["attributes"]["brightness"].get<int>(); // brightness is NULL If the thing is off
    lv_slider_set_value(brightnessSlider, brightness, LV_ANIM_OFF);

    std::vector<int> vec_rgb = state["attributes"]["rgb_color"];

    int rgb[3];
    short cnt = 0;
    for (auto col : vec_rgb) {
      rgb[cnt] = col;
      cnt++;
    }
    lv_colorwheel_set_rgb(cw, lv_color_make(rgb[0], rgb[1], rgb[2]));
  }
  else {
    lv_obj_clear_state(sw, LV_STATE_CHECKED);
    lv_slider_set_value(brightnessSlider, 0, LV_ANIM_OFF);
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

void UIRGBLight::colorwheel_move_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_VALUE_CHANGED) {

    lv_obj_t* colorwheel = e->target;
    lv_color_t color = lv_colorwheel_get_rgb(e->target);

    std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
    HADomains::Light light(ent);

    uint8_t rgb[3];
    rgb[0] = color.ch.red;
    rgb[1] = color.ch.green;
    rgb[2] = color.ch.blue;

    light.turn_on({.rgb_color = rgb});
  }
}