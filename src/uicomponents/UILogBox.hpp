#pragma once

#include "uicomponents/UIComponents.hpp"
#include <src/core/lv_obj.h>

class UILogBox : public UIComponent
{
public:
  UILogBox(lv_obj_t* _parent);
  ~UILogBox();
  void updateIfNeeded();

protected:
  void update() override;
  lv_obj_t* log_box;
  bool dirty;
};
