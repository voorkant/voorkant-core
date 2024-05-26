
#ifndef UICOMPONENTS_HPP
#define UICOMPONENTS_HPP

#include "HAEntity.hpp"
#include "Backend.hpp"
#include <lvgl.h>
#include <memory>
#include <src/core/lv_obj.h>
#include "Observer.hpp"
#include "generated/domains.hpp"

extern std::mutex g_lvgl_updatelock;

// FIXME: we never free() the lv_obj_t*'s in code
class UIComponent : public IObserver
{
public:
  UIComponent(lv_obj_t* _parent);
  ~UIComponent();

protected:
  lv_obj_t* createLabel(lv_obj_t* _parent, std::string _text);
  lv_obj_t* parentContainer;
  const lv_label_long_mode_t labelLongMode = LV_LABEL_LONG_SCROLL;
};

class UIEntity : public UIComponent
{
public:
  UIEntity(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);
  ~UIEntity();

protected:
  std::shared_ptr<HAEntity> entity;
  const lv_coord_t uiEntityWidth = (800 - (2 * 9)) / 3;
};

class UIButton : public UIEntity
{
public:
  UIButton(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);
  void update() override;

private:
  lv_obj_t* btn;
  static void btnPressCB(lv_event_t* _e);
};

class UISwitch : public UIEntity
{
public:
  UISwitch(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

  void update() override;

private:
  lv_obj_t* sw;
  static void swToggleCB(lv_event_t* _e);
};

class UIDummy : public UIEntity
{
public:
  UIDummy(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);
  void update() override;

private:
  lv_obj_t* extratext2;
};

#endif
