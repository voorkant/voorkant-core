#include "front-lvgl.hpp"

static uint32_t intFromRGB(json attrs)
{
  if (attrs.count("rgb_color")) {
    auto rgb = attrs["rgb_color"];
    // cout<<"RGB "<<rgb<<endl;
    if (rgb.size() == 3) {
      uint32_t color = (rgb[0].get<int>() << 16) + (rgb[1].get<int>() << 8) + (rgb[2].get<int>());
      // cout<<" "<<color;
      return color;
    }
  }

  return 0; // black. Should we return white? Some middle ground?
}

static string current_light; // FIXME: THIS NEEDS A MUTEX
static bool newcolor = false;

static void btn_event_cb(lv_event_t* e)
{
  lv_event_code_t code = lv_event_get_code(e);
  // lv_obj_t* btn = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    // static uint32_t cnt = 0;
    // cnt++;

    // /*Get the first child of the button which is the label and change its text*/
    // lv_obj_t * label = lv_obj_get_child(btn, 0);
    // lv_label_set_text_fmt(label, "Button: %d", cnt);
    // cerr<<"cnt="<<cnt<<endl;
  }
}

static std::array<std::pair<lv_obj_t*, lv_obj_t*>, 3> rgbsliders; // first is slider, second is label for slider

static void slider_event_cb(lv_event_t* e)
{
  lv_obj_t* slider = lv_event_get_target(e);

  for (const auto& rgbslider : rgbsliders) {
    if (rgbslider.first == slider) {
      /*Refresh the text*/
      lv_label_set_text_fmt(rgbslider.second, "%" LV_PRId32, lv_slider_get_value(slider));
      lv_obj_align_to(rgbslider.second, slider, LV_ALIGN_OUT_TOP_MID, 0, -15); /*Align top of the slider*/
    }
    newcolor = true;
  }
}

void uithread(HABackend& backend, int argc, char* argv[])
{
  argparse::ArgumentParser program("client-lvgl");

  argparse::ArgumentParser entity_command("entity");
  entity_command.add_argument("name")
    .help("what entity to render");

  program.add_subparser(entity_command);

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    cerr << err.what() << endl;
    cerr << program;
    return;
  }

  if (program.is_subcommand_used(entity_command)) {
    // FIXME: now actually use the argument
    current_light = entity_command.get<string>("name");
    cerr << "should render " << current_light << endl;
  }
  else {
    cerr << "no command given" << endl;
    return;
  }

  backend.Start();

  cerr << "calling lv_init" << endl;
  lv_init();
#if defined(VOORKANT_LVGL_SDL)
  sdl_init();
#elif defined(VOORKANT_LVGL_FBDEV)
  fbdev_init();
#else
#error "no useful VOORKANT_LVGL_* found"
#endif
  cerr << "called fbdev_init" << endl;

// make sure these numbers align with SDL_HOR_RES/SDL_VER_RES
#define MY_DISP_HOR_RES 800
#define MY_DISP_VER_RES 480
#define DISP_BUF_SIZE 16384

  /*Create a display buffer*/
  static lv_disp_draw_buf_t disp_buf;
  static lv_color_t buf_1[DISP_BUF_SIZE];
  static lv_color_t buf_2[DISP_BUF_SIZE];
  lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, DISP_BUF_SIZE);

  lv_disp_drv_t disp_drv; /*A variable to hold the drivers. Can be local variable*/
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.hor_res = MY_DISP_HOR_RES;
  disp_drv.ver_res = MY_DISP_VER_RES;
  disp_drv.draw_buf = &disp_buf; /*Set an initialized buffer*/
#if defined(VOORKANT_LVGL_SDL)
  disp_drv.flush_cb = sdl_display_flush;
#elif defined(VOORKANT_LVGL_FBDEV)
  disp_drv.flush_cb = fbdev_flush; /*Set a flush callback to draw to the display*/
#else
#error "no useful VOORKANT_LVGL_* found"
#endif
  /*lv_disp_t* disp;*/
  /*disp = */ lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

// #if 0
#if defined(VOORKANT_LVGL_FBDEV)
  evdev_init();
#endif
  lv_indev_drv_t enc_drv;
  lv_indev_drv_init(&enc_drv);
  enc_drv.type = LV_INDEV_TYPE_POINTER;
#if defined(VOORKANT_LVGL_SDL)
  enc_drv.read_cb = sdl_mouse_read;
#elif defined(VOORKANT_LVGL_FBDEV)
  enc_drv.read_cb = evdev_read;
#else
#error "no useful VOORKANT_LVGL_* found"
#endif
  /*lv_indev_t* enc_indev = */ lv_indev_drv_register(&enc_drv);
  // #endif
  // lv_indev_set_group(enc_indev, g);
  // lv_group_t* g = lv_group_create();
  // lv_group_set_default(g);

  /*Create a container with ROW flex direction that wraps.
  This is our MAIN box that we put everything in. We have this here because we want some spacing around it.
  */
  lv_obj_t* cont_row = lv_obj_create(lv_scr_act());
  lv_obj_remove_style_all(cont_row);
  lv_obj_set_size(cont_row, MY_DISP_HOR_RES, MY_DISP_VER_RES);
  lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_COLUMN_WRAP);
  lv_obj_set_style_pad_row(cont_row, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_column(cont_row, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

  std::vector<std::unique_ptr<UIEntity>> uielements;
  int i = 0;
  auto entities = backend.GetEntitiesByDomain("light");
  for (const auto& entity : entities) {
    // if (i % 2 == 0) {
    //   std::unique_ptr<UIEntity> btn = std::make_unique<UIButton>(entity, cont_row);
    //   uielements.push_back(std::move(btn));
    // }
    // else {
    //   std::unique_ptr<UIEntity> sw = std::make_unique<UISwitch>(entity, cont_row);
    //   uielements.push_back(std::move(sw));
    // }
    // if (entity->name == "Entrance Color + White Lights") {
    std::unique_ptr<UIEntity> rgb = std::make_unique<UIRGBLight>(entity, cont_row);
    uielements.push_back(std::move(rgb));
    //}

    i++;
  }

  i = 0;
  while (true) {
    usleep(5 * 1000); // 5000 usec = 5 ms
    {
      std::unique_lock<std::mutex> lvlock(G_LVGLUpdatelock);
      lv_tick_inc(5); // 5 ms
      lv_task_handler();
    }
    if (i++ == (1000 / 5)) {
      cerr << "." << flush;
      i = 0;
    }
  }
}