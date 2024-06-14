#include "UIComponents.hpp"
#include "logger.hpp"
#include <src/core/lv_obj_pos.h>
#include <src/misc/lv_area.h>

lv_obj_t* UIComponent::createLabel(lv_obj_t* _parent, std::string _text)
{
  lv_obj_t* label = lv_label_create(_parent);
  lv_label_set_text(label, _text.c_str());
  lv_label_set_long_mode(label, labelLongMode);

  return label;
}

UIComponent::UIComponent(lv_obj_t* _parent) :
  parentContainer(_parent)
{
}
UIComponent::~UIComponent()
{
}

UIEntity::~UIEntity()
{
  entity->detach((IObserver*)this);
};

UIEntity::UIEntity(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIComponent(_parent)
{
  entity = _entity;

  // this `if` is here because uiapexcard does not know what to subscribe to before it has parsed its config.
  // perhaps even more importantly, once it does know, it might want to subscribe to multiple things
  // FIXME: so perhaps subscription should be handled in a more flexible way instead of right here in the constructor
  if (entity) {
    entity->attach((IObserver*)this);
  }
};

UIButton::UIButton(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  // FIXME: This code is duplicated in UISwitch, consider this after another few UIentities
  btn = lv_button_create(_parent);
  lv_obj_set_size(btn, uiEntityWidth, 50);
  lv_obj_center(btn);
  lv_obj_set_style_pad_all(btn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_add_event_cb(btn, UIButton::btnPressCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity)); // FIXME: put this magic (reinterpret_cast etc.) somewhere central

  lv_obj_t* label = createLabel(btn, _entity->name);
  lv_obj_set_width(label, LV_PCT(100));
  lv_obj_set_align(label, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
  update();
};

void UIButton::update()
{
  auto state = entity->getJsonState();

  {
    std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
    if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
      lv_obj_add_state(btn, LV_STATE_CHECKED);
    }
    else {
      lv_obj_remove_state(btn, LV_STATE_CHECKED);
    }
  }
};

void UIButton::btnPressCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(_e->user_data);
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
  lv_obj_remove_flag(switchcontainer, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_pad_all(switchcontainer, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

  sw = lv_switch_create(switchcontainer);
  lv_obj_set_width(sw, 50);
  lv_obj_add_event_cb(sw, UISwitch::swToggleCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  lv_obj_set_align(sw, LV_ALIGN_RIGHT_MID);

  lv_obj_t* label = createLabel(switchcontainer, _entity->name);
  lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
  lv_obj_set_width(label, uiEntityWidth - 65); // 50 + padding == switch width

  update();
};

void UISwitch::update()
{
  auto state = entity->getJsonState();
  {
    std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
    if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
      lv_obj_add_state(sw, LV_STATE_CHECKED);
    }
    else {
      lv_obj_remove_state(sw, LV_STATE_CHECKED);
    }
  }
};

void UISwitch::swToggleCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(_e->user_data);
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(ent);
    light.toggle({});
  }
};

UIDummy::UIDummy(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  lv_obj_t* flowpanel = lv_obj_create(_parent);
  lv_obj_set_width(flowpanel, uiEntityWidth);
  lv_obj_set_height(flowpanel, 80);
  lv_obj_set_style_pad_all(flowpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(flowpanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(flowpanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

  lv_obj_t* label = createLabel(flowpanel, entity->name);
  lv_obj_set_width(label, LV_PCT(100));
  lv_obj_set_align(label, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  string text = "Domain: ";
  lv_obj_t* extratext = createLabel(flowpanel, text.append(_entity->domain));
  lv_obj_set_width(extratext, LV_PCT(100));
  lv_obj_set_align(extratext, LV_ALIGN_LEFT_MID);

  extratext2 = createLabel(flowpanel, "State:");
  lv_obj_set_width(extratext2, LV_PCT(100));
  lv_obj_set_align(extratext2, LV_ALIGN_LEFT_MID);

  const auto& services = _entity->getServices();
  for (const auto& service : services) {
    string txt = "Service: ";
    lv_obj_t* servicelabel = createLabel(flowpanel, txt.append(service->name));
    lv_obj_set_width(servicelabel, LV_PCT(100));
    lv_obj_set_align(servicelabel, LV_ALIGN_LEFT_MID);
  }

  update();
};

void UIDummy::update()
{
  auto state = entity->getJsonState();
  g_log << Logger::Debug << "We received a UIupdate for " << entity->name << ":" << std::endl;
  // g_log << Logger::Debug << state.dump(2) << std::endl; // - commented because of #93
  string s = "State: " + state["state"].get<string>() + " " + state["attributes"].value("unit_of_measurement", "");

  {
    std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
    lv_label_set_text(extratext2, s.data());
  }
};

UISensor::UISensor(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  lv_obj_t* flowpanel = lv_obj_create(_parent);
  lv_obj_set_width(flowpanel, uiEntityWidth);
  lv_obj_set_height(flowpanel, 60);
  lv_obj_set_style_pad_all(flowpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(flowpanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(flowpanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  lv_obj_add_event_cb(flowpanel, UISensor::clickCB, LV_EVENT_CLICKED, reinterpret_cast<void*>(&entity));

  lv_obj_t* label = createLabel(flowpanel, entity->name);
  lv_obj_set_width(label, LV_PCT(100));
  lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

  extratext2 = createLabel(flowpanel, "State:");
  lv_obj_set_width(extratext2, LV_PCT(100));
  lv_obj_set_align(extratext2, LV_ALIGN_RIGHT_MID);
  lv_obj_set_style_text_align(extratext2, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

  const auto& services = _entity->getServices();
  for (const auto& service : services) {
    string txt = "Service: ";
    lv_obj_t* servicelabel = createLabel(flowpanel, txt.append(service->name));
    lv_obj_set_width(servicelabel, LV_PCT(100));
    lv_obj_set_align(servicelabel, LV_ALIGN_LEFT_MID);
  }

  update();
};

void UISensor::update()
{
  auto state = entity->getJsonState();
  g_log << Logger::Debug << "We received a UIupdate for " << entity->name << ":" << std::endl;
  // g_log << Logger::Debug << state.dump(2) << std::endl; // - commented because of #93
  string s = state["state"].get<string>() + " " + state["attributes"].value("unit_of_measurement", "");

  lv_label_set_text(extratext2, s.data());
};

void UISensor::clickCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(_e->user_data);
  if (code == LV_EVENT_CLICKED) {
    g_log << Logger::Debug << "got click on " << ent->fullname << endl;
  }
};
