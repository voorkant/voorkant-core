
#ifndef UICOMPONENTS_HPP
#define UICOMPONENTS_HPP

#include "HAEntity.hpp"
#include "Backend.hpp"
#include <lvgl.h>
#include "generated/domains.hpp"

class UIEntity
{
public:
  UIEntity(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent)
  {
    parentContainer = _parent;
    entity = _entity;
  }

protected:
  std::shared_ptr<HAEntity> entity;
  lv_obj_t* parentContainer;
};

class UISwitch : UIEntity
{
public:
  UISwitch(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
    UIEntity(_entity, _parent)
  {
    // START BUTTON EXAMPLE
    lv_obj_t* btn = lv_btn_create(_parent); /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10); /*Set its position*/
    lv_obj_set_size(btn, 240, 50); /*Set its size*/
    lv_obj_add_event_cb(btn, UISwitch::btn_press_cb, LV_EVENT_ALL, reinterpret_cast<void*>(&_entity)); /*Assign a callback to the button*/

    lv_obj_t* label = lv_label_create(btn); /*Add a label to the button*/
    lv_label_set_text(label, _entity->name.c_str()); /*Set the labels text*/
    lv_obj_center(label);
  }

private:
  static void btn_press_cb(lv_event_t* e)
  {
    lv_event_code_t code = lv_event_get_code(e);

    std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
    if (code == LV_EVENT_CLICKED) {
      HADomains::Light light(ent);
      light.toggle({});
    }
  }
};

#endif