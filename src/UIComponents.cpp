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
  // FIXME: This code is duplicated in UISwitch, consider this after another few UIentities
  btn = lv_btn_create(_parent);
  lv_obj_set_size(btn, 240, 50);
  lv_obj_center(btn);
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(btn, UIButton::btn_press_cb, LV_EVENT_ALL, reinterpret_cast<void*>(&entity));
  lv_obj_t* label = lv_label_create(btn);
  lv_label_set_text(label, _entity->name.c_str());
  lv_obj_center(label);
  uiupdate();
};

void UIButton::uiupdate()
{
  auto state = entity->getJsonState();
  if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
    lv_obj_add_state(btn, LV_STATE_CHECKED);
  }
  else {
    lv_obj_clear_state(btn, LV_STATE_CHECKED);
  }
};

void UIButton::btn_press_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(ent);
    light.toggle({});
  }
};

UISwitch::UISwitch(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  // This code is duplicated in UISwitch, consider this after another few UIentities
  lv_obj_t* switchcontainer = lv_obj_create(_parent);
  lv_obj_set_size(switchcontainer, 240, 50);
  lv_obj_center(switchcontainer);

  sw = lv_switch_create(switchcontainer);
  lv_obj_add_event_cb(sw, UISwitch::sw_toggle_cb, LV_EVENT_ALL, reinterpret_cast<void*>(&entity));
  lv_obj_set_align(sw, LV_ALIGN_RIGHT_MID);

  lv_obj_t* label = lv_label_create(switchcontainer);
  lv_label_set_text(label, _entity->name.c_str());
  uiupdate();
};

void UISwitch::uiupdate()
{
  auto state = entity->getJsonState();
  if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
    lv_obj_add_state(sw, LV_STATE_CHECKED);
  }
  else {
    lv_obj_clear_state(sw, LV_STATE_CHECKED);
  }
};

void UISwitch::sw_toggle_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(ent);
    light.toggle({});
  }
};
