#ifndef UIRGBLIGHT_HPP
#define UIRGBLIGHT_HPP
#include "UIComponents.hpp"

class UIRGBLight : public UIEntity
{
public:
  UIRGBLight(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent);

  void uiupdate() override;

private:
};

#endif