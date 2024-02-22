#ifndef UIRGBLIGHT_HPP
#define UIRGBLIGHT_HPP
#include "UIComponents.hpp"
#include "imgs/colorwheel24.cpp"
#include "imgs/colortemp24.cpp"
#include "imgs/brightness24.cpp"
#include "imgs/white24.cpp"
#include <iostream>
#include <cctype>
#include <src/core/lv_event.h>
#include <src/draw/lv_img_buf.h>

LV_IMG_DECLARE(colorwheel24);
LV_IMG_DECLARE(colortemp24);
LV_IMG_DECLARE(brightness24);
LV_IMG_DECLARE(white24);

class UIRGBLight : public UIEntity
{
public:
  UIRGBLight(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

  void uiupdate() override;

private:
  lv_obj_t* btnOnOff;
  lv_obj_t* btnBrightness;
  lv_obj_t* btnColorWheel;
  lv_obj_t* btnColorTemp;
  lv_obj_t* btnWhite;
  lv_obj_t* cw;
  lv_obj_t* brightnessSlider;
  lv_obj_t* colortempSlider;
  lv_obj_t* tilecontainer;
  lv_obj_t* flowpanel;
  lv_obj_t* brightnessLabel;
  lv_obj_t* btns;
  // lv_obj_t* imgBtnOnOff;
  // lv_obj_t* imgBtnBrightness;
  // lv_obj_t* imgBtnColorTemp;
  // lv_obj_t* imgBtnColorWheel;
  bool showBrightness = false;
  bool showColorWheel = false;
  bool showColorTemp = false;
  bool showWhite = false;

  lv_obj_t* createImageButton(const void* imgOrSymbol, lv_event_cb_t callbackEvent, lv_event_code_t eventCode, bool toggle = false);
  static void btnOnOff_cb(lv_event_t* e);
  static void btnBrightness_cb(lv_event_t* e);
  static void btnColorWheel_cb(lv_event_t* e);
  static void btnColorTemp_cb(lv_event_t* e);

  static void brightness_slide_cb(lv_event_t* e);
  static void colortemp_slide_cb(lv_event_t* e);
  static void colorwheel_move_cb(lv_event_t* e);
  static void btnmatrix_event_cb(lv_event_t* e);
  static void tilemove_cb(lv_event_t* e);

  std::string getColorMode();
  int getIntAttribute(std::string attributeName, int defaultValue);
};

#endif