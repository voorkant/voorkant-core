
#ifndef UICOMPONENTS_HPP
#define UICOMPONENTS_HPP

#include "HAEntity.hpp"
#include <lvgl.h>

class UIEntity
{
public:
  UIEntity(HAEntity _entity, lv_obj_t* _parent)
  {
    parentContainer = _parent;
    entity = _entity;
  }

private:
  HAEntity entity;
  lv_obj_t* parentContainer;
};

class UISwitch : UIEntity
{
  UISwitch(HAEntity _entity, lv_obj_t* _parent) :
    UIEntity(_entity, _parent)
  {
    lv_obj_t* btn = lv_btn_create(parentContainer);
    lv_obj_set_size(btn, 100, LV_PCT(100));

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text_fmt(label, "On/Off");
    lv_obj_center(label);
  }
};

#endif