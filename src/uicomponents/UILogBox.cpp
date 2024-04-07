#include "UILogBox.hpp"
#include "Observer.hpp"
#include "logger.hpp"
#include "uicomponents/UIComponents.hpp"
#include <src/lv_api_map.h>
#include <src/widgets/lv_textarea.h>

UILogBox::UILogBox(lv_obj_t* _parent) :
  UIComponent(_parent)
{
  /* logger box */
  log_box = lv_textarea_create(_parent);
  lv_obj_set_height(log_box, LV_PCT(100));
  lv_obj_set_flex_align(log_box, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  lv_obj_set_flex_grow(log_box, 1);
  lv_textarea_set_placeholder_text(log_box, "No log...");
  g_log.attach((IObserver*)this);
}

UILogBox::~UILogBox()
{
  g_log.detach((IObserver*)this);
}

void UILogBox::update()
{
  lv_textarea_set_text(log_box, g_log.getForLogBox().c_str());
}