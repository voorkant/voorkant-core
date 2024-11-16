#include "UIComponents.hpp"
#include "logger.hpp"
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_event.h>
#include <src/widgets/canvas/lv_canvas.h>

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
  lv_obj_set_width(switchcontainer, uiEntityWidth);
  lv_obj_set_height(switchcontainer, LV_SIZE_CONTENT);
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

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(lv_event_get_user_data(_e));
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
  lv_obj_set_height(flowpanel, LV_SIZE_CONTENT);
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
  lv_obj_set_height(flowpanel, LV_SIZE_CONTENT);
  lv_obj_set_style_pad_all(flowpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(flowpanel, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(flowpanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  lv_obj_add_event_cb(flowpanel, UISensor::clickCB, LV_EVENT_CLICKED, reinterpret_cast<void*>(&entity));


  lv_obj_t* iconpart = lv_canvas_create(flowpanel);
#define MAAT 100
  lv_obj_set_width(iconpart, MAAT);
  lv_obj_set_height(iconpart, MAAT);
  lv_obj_set_style_pad_all(iconpart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(iconpart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  static auto canvas_buf = lv_draw_buf_create(MAAT, MAAT, LV_COLOR_FORMAT_ARGB8888, 0);
  static lv_layer_t svglayer;
  lv_image_cache_drop(canvas_buf);
  lv_canvas_set_draw_buf(iconpart, canvas_buf);
  lv_canvas_init_layer(iconpart, &svglayer);
  lv_canvas_fill_bg(iconpart, lv_color_make(0xff, 0xff, 0xff), 255);

  // static char svg_data[] = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
  //                          "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
  //                          "<svg width=\"100%\" height=\"100%\" viewBox=\"0 0 142 142\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xml:space=\"preserve\" xmlns:serif=\"http://www.serif.com/\" style=\"fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;\">"
  //                          "    <g>"
  //                          "        <g>"
  //                           "           <path d=\"M70.5,50C72.3,50 74.1,50.1 75.9,50.1L76,50.1C77.8,50.2 79.6,50.3 81.4,50.4C86.7,50.8 91.6,53.6 94.7,57.9C94.8,58.1 94.9,58.2 95,58.4C91.9,60.7 89.2,63.5 87,66.7C86.6,67.3 86.2,67.9 85.9,68.5C82.9,73.6 81.2,79.5 81.2,85.8C81.2,88.8 81.6,91.7 82.3,94.5C83.7,99.7 86.3,104.5 89.8,108.4C87.7,111.5 84.3,113.4 80.5,113.4C79.8,113.4 79.2,113.3 78.5,113.2L73.7,112.4L71.1,112L70.4,111.9L69.7,112L64.8,112.8L63.4,113L62.3,113.2L62.2,113.2C61.9,113.3 61.6,113.3 61.3,113.3L60.3,113.3C57.7,113.3 55.2,112.4 53.3,110.7C60.1,104.5 65.8,97.1 65.8,87.2C65.8,86.2 63.8,84.2 64.2,82.7C66.8,71.7 56.7,61.8 47.5,56.4C50.6,53 54.9,50.8 59.6,50.4C61.4,50.3 63.2,50.2 65,50.1L66.3,50.1C66.9,50.1 67.4,50.1 68,50L70.5,50M76.3,46L67.9,46C67.3,46 66.8,46 66.2,46.1L64.8,46.1C62.8,46.2 60.9,46.3 59.3,46.4C53.6,46.9 48.4,49.5 44.5,53.7L41.2,57.4L45.5,59.9C58.5,67.5 61.6,76.5 60.4,81.8C59.8,84.3 61,86.4 61.8,87.6C61.9,87.7 61.9,87.8 62,87.9C61.8,94.8 58.3,100.9 50.8,107.8L47.4,110.9L51,113.8C53.7,116 57.1,117.2 60.5,117.3L61.1,117.3L61,117.3L61.7,117.3C62.1,117.3 62.4,117.2 62.8,117.2L63,117.2L64.1,117L65.5,116.8L70.4,116L70.5,116L73.1,116.4L77.9,117.1C78.8,117.3 79.7,117.3 80.6,117.3C85.7,117.3 90.4,114.8 93.2,110.6L95,108L92.9,105.7C89.8,102.2 87.5,98 86.3,93.5C85.6,91 85.3,88.4 85.3,85.8C85.3,80.4 86.7,75.1 89.5,70.5C89.8,70 90.1,69.4 90.5,68.9C92.4,66.1 94.8,63.6 97.6,61.5L100.7,59.2L98.5,56L98.5,55.9C98.4,55.7 98.3,55.5 98.1,55.4C94.3,50.2 88.3,46.9 81.9,46.3C80.1,46.1 78.2,46 76.3,46Z\" style=\"fill:rgb(63,135,63);fill-rule:nonzero;\"/>"
  //                           "           <path d=\"M58.3,31.3C63.9,31.3 67.6,38.2 67.6,40.6L67.6,40.7C67.6,41.3 67.7,41.8 67.7,42.4C68.4,42.5 69,42.5 69.7,42.5C74.1,42.6 78.3,40.8 81.5,37.8C85,34.1 86.7,29.1 86.1,24C85.4,23.9 84.8,23.9 84.1,23.9C79.7,23.8 75.5,25.6 72.3,28.6C71,29.9 69.9,31.5 69.1,33.2C66.6,29.7 62.5,27.6 58.2,27.6C57.2,27.6 56.3,28.4 56.3,29.5C56.4,30.5 57.3,31.3 58.3,31.3ZM75,31.2C77,29.2 79.6,28 82.5,27.7C82.2,30.5 80.9,33.1 79,35.1C77,37.1 74.4,38.3 71.5,38.6C71.7,35.9 73,33.2 75,31.2Z\" style=\"fill:rgb(63,135,63);fill-rule:nonzero;\" fill=\"#00F\"/>"
  //                       "           </g>"
  //                              "</g>\n</svg>\n";

  // const char * svg_data = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
  //                            "<svg width=\"100%\" height=\"100%\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xml:space=\"preserve\" xmlns:serif=\"http://www.serif.com/\" style=\"fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;\">"
  //                            "<g fill=\"#FF0000\">"
  //                            // "<rect x=\"0\" y=\"0\" width=\"100\" height=\"100\"/>"
  //                            // "<circle fill=\"#00F\" cx=\"10\" cy=\"100\" r=\"50\"/>"
  //                            // "<ellipse fill=\"#00F\" cx=\"2\" cy=\"2\" rx=\"100\" ry=50/>"
  //                            "<path d=\"M70.5,50C72.3,50 74.1,50.1 75.9,50.1L76,50.1C77.8,50.2 79.6,50.3 81.4,50.4C86.7,50.8 91.6,53.6 94.7,57.9C94.8,58.1 94.9,58.2 95,58.4C91.9,60.7 89.2,63.5 87,66.7C86.6,67.3 86.2,67.9 85.9,68.5C82.9,73.6 81.2,79.5 81.2,85.8C81.2,88.8 81.6,91.7 82.3,94.5C83.7,99.7 86.3,104.5 89.8,108.4C87.7,111.5 84.3,113.4 80.5,113.4C79.8,113.4 79.2,113.3 78.5,113.2L73.7,112.4L71.1,112L70.4,111.9L69.7,112L64.8,112.8L63.4,113L62.3,113.2L62.2,113.2C61.9,113.3 61.6,113.3 61.3,113.3L60.3,113.3C57.7,113.3 55.2,112.4 53.3,110.7C60.1,104.5 65.8,97.1 65.8,87.2C65.8,86.2 63.8,84.2 64.2,82.7C66.8,71.7 56.7,61.8 47.5,56.4C50.6,53 54.9,50.8 59.6,50.4C61.4,50.3 63.2,50.2 65,50.1L66.3,50.1C66.9,50.1 67.4,50.1 68,50L70.5,50M76.3,46L67.9,46C67.3,46 66.8,46 66.2,46.1L64.8,46.1C62.8,46.2 60.9,46.3 59.3,46.4C53.6,46.9 48.4,49.5 44.5,53.7L41.2,57.4L45.5,59.9C58.5,67.5 61.6,76.5 60.4,81.8C59.8,84.3 61,86.4 61.8,87.6C61.9,87.7 61.9,87.8 62,87.9C61.8,94.8 58.3,100.9 50.8,107.8L47.4,110.9L51,113.8C53.7,116 57.1,117.2 60.5,117.3L61.1,117.3L61,117.3L61.7,117.3C62.1,117.3 62.4,117.2 62.8,117.2L63,117.2L64.1,117L65.5,116.8L70.4,116L70.5,116L73.1,116.4L77.9,117.1C78.8,117.3 79.7,117.3 80.6,117.3C85.7,117.3 90.4,114.8 93.2,110.6L95,108L92.9,105.7C89.8,102.2 87.5,98 86.3,93.5C85.6,91 85.3,88.4 85.3,85.8C85.3,80.4 86.7,75.1 89.5,70.5C89.8,70 90.1,69.4 90.5,68.9C92.4,66.1 94.8,63.6 97.6,61.5L100.7,59.2L98.5,56L98.5,55.9C98.4,55.7 98.3,55.5 98.1,55.4C94.3,50.2 88.3,46.9 81.9,46.3C80.1,46.1 78.2,46 76.3,46Z\" style=\"fill:rgb(63,135,63);fill-rule:nonzero;\"/>"
  //                           "           <path d=\"M58.3,31.3C63.9,31.3 67.6,38.2 67.6,40.6L67.6,40.7C67.6,41.3 67.7,41.8 67.7,42.4C68.4,42.5 69,42.5 69.7,42.5C74.1,42.6 78.3,40.8 81.5,37.8C85,34.1 86.7,29.1 86.1,24C85.4,23.9 84.8,23.9 84.1,23.9C79.7,23.8 75.5,25.6 72.3,28.6C71,29.9 69.9,31.5 69.1,33.2C66.6,29.7 62.5,27.6 58.2,27.6C57.2,27.6 56.3,28.4 56.3,29.5C56.4,30.5 57.3,31.3 58.3,31.3ZM75,31.2C77,29.2 79.6,28 82.5,27.7C82.2,30.5 80.9,33.1 79,35.1C77,37.1 74.4,38.3 71.5,38.6C71.7,35.9 73,33.2 75,31.2Z\" style=\"fill:rgb(63,135,63);fill-rule:nonzero;\" fill=\"#00F\"/>"
  //                            "</g></svg>";


  const char *svg_data =
"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"
"<svg width=\"100%\" height=\"100%\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xml:space=\"preserve\" xmlns:serif=\"http://www.serif.com/\" style=\"fill-rule:evenodd;clip-rule:evenodd;stroke-linejoin:round;stroke-miterlimit:2;\">"
    "<g>"
        "<g>"
            "<path d=\"M70.5,50C72.3,50 74.1,50.1 75.9,50.1L76,50.1C77.8,50.2 79.6,50.3 81.4,50.4C86.7,50.8 91.6,53.6 94.7,57.9C94.8,58.1 94.9,58.2 95,58.4C91.9,60.7 89.2,63.5 87,66.7C86.6,67.3 86.2,67.9 85.9,68.5C82.9,73.6 81.2,79.5 81.2,85.8C81.2,88.8 81.6,91.7 82.3,94.5C83.7,99.7 86.3,104.5 89.8,108.4C87.7,111.5 84.3,113.4 80.5,113.4C79.8,113.4 79.2,113.3 78.5,113.2L73.7,112.4L71.1,112L70.4,111.9L69.7,112L64.8,112.8L63.4,113L62.3,113.2L62.2,113.2C61.9,113.3 61.6,113.3 61.3,113.3L60.3,113.3C57.7,113.3 55.2,112.4 53.3,110.7C60.1,104.5 65.8,97.1 65.8,87.2C65.8,86.2 63.8,84.2 64.2,82.7C66.8,71.7 56.7,61.8 47.5,56.4C50.6,53 54.9,50.8 59.6,50.4C61.4,50.3 63.2,50.2 65,50.1L66.3,50.1C66.9,50.1 67.4,50.1 68,50L70.5,50M76.3,46L67.9,46C67.3,46 66.8,46 66.2,46.1L64.8,46.1C62.8,46.2 60.9,46.3 59.3,46.4C53.6,46.9 48.4,49.5 44.5,53.7L41.2,57.4L45.5,59.9C58.5,67.5 61.6,76.5 60.4,81.8C59.8,84.3 61,86.4 61.8,87.6C61.9,87.7 61.9,87.8 62,87.9C61.8,94.8 58.3,100.9 50.8,107.8L47.4,110.9L51,113.8C53.7,116 57.1,117.2 60.5,117.3L61.1,117.3L61,117.3L61.7,117.3C62.1,117.3 62.4,117.2 62.8,117.2L63,117.2L64.1,117L65.5,116.8L70.4,116L70.5,116L73.1,116.4L77.9,117.1C78.8,117.3 79.7,117.3 80.6,117.3C85.7,117.3 90.4,114.8 93.2,110.6L95,108L92.9,105.7C89.8,102.2 87.5,98 86.3,93.5C85.6,91 85.3,88.4 85.3,85.8C85.3,80.4 86.7,75.1 89.5,70.5C89.8,70 90.1,69.4 90.5,68.9C92.4,66.1 94.8,63.6 97.6,61.5L100.7,59.2L98.5,56L98.5,55.9C98.4,55.7 98.3,55.5 98.1,55.4C94.3,50.2 88.3,46.9 81.9,46.3C80.1,46.1 78.2,46 76.3,46Z\" style=\"fill:rgb(63,135,63);fill-rule:nonzero;\"/>"
            "<path d=\"M58.3,31.3C63.9,31.3 67.6,38.2 67.6,40.6L67.6,40.7C67.6,41.3 67.7,41.8 67.7,42.4C68.4,42.5 69,42.5 69.7,42.5C74.1,42.6 78.3,40.8 81.5,37.8C85,34.1 86.7,29.1 86.1,24C85.4,23.9 84.8,23.9 84.1,23.9C79.7,23.8 75.5,25.6 72.3,28.6C71,29.9 69.9,31.5 69.1,33.2C66.6,29.7 62.5,27.6 58.2,27.6C57.2,27.6 56.3,28.4 56.3,29.5C56.4,30.5 57.3,31.3 58.3,31.3ZM75,31.2C77,29.2 79.6,28 82.5,27.7C82.2,30.5 80.9,33.1 79,35.1C77,37.1 74.4,38.3 71.5,38.6C71.7,35.9 73,33.2 75,31.2Z\" style=\"fill:rgb(63,135,63);fill-rule:nonzero;\"/>"
        "</g>"
    "</g>"
"</svg>";


  lv_svg_node_t * svg = lv_svg_load_data(svg_data, lv_strlen(svg_data));
  lv_draw_svg(&svglayer, svg);
  lv_canvas_finish_layer(iconpart, &svglayer);
  lv_svg_node_delete(svg);

  lv_obj_t* textpart = lv_obj_create(flowpanel);
  lv_obj_set_width(textpart, uiEntityWidth - 55);
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

  const auto& services = _entity->getServices();
  for (const auto& service : services) {
    string txt = "Service: ";
    lv_obj_t* servicelabel = createLabel(textpart, txt.append(service->name));
    lv_obj_set_width(servicelabel, LV_PCT(100));
    lv_obj_set_align(servicelabel, LV_ALIGN_LEFT_MID);
  }

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
