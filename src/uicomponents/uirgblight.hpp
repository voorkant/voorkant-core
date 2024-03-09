#ifndef UIRGBLIGHT_HPP
#define UIRGBLIGHT_HPP
#include "UIComponents.hpp"
#include <src/core/lv_event.h>
#include <src/draw/lv_img_buf.h>

class UIRGBLight : public UIEntity
{
public:
  UIRGBLight(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

  void uiupdate() override;

private:
  // FIXME: we never free() the lv_obj_t*'s in code
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

  lv_obj_t* createImageButton(const void* _imgOrSymbol, lv_event_cb_t _callbackEvent, lv_event_code_t _eventCode, bool _toggle = false);
  static void btnOnOffCB(lv_event_t* _e);
  static void btnBrightnessCB(lv_event_t* _e);
  static void btnColorWheelCB(lv_event_t* _e);
  static void btnColorTempCB(lv_event_t* _e);

  static void slideBrightnessCB(lv_event_t* _e);
  static void slideColorTempCB(lv_event_t* _e);
  static void changeColorWheelCB(lv_event_t* _e);
  static void changeTileCB(lv_event_t* _e);

  std::string getColorMode();
  int getIntAttribute(std::string _attributeName, int _defaultValue);
};

#endif