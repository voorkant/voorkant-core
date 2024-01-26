#include "uirgblight.hpp"

UIRGBLight::UIRGBLight(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  lv_obj_t* flowpanel = lv_obj_create(_parent);
  lv_obj_set_width(flowpanel, uiEntityWidth);
  lv_obj_set_height(flowpanel, 100);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_COLUMN);

  lv_obj_t* cw = lv_colorwheel_create(flowpanel, true);
  // lv_obj_set_width(cw, lv_pct(50));
  // lv_obj_set_height(cw, lv_pct(50));
  lv_obj_center(cw);

  uiupdate();
};

void UIRGBLight::uiupdate()
{
  //       auto state = entity->getJsonState();
  //   if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
  //     lv_obj_add_state(btn, LV_STATE_CHECKED);
  //   }
  //   else {
  //     lv_obj_clear_state(btn, LV_STATE_CHECKED);
  //   }
}