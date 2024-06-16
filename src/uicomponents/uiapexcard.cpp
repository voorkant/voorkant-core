#include "uiapexcard.hpp"
#include "logger.hpp"
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style.h>
#include <src/layouts/grid/lv_grid.h>
#include <src/misc/lv_area.h>
#include <src/misc/lv_color.h>
#include <chrono>
#include <src/widgets/scale/lv_scale.h>
#include <time.h>
#include <date/date.h>

#include "quickjs.h"
#include "quickjs-libc.h"

// FIXME: we do a whole lot of json parsing in this file, that we should be doing somewhere else.

static auto const G_TICK_DIVIDER = 12; // if values.size() doesn't divide cleanly by this, your graph will suck

#if 0
void UIApexCard::drawEventCB(lv_event_t* _e)
{
  lv_draw_task_t* task = lv_event_get_draw_task(_e);
  lv_draw_dsc_base_t* dsc = task->draw_dsc;
  if (!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL))
    return;

  auto apexcard = (UIApexCard*)(_e->user_data);

  if (dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {
    size_t index = dsc->value;
    auto timestamp = apexcard->values[index].first; // FIXME: check index before we, well, index?
    struct tm local_timestamp;
    localtime_r(&timestamp, &local_timestamp);
    char timebuf[100] = "";
    if (local_timestamp.tm_hour == 0) {
      strftime(timebuf, sizeof(timebuf), "%d %b", &local_timestamp);
    }
    else if (index % 6 == 0) {
      strftime(timebuf, sizeof(timebuf), "%H:%M", &local_timestamp);
      // dsc->radius = 90;
    }
    lv_snprintf(dsc->text, dsc->text_length, "%s", timebuf); // is there something simpler than snprintf if we already have the string?
  }
}
#endif

// https://stackoverflow.com/a/38839725
// FIXME would be much easier to handle this in JS
date::sys_time<std::chrono::milliseconds>
parse8601(std::istream&& is)
{
  std::string save;
  is >> save;
  std::istringstream in{save};
  date::sys_time<std::chrono::milliseconds> tp;
  in >> date::parse("%FT%TZ", tp);
  if (in.fail()) {
    in.clear();
    in.exceptions(std::ios::failbit);
    in.str(save);
    in >> date::parse("%FT%T%Ez", tp);
  }
  return tp;
}

