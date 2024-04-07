#include "UICamera.hpp"

// FIXME: we do a whole lot of json parsing in this file, that we should be doing somewhere else.

UICamera::UICamera(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  auto state = entity->getJsonState();
  std::cerr << "INITIAL STATE FOR " << _entity->name << ":" << state.dump(2) << std::endl;

  if (!state.contains("attributes")) {
    throw std::runtime_error("Camera can't operate with a state that has no attributes");
  }

  auto attributes = state["attributes"];

  // We generate a UI based on 'supported_color_modes'. color_mode then tells us which mode to use. Color_mode should be in update()
  imgpanel = lv_img_create(_parent);
  lv_img_set_src(imgpanel, "A:test.png");
  // lv_obj_align(imgpanel, LV_ALIGN_LEFT_MID, 20, 0);

  update();
}

void UICamera::update()
{
  auto state = entity->getJsonState();
  std::cerr << "UPDATED STATE FOR " << entity->name << ":" << state.dump(2) << std::endl;

  {
    std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
  }
}
