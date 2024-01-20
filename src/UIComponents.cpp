#include "UIComponents.hpp"

UIEntity::~UIEntity()
{
  entity->detach((IObserver*)this);
};

UIEntity::UIEntity(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent)
{
  parentContainer = _parent;
  entity = _entity;
  entity->attach((IObserver*)this);
};

UIButton::UIButton(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  // START BUTTON EXAMPLE
  btn = lv_btn_create(_parent); /*Add a button the current screen*/
  lv_obj_set_size(btn, 240, 50);
  lv_obj_center(btn);
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(btn, btn_press_cb, LV_EVENT_ALL, reinterpret_cast<void*>(&entity)); /*Assign a callback to the button*/

  lv_obj_t* label = lv_label_create(btn); /*Add a label to the button*/
  lv_label_set_text(label, _entity->name.c_str()); /*Set the labels text*/
  lv_obj_center(label);
  uiupdate();
};

void UIButton::uiupdate()
{
  auto state = entity->getJsonState();
  if (state["state"] == "on") {
    lv_obj_add_state(btn, LV_STATE_CHECKED);
  }
  else {
    lv_obj_clear_state(btn, LV_STATE_CHECKED);
  }
};

UISwitch::UISwitch(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  // START BUTTON EXAMPLE
  lv_obj_t* switchcontainer = lv_obj_create(_parent);
  lv_obj_set_size(switchcontainer, 240, 50);
  lv_obj_center(switchcontainer);

  sw = lv_switch_create(switchcontainer); /*Add a button the current screen*/
  lv_obj_add_event_cb(sw, btn_press_cb, LV_EVENT_ALL, reinterpret_cast<void*>(&entity)); /*Assign a callback to the button*/
  lv_obj_add_flag(sw, LV_OBJ_FLAG_EVENT_BUBBLE);
  lv_obj_set_align(sw, LV_ALIGN_RIGHT_MID);

  lv_obj_t* label = lv_label_create(switchcontainer); /*Add a label to the button*/
  lv_label_set_text(label, _entity->name.c_str()); /*Set the labels text*/
  uiupdate();
};

void UISwitch::uiupdate()
{
  auto state = entity->getJsonState();
  if (state["state"] == "on") {
    lv_obj_add_state(sw, LV_STATE_CHECKED);
  }
  else {
    lv_obj_clear_state(sw, LV_STATE_CHECKED);
  }
};
