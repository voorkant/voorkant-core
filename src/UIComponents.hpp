
#ifndef UICOMPONENTS_HPP
#define UICOMPONENTS_HPP

#include "HAEntity.hpp"
#include "Backend.hpp"
#include <lvgl.h>
#include "Observer.hpp"
#include "generated/domains.hpp"

static void btn_press_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);

  std::shared_ptr<HAEntity> ent = *reinterpret_cast<std::shared_ptr<HAEntity>*>(e->user_data);
  if (code == LV_EVENT_VALUE_CHANGED) {
    HADomains::Light light(ent);
    light.toggle({});
  }
}

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
};

class UISwitch : public UIEntity
{
public:
  UISwitch(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

  void uiupdate() override;

private:
  lv_obj_t* sw;
};

#endif