#include "UIComponents.hpp"

UIEntity::~UIEntity()
{
  entity->detach((IObserver*)this);
};

lv_obj_t* UIEntity::createLabel(lv_obj_t* _parent, std::string text)
{
  lv_obj_t* label = lv_label_create(_parent);
  lv_label_set_text(label, text.c_str());
  lv_label_set_long_mode(label, labelLongMode);

  return label;
}

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
  lv_obj_set_size(btn, uiEntityWidth, 50);
  lv_obj_center(btn);
  lv_obj_set_style_pad_all(btn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(btn, UIButton::btn_press_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity)); // FIXME: put this magic (reinterpret_cast etc.) somewhere central

  lv_obj_t* label = createLabel(btn, _entity->name);
  lv_obj_set_width(label, LV_PCT(100));
  lv_obj_set_align(label, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
  uiupdate();
};

void UIButton::uiupdate()
{
  auto state = entity->getJsonState();

  {
    std::unique_lock<std::mutex> lvlock(G_LVGLUpdatelock);
    if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
      lv_obj_add_state(btn, LV_STATE_CHECKED);
    }
    else {
      lv_obj_clear_state(btn, LV_STATE_CHECKED);
    }
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
  lv_obj_set_width(switchcontainer, uiEntityWidth);
  lv_obj_set_height(switchcontainer, 50);
  lv_obj_clear_flag(switchcontainer, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_pad_all(switchcontainer, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

  sw = lv_switch_create(switchcontainer);
  lv_obj_set_width(sw, 50);
  lv_obj_add_event_cb(sw, UISwitch::sw_toggle_cb, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  lv_obj_set_align(sw, LV_ALIGN_RIGHT_MID);

  lv_obj_t* label = createLabel(switchcontainer, _entity->name);
  lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
  lv_obj_set_width(label, uiEntityWidth - 65); // 50 + padding == switch width

  uiupdate();
};

void UISwitch::uiupdate()
{
  auto state = entity->getJsonState();
  {
    std::unique_lock<std::mutex> lvlock(G_LVGLUpdatelock);
    if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
      lv_obj_add_state(sw, LV_STATE_CHECKED);
    }
    else {
      lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }
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