UIApexCard::UIApexCard(json _card, lv_obj_t* _parent) :
  UIEntity(nullptr, _parent)
{
  auto& backend = HABackend::getInstance();

  // // We generate a UI based on 'supported_color_modes'. color_mode then tells us which mode to use. Color_mode should be in uiupdate()
  flowpanel = lv_obj_create(_parent);
  lv_obj_set_width(flowpanel, uiEntityWidth * 3);
  lv_obj_set_height(flowpanel, /* MY_DISP_VER_RES */ 480 * 0.8);
  // lv_obj_set_style_pad_all(flowpanel, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(flowpanel, LV_ALIGN_CENTER);
  // lv_obj_set_flex_flow(flowpanel, LV_FLEX_FLOW_COLUMN);
  // lv_obj_set_flex_align(flowpanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  static int32_t column_dsc[] = {25, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};   /*2 columns with 100 and 400 ps width*/
  static int32_t row_dsc[] = {25, LV_GRID_FR(1), 25, LV_GRID_TEMPLATE_LAST}; /*3 100 px tall rows*/
  lv_obj_set_grid_dsc_array(flowpanel, column_dsc, row_dsc);
  lv_obj_set_layout(flowpanel, LV_LAYOUT_GRID);

  // lv_coord_t widthheight = uiEntityWidth - (lv_coord_t)50;

  g_log << Logger::LogLevel::Debug << "apexcard=" << _card << std::endl;
  lv_obj_t* label = createLabel(flowpanel, _card["header"]["title"]); // FIXME check show bool FIXME handle absence of title FIXME once we figure out object cleanup, stick this in the right spot
  lv_obj_set_width(label, LV_PCT(100));
  // lv_obj_set_align(label, LV_ALIGN_CENTER);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
  lv_obj_set_grid_cell(label, LV_GRID_ALIGN_CENTER, 0, 2, LV_GRID_ALIGN_CENTER, 0, 1);

  // chart_and_y_axis = lv_obj_create(flowpanel);
  // lv_obj_set_size(chart_and_y_axis, uiEntityWidth * 3 - 100, /* MY_DISP_VER_RES */ 480 * 0.65 - 30 - 25);
  // lv_obj_set_align(chart_and_y_axis, LV_ALIGN_CENTER);
  // lv_obj_set_grid_cell(chart_and_y_axis, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);
  // lv_obj_set_flex_align(chart_and_y_axis, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
  // lv_obj_set_style_border_width(chart_and_y_axis, 0, LV_PART_MAIN);

  lv_obj_t* scale_y = lv_scale_create(flowpanel);
  lv_obj_set_grid_cell(scale_y, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 1, 1);

  chart = lv_chart_create(flowpanel);
  lv_obj_set_grid_cell(chart, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);
  // lv_obj_set_size(chart, uiEntityWidth * 3 - 100 - 25, /* MY_DISP_VER_RES */ 480 * 0.65 - 30);
  // lv_obj_set_width(chart, LV_PCT(100));
  // lv_obj_set_align(chart, LV_ALIGN_CENTER);

  std::cerr << "lv_obj_get_content_width(chart)=" << lv_obj_get_content_width(chart) << std::endl;
  std::cerr << "lv_obj_get_content_height(chart)=" << lv_obj_get_content_height(chart) << std::endl;
  // lv_obj_center(chart);
  lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
  // lv_obj_add_event_cb(chart, drawEventCB, LV_EVENT_DRAW_PART_BEGIN, reinterpret_cast<void*>(this));

  std::cerr << _card << std::endl;
  std::string data_generator = _card["series"][0]["data_generator"].get<std::string>();
  std::cerr << "data_generator:" << data_generator << std::endl;
  // auto data = backend.getEntityByName(_card["series"][0]["entity"].get<std::string>())->getJsonState()["attributes"]["prices"]; // FIXME: do multiple series, leave decision of what data to plot to the data_generator JS
  auto entity = backend.getEntityByName(_card["series"][0]["entity"].get<std::string>())->getJsonState(); // FIXME: do multiple series, leave decision of what data to plot to the data_generator JS, handle absence of series key

  auto qjsrt = JS_NewRuntime();
  auto qjsc = JS_NewContext(qjsrt);

  js_std_add_helpers(qjsc, -1, NULL); // this gives us console.log

  // std::string c("JSON.stringify({'a':0.5})");
  std::string f = std::string("JSON.stringify((function(){ ") + data_generator + "})())";
  std::string e = "entity = " + entity.dump();
  std::string c = e + ";\n" + f;
  g_log << Logger::LogLevel::Debug << "JS_EVAL[" << c << "]" << std::endl;
  auto ret = JS_Eval(qjsc, c.data(), c.size(), "<internal>", 0);

  if (JS_IsException(ret)) {
    std::cerr << "exception" << std::endl;
    js_std_dump_error(qjsc);
  }
  auto rets = JS_ToCString(qjsc, ret);
  g_log << Logger::LogLevel::Debug << "rets=" << rets << std::endl;
  auto data = json::parse(rets);

  JS_FreeValue(qjsc, ret); // this also invalidates `rets`, but we parsed it into `data` just above
  std::cerr << "/JS_EVAL" << std::endl;

  auto min = std::numeric_limits<double>::max();
  auto max = std::numeric_limits<double>::min();
  std::cerr << data << std::endl;
  std::cerr << data.size() << std::endl;
  int nowindex = 0;
  int counter = 0;
  struct timeval now;
  gettimeofday(&now, nullptr);
  for (const auto& v : data) {
    std::cerr << "." << std::endl;

    std::chrono::duration<long, std::milli> fromtu;
    // the apexcard docs say v[0] is a milliseconds-since-epoch value but some configs stick date strings in there
    // Ruben suggests we could also add a bit of post-processing after data_generator that always returns ecma epoch time numbers
    switch (v[0].type()) {
    case nlohmann::detail::value_t::string: {
      auto from = v[0].get<string>();
      std::cerr << "from=" << from << std::endl;
      auto fromt = parse8601(std::istringstream{from});
      fromtu = fromt.time_since_epoch(); // unix epoch time in milliseconds
    } break;
    case nlohmann::detail::value_t::number_integer:
    case nlohmann::detail::value_t::number_unsigned:
    case nlohmann::detail::value_t::number_float:
      fromtu = std::chrono::duration<long, std::milli>(v[0].get<long>());
      break;
    default:
      break;
    }
    // if (v[0].type() == json::value_t::

    auto pair = std::make_pair<time_t, double>(fromtu.count() / 1000, v[1].get<double>());

    if (fromtu.count() / 1000 <= now.tv_sec) {
      nowindex = counter;
    }

    values.push_back(pair);
    min = std::min(min, pair.second);
    max = std::max(max, pair.second);
    counter++;
  }

  std::cerr << "min=" << min << ", max=" << max << std::endl;
  std::cerr << values.size() << std::endl;
  const auto float_factor = 1000.0; // milli-euros

  if (values.empty()) {
    values.push_back(std::make_pair(0, 0)); // FIXME: hack to avoid a crash inside LVGL with 0 chart points
    values.push_back(std::make_pair(3600 * 24 * 365 * 10, 100)); // FIXME: hack to avoid a crash inside LVGL with 0 chart points
    min = 0;
    max = 100;
  }
  lv_chart_set_point_count(chart, values.size()); // hours
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, min * float_factor, max * float_factor); // FIXME/FIXTHEM: lvgl 8.3 docs say it's LV_CHART_AXIS_PRIMARY which is just wrong
  lv_obj_t* scale_x = lv_scale_create(flowpanel);

  lv_scale_set_mode(scale_x, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
  lv_obj_update_layout(chart); // this makes lv_chart_get_point_pos_by_id work later

  lv_obj_set_size(scale_x, lv_obj_get_width(chart), 25);
  lv_scale_set_total_tick_count(scale_x, values.size());
  lv_scale_set_major_tick_every(scale_x, 1);
  lv_scale_set_range(scale_x, 0, values.size() - 1);
  lv_scale_set_label_show(scale_x, true);
  lv_obj_set_style_pad_hor(scale_x, lv_chart_get_first_point_center_offset(chart), 0);
  lv_obj_set_grid_cell(scale_x, LV_GRID_ALIGN_CENTER, 1, 1, LV_GRID_ALIGN_CENTER, 2, 1);

  lv_scale_set_mode(scale_y, LV_SCALE_MODE_VERTICAL_LEFT);
  lv_scale_set_range(scale_y, min * float_factor, max * float_factor);
  lv_obj_set_size(scale_y, 25, lv_obj_get_height(chart));
  lv_scale_set_total_tick_count(scale_y, 10);
  lv_scale_set_major_tick_every(scale_y, 1);
  lv_scale_set_label_show(scale_y, true);
  lv_obj_set_style_pad_hor(scale_y, lv_chart_get_first_point_center_offset(chart), 0);
  lv_obj_set_style_pad_ver(scale_y, 0, 0);


  // lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, values.size(), 1, true, 40); // major ticks point 10 px down, minor 5. values.size() major ticks, and 1 minor (actually means zero!) in between those. [true] labels on major ticks. 40px for labels.
  // lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 50);

  ser1 = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
  lv_coord_t* ser1_array = lv_chart_get_y_array(chart, ser1);

  for (int i = 0; i < values.size(); i++) {
    ser1_array[i] = values[i].second * 1000;
  }

  lv_obj_update_layout(chart); // this makes lv_chart_get_point_pos_by_id work later

  lv_point_t now_coordinates;
  std::cerr << "nowindex=" << nowindex << std::endl;
  lv_chart_get_point_pos_by_id(chart, ser1, nowindex, &now_coordinates);
  std::cerr << "coords(x,y)=" << now_coordinates.x << "," << now_coordinates.y << std::endl;

  lv_obj_t* now_label = createLabel(chart, "<-Now");
  lv_obj_set_pos(now_label, now_coordinates.x, now_coordinates.y);
  // lv_obj_set_style_border_color(now_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  // lv_obj_set_style_border_width(now_label, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_set_style_border_color(now_label, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_opa(now_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_opa(now_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(now_label, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

  // lv_obj_t* label = createLabel(flowpanel, entity->name);
  // lv_obj_set_width(label, LV_PCT(100));
  // lv_obj_set_align(label, LV_ALIGN_CENTER);
  // lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  // brightnessLabel = createLabel(flowpanel, "");
  // lv_obj_set_width(brightnessLabel, LV_PCT(100));
  // lv_obj_set_align(brightnessLabel, LV_ALIGN_CENTER);
  // lv_obj_set_style_text_align(brightnessLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

  // tilecontainer = lv_tileview_create(flowpanel);
  // lv_obj_add_event_cb(tilecontainer, UIApexCard::changeTileCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(this));
  // lv_obj_set_height(tilecontainer, uiEntityWidth);

  // lv_coord_t sliderheight = widthheight - (lv_coord_t)25;

  // if (showBrightness) {
  //   lv_obj_t* brightness_tile = lv_tileview_add_tile(tilecontainer, 0, 0, LV_DIR_HOR);
  //   brightnessSlider = lv_slider_create(brightness_tile);
  //   lv_obj_set_height(brightnessSlider, sliderheight);
  //   lv_obj_set_width(brightnessSlider, 50);
  //   lv_obj_set_align(brightnessSlider, LV_ALIGN_CENTER);
  //   lv_slider_set_range(brightnessSlider, 0, 255);
  //   lv_obj_add_event_cb(brightnessSlider, UIApexCard::slideBrightnessCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  // }

  // if (showColorWheel) {
  //   lv_obj_t* cw_tile = lv_tileview_add_tile(tilecontainer, 1, 0, LV_DIR_HOR);
  //   cw = lv_colorwheel_create(cw_tile, true);
  //   lv_obj_set_size(cw, widthheight, widthheight);
  //   lv_obj_set_align(cw, LV_ALIGN_CENTER);
  //   lv_colorwheel_set_mode_fixed(cw, false);
  //   lv_obj_add_event_cb(cw, UIApexCard::changeColorWheelCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(this));
  //   lv_obj_set_style_arc_width(cw, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
  //   lv_obj_set_style_border_color(cw, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
  //   lv_obj_set_style_opa(cw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
  //   lv_obj_set_style_border_opa(cw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
  //   lv_obj_set_style_border_width(cw, 3, LV_PART_KNOB | LV_STATE_DEFAULT);
  //   lv_obj_set_style_pad_all(cw, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
  // }

  // if (showColorTemp) {

  //   // TODO: RGBW and RGBWW have a few sliders underneath the color wheels
  //   // In white mode, the indicator on the color wheel should be removed. Not sure if we can do that.

  //   lv_obj_t* colortemp_tile = lv_tileview_add_tile(tilecontainer, 2, 0, LV_DIR_HOR);
  //   colortempSlider = lv_slider_create(colortemp_tile);
  //   lv_obj_set_height(colortempSlider, sliderheight);
  //   lv_obj_set_width(colortempSlider, 50);
  //   lv_obj_set_align(colortempSlider, LV_ALIGN_CENTER);
  //   int min_color_temp = getIntAttribute("min_color_temp_kelvin", 2000);
  //   int max_color_temp = getIntAttribute("max_color_temp_kelvin", 6500);
  //   // FIXME: for whatever reason we can't get this to work the opposite way around, which is what HA does
  //   lv_slider_set_range(colortempSlider, min_color_temp, max_color_temp);
  //   lv_obj_add_event_cb(colortempSlider, UIApexCard::slideColorTempCB, LV_EVENT_VALUE_CHANGED, reinterpret_cast<void*>(&entity));
  // }

  // btns = lv_obj_create(flowpanel);
  // lv_obj_remove_style_all(btns);
  // lv_obj_set_width(btns, uiEntityWidth - 15);
  // lv_obj_set_height(btns, 50);
  // lv_obj_set_style_pad_all(btns, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  // lv_obj_set_align(btns, LV_ALIGN_CENTER);
  // lv_obj_set_flex_flow(btns, LV_FLEX_FLOW_ROW);
  // lv_obj_set_flex_align(btns, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  // lv_obj_remove_flag(btns, LV_OBJ_FLAG_SCROLLABLE);

  // btnOnOff = createImageButton(LV_SYMBOL_POWER, UIApexCard::btnOnOffCB, LV_EVENT_VALUE_CHANGED, true);

  // if (showBrightness) {
  //   btnBrightness = createImageButton(&G_BRIGHTNESS24, UIApexCard::btnBrightnessCB, LV_EVENT_CLICKED);
  //   lv_obj_add_state(btnBrightness, LV_STATE_CHECKED);
  // }

  // if (showColorWheel) {
  //   btnColorWheel = createImageButton(&G_COLORWHEEL24, UIApexCard::btnColorWheelCB, LV_EVENT_CLICKED);
  // }
  // if (showColorTemp) {
  //   btnColorTemp = createImageButton(&G_COLORTEMP24, UIApexCard::btnColorTempCB, LV_EVENT_CLICKED);
  // }

  update();
}

void UIApexCard::update()
{
  std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);

  lv_chart_refresh(chart);
  // auto state = entity->getJsonState();
  // string colormode = getColorMode();
  // // std::cerr << "COLOR MODE: " << colormode << std::endl;
  // std::cerr << "UPDATED STATE FOR " << entity->name << ":" << state.dump(2) << std::endl;

  // {
  //   std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
  //   if (state["state"] == "on") { // FIXME: We should get rid of parsing JSON here
  //     lv_obj_add_state(btnOnOff, LV_STATE_CHECKED);
  //     int brightness = state["attributes"]["brightness"].get<int>(); // brightness is NULL If the thing is off
  //     lv_slider_set_value(brightnessSlider, brightness, LV_ANIM_OFF);
  //     int brightness_percent = static_cast<int>(brightness / 2.55);
  //     std::string str_brightness_percent = std::to_string(brightness_percent);
  //     lv_label_set_text(brightnessLabel, (str_brightness_percent + "%").c_str());
  //     if (colormode == "hs") {

  //       std::vector<int> vec_hs = state["attributes"]["hs_color"];

  //       lv_color_hsv_t hsv_val;
  //       hsv_val.h = vec_hs.at(0);
  //       hsv_val.s = vec_hs.at(1);
  //       hsv_val.v = brightness_percent;
  //       lv_colorwheel_set_hsv(cw, hsv_val);
  //     }
  //     else if (colormode == "color_temp") {
  //       int colortemp = state["attributes"]["color_temp_kelvin"].get<int>();
  //       std::cerr << "colormode == color temp and colortemp itself is: " << colortemp << std::endl;
  //       //   lv_slider_set_value(colortempSlider, colortemp, LV_ANIM_OFF);
  //     }
  //     else if (colormode == "brightness") {
  //       std::cerr << "BRIGHTNESS" << std::endl;
  //     }
  //     else if (colormode == "white") {
  //       std::cerr << "WHITE" << std::endl;
  //     }
  //     else {
  //       std::cerr << " NO COLOR MODE " << colormode << " SO USING RGB" << std::endl;
  //       std::vector<int> vec_rgb = state["attributes"]["rgb_color"];

  //       int rgb[3];
  //       short cnt = 0;
  //       for (auto col : vec_rgb) {
  //         rgb[cnt] = col;
  //         cnt++;
  //       }
  //       lv_colorwheel_set_rgb(cw, lv_color_make(rgb[0], rgb[1], rgb[2]));
  //     }
  //   }
  //   else {
  //     lv_obj_remove_state(btnOnOff, LV_STATE_CHECKED);
  //     lv_slider_set_value(brightnessSlider, 0, LV_ANIM_OFF);
  //     lv_label_set_text(brightnessLabel, "Off");
  //   }
  // }
}
