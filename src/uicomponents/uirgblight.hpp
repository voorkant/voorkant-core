#ifndef UIRGBLIGHT_HPP
#define UIRGBLIGHT_HPP
#include "UIComponents.hpp"
#include <ostream>
#include <src/core/lv_event.h>
#include <src/core/lv_obj_pos.h>
#include <src/extra/widgets/colorwheel/lv_colorwheel.h>
#include <src/extra/widgets/tileview/lv_tileview.h>
#include <src/misc/lv_anim.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_color.h>
#include <src/widgets/lv_bar.h>
#include <src/widgets/lv_btnmatrix.h>
#include <src/widgets/lv_slider.h>
#include "generated/domains.hpp"
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style.h>
#include <src/extra/widgets/colorwheel/lv_colorwheel.h>
#include <src/font/lv_symbol_def.h>
#include <src/misc/lv_anim.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_txt.h>
#include <src/widgets/lv_bar.h>
#include <src/widgets/lv_btn.h>
#include <src/widgets/lv_img.h>
#include <src/widgets/lv_label.h>
#include <src/widgets/lv_slider.h>
#include <src/widgets/lv_img.h>

#include <stdexcept>
#include <vector>

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
  static void sw_toggle_cb(lv_event_t* e);
  static void brightness_slide_cb(lv_event_t* e);
  static void colortemp_slide_cb(lv_event_t* e);
  static void colorwheel_move_cb(lv_event_t* e);
  static void btnmatrix_event_cb(lv_event_t* e);

  std::string getColorMode();
};

#endif