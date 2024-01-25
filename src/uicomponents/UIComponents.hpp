
#ifndef UICOMPONENTS_HPP
#define UICOMPONENTS_HPP

#include "HAEntity.hpp"
#include "Backend.hpp"
#include <lvgl.h>
#include "Observer.hpp"
#include "generated/domains.hpp"

class UIEntity : public IObserver
{
public:
  ~UIEntity();
  UIEntity(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

protected:
  std::shared_ptr<HAEntity> entity;
  lv_obj_t* parentContainer;
};

class UIButton : public UIEntity
{
public:
  UIButton(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);
  void uiupdate() override;

private:
  lv_obj_t* btn;
  static void btn_press_cb(lv_event_t* e);
};

class UISwitch : public UIEntity
{
public:
  UISwitch(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

  void uiupdate() override;

private:
  lv_obj_t* sw;
  static void sw_toggle_cb(lv_event_t* e);
};

#endif