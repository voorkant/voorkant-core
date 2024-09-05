#include "UILogBox.hpp"
#include "Observer.hpp"
#include "logger.hpp"
#include "uicomponents/UIComponents.hpp"

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
  // because we also log entries from LVGL, update might be called exactly while LVGL is rendering
  // if we update text without the lvlock at that point, lvgl throws a (non-fatal) error and our text is not rendered now
  // if we try grabbing lvlock during the render, while this thread already has it, terrible things happen
  // so instead we mark ourselves dirty and uithread will poke us soon
  dirty = true;
}

void UILogBox::updateIfNeeded()
{
  if (dirty) { // i feel like dirty itself should be locked, but the worst that could happen is sometimes missing an update, without causing deadlocks
    dirty = false;

    std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);

    lv_textarea_set_text(log_box, g_log.getForLogBox().c_str());
  }
}
