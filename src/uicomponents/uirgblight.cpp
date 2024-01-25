#include "uirgblight.hpp"

UIRGBLight::UIRGBLight(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  lv_obj_t* flowpanel = lv_obj_create(_parent);
  auto width = lv_obj_get_width(_parent);
  auto height = lv_obj_get_height(_parent);
  std::cerr << "Height/width: " << height << "/" << width << std::endl;

  lv_obj_set_size(flowpanel, height, width);
  lv_obj_align(flowpanel, LV_ALIGN_TOP_MID, 0, 5);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_COLUMN);

  lv_obj_t* cw = lv_colorwheel_create(flowpanel, true);
  lv_obj_set_size(cw, 200, width - 20);
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