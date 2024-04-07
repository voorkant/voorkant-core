#pragma once
#include "UIComponents.hpp"
#include <src/core/lv_event.h>
#include <src/draw/lv_img_buf.h>

class UICamera : public UIEntity
{
public:
  UICamera(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

  void update() override;

private:
  // FIXME: we never free() the lv_obj_t*'s in code
  lv_obj_t* imgpanel;
};
