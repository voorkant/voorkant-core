#pragma once
#include "UIComponents.hpp"
#include <src/core/lv_event.h>
#include <src/draw/lv_img_buf.h>

class UIApexCard : public UIEntity
{
public:
  UIApexCard(const std::string _panel, int _index, lv_obj_t* _parent);

  void uiupdate() override;

private:
  // FIXME: we never free() the lv_obj_t*'s in code
  lv_obj_t* chart;
  lv_obj_t* flowpanel;
  lv_chart_series_t* ser1;
};
