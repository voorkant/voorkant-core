#include "UIComponents.hpp"
#include "mdimap.hpp"
#include "logger.hpp"
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_text.h>

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
  // lv_obj_set_size(btn, uiEntityWidth, 50);
  lv_obj_set_width(btn, LV_PCT(100));

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

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(lv_event_get_user_data(_e));
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
  // lv_obj_set_width(switchcontainer, uiEntityWidth);
  lv_obj_set_height(switchcontainer, LV_SIZE_CONTENT);
  lv_obj_set_width(switchcontainer, LV_PCT(100));
  lv_obj_remove_flag(switchcontainer, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_pad_all(switchcontainer, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

  sw = lv_switch_create(switchcontainer);
  lv_obj_set_width(sw, 50);
  lv_obj_add_event_cb(sw, UISwitch::swToggleCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  lv_obj_set_align(sw, LV_ALIGN_RIGHT_MID);

  lv_obj_t* label = createLabel(switchcontainer, _entity->name); // FIXME _entity->name ignores custom names set in dashboard. likely a problem in more places.
  lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
  // lv_obj_set_width(label, uiEntityWidth - 65); // 50 + padding == switch width

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

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(lv_event_get_user_data(_e));
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(ent); // FIXME: this is wrong for things like switch.ac, sends the wrong domain (light instead of switch)
    light.toggle({}); // FIXME: HAweb explicitly calls turn_on/turn_off instead of toggle
  }
};

// if _icon is passed, we got one from the dashboard, use that
string getIconFor(std::shared_ptr<HAEntity> _entity, std::string _icon) // for now, this function -always- returns something that starts with mdi:
{
  if (!_icon.empty()) {
    return _icon;
  }
  json state = _entity->getJsonState();

  // 1. see if the state simply contains an icon - user might have set it explicitly
  string icon = state["attributes"].value("icon", "");

  if (!icon.empty()) {
    return icon;
  }

  if (state["attributes"].count("entity_picture")) {
    // there is an icon, but it is not in a format we support yet (like SVG)
    return "mdi:border-none-variant";
  }
  // 2. see if we can find one for platform+translation key
  voorkant::lvgl::iconkey key = {_entity->platform, _entity->translation_key};
  if (voorkant::lvgl::iconmap.count(key)) {
    return voorkant::lvgl::iconmap.at(key);
  }

  // 3. maybe we can find one by domain plus device_class?
  auto& domain = _entity->domain;
  auto device_class = state["attributes"].value("device_class", "_");

  if (voorkant::lvgl::iconcomponentmap.count(domain)) {
    auto& domaindata = voorkant::lvgl::iconcomponentmap[domain];
    if (domaindata.count(device_class)) {
      if (domaindata[device_class].count("default")) { // FIXME: handle state-dependent variants too
        return domaindata[device_class]["default"];
      }
    }
  }

  return "mdi:border-none";
}

UISensor::UISensor(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent, std::string _icon) :
  UIEntity(_entity, _parent)
{
  lv_obj_t* flowpanel = lv_obj_create(_parent);
  // lv_obj_set_width(flowpanel, uiEntityWidth);
  lv_obj_set_width(flowpanel, LV_PCT(100));
  lv_obj_set_height(flowpanel, LV_SIZE_CONTENT);
  lv_obj_set_style_pad_all(flowpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(flowpanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(flowpanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  lv_obj_add_event_cb(flowpanel, UISensor::clickCB, LV_EVENT_CLICKED, reinterpret_cast<void*>(&entity));

  lv_obj_t* iconpart = lv_label_create(flowpanel);
  lv_obj_set_width(iconpart, 30);
  lv_obj_set_height(iconpart, LV_SIZE_CONTENT);
  lv_obj_set_style_pad_all(iconpart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(iconpart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  string icon = getIconFor(_entity, _icon);
  // cerr << "iconmap[" << _entity->platform << "," << _entity->translation_key << "]=" << voorkant::lvgl::iconmap[{_entity->platform, _entity->translation_key}] << endl;

  if (icon.substr(0, 4) == "mdi:") {
    icon = icon.substr(4);
  }
  else {
    icon = "help"; // as getIconFor currently promises something mdi:, we should never get here
  }

  lv_label_set_text(iconpart, voorkant::mdi::name2id(icon).data());
  lv_obj_add_style(iconpart, &voorkant::lvgl::mdistyle, 0);
  lv_obj_set_style_text_align(iconpart, LV_TEXT_ALIGN_CENTER, 0);

  lv_obj_t* textpart = lv_obj_create(flowpanel);
  // lv_obj_set_width(textpart, uiEntityWidth - 55);
  lv_obj_set_flex_grow(textpart, 1);
  lv_obj_set_height(textpart, LV_SIZE_CONTENT);
  lv_obj_set_style_pad_all(textpart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(textpart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_flex_flow(textpart, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(textpart, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

  lv_obj_t* label = createLabel(textpart, entity->name);
  lv_obj_set_width(label, LV_PCT(100));
  lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

  extratext2 = createLabel(textpart, "State:");
  lv_obj_set_width(extratext2, LV_PCT(100));
  lv_obj_set_align(extratext2, LV_ALIGN_RIGHT_MID);
  lv_obj_set_style_text_align(extratext2, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

  update();
};

void UISensor::update()
{
  std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);

  auto state = entity->getJsonState();
  g_log << Logger::Debug << "We received a UIupdate for " << entity->name << ":" << std::endl;
  // g_log << Logger::Debug << state.dump(2) << std::endl; // - commented because of #93
  string s = state["state"].get<string>() + " " + state["attributes"].value("unit_of_measurement", "");

  lv_label_set_text(extratext2, s.data());
};

void UISensor::clickCB(lv_event_t* _e)
{
  lv_event_code_t code = lv_event_get_code(_e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(lv_event_get_user_data(_e));
  if (code == LV_EVENT_CLICKED) {
    g_log << Logger::Debug << "got click on " << ent->fullname << endl;
  }
};
