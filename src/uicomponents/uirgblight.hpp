#ifndef UIRGBLIGHT_HPP
#define UIRGBLIGHT_HPP
#include "UIComponents.hpp"

class UIRGBLight : public UIEntity
{
public:
  UIRGBLight(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

  void uiupdate() override;

private:
  lv_obj_t* sw;
  lv_obj_t* cw;
  lv_obj_t* brightnessSlider;
  static void sw_toggle_cb(lv_event_t* e);
  static void brightness_slide_cb(lv_event_t* e);
  static void colorwheel_move_cb(lv_event_t* e);
};

#endif