#include "main.hpp"

#include "argparse.hpp"
#include "src/argparse.hpp"

#include <iostream>
#include <sdl/sdl_common.h>
#include <string>
#include <unistd.h>

#include <lvgl.h>
#include <src/core/lv_disp.h>
#include "sdl/sdl.h"

using std::string;
// using std::map;

using std::cout;
using std::cerr;
using std::endl;
using std::flush;

static uint32_t intFromRGB(json attrs)
{
    if(attrs.count("rgb_color")) {
        auto rgb = attrs["rgb_color"];
        // cout<<"RGB "<<rgb<<endl;
        if (rgb.size() == 3) {
            uint32_t color = (rgb[0].get<int>() << 16) + (rgb[1].get<int>() << 8) + (rgb[2].get<int>());
            // cout<<" "<<color;
            return color;
        }
    }
}

static uint32_t c=0;
static string current_light; // FIXME: THIS NEEDS A MUTEX
static bool toggle = false;

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        toggle = true;
        // static uint32_t cnt = 0;
        // cnt++;

        // /*Get the first child of the button which is the label and change its text*/
        // lv_obj_t * label = lv_obj_get_child(btn, 0);
        // lv_label_set_text_fmt(label, "Button: %d", cnt);
        // cerr<<"cnt="<<cnt<<endl;
    }
}

void uithread(WSConn & wc, int argc, char* argv[])
{
    cerr<<"calling lv_init"<<endl;
    lv_init();
    sdl_init();
    cerr<<"called lv_init and sdl_init"<<endl;

#define MY_DISP_HOR_RES 480

    /*Create a display buffer*/
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf_1[SDL_HOR_RES * SDL_VER_RES];
    static lv_color_t buf_2[SDL_HOR_RES * SDL_VER_RES];
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, SDL_HOR_RES * SDL_VER_RES);

    lv_disp_drv_t disp_drv;                 /*A variable to hold the drivers. Can be local variable*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    disp_drv.draw_buf = &disp_buf;            /*Set an initialized buffer*/
    disp_drv.flush_cb = sdl_display_flush;        /*Set a flush callback to draw to the display*/
    lv_disp_t * disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

    lv_indev_drv_t enc_drv;
    lv_indev_drv_init(&enc_drv);
    enc_drv.type = LV_INDEV_TYPE_POINTER;
    enc_drv.read_cb = sdl_mouse_read;
    lv_indev_t * enc_indev = lv_indev_drv_register(&enc_drv);
    // lv_indev_set_group(enc_indev, g);
    lv_group_t * g = lv_group_create();
    lv_group_set_default(g);

// START BUTTON EXAMPLE
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 240, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
// END BUTTON EXAMPLE

    argparse::ArgumentParser program("client-cli");

    argparse::ArgumentParser subscribe_command("subscribe");
    subscribe_command.add_argument("pattern")
      .help("specific state name, or *"); // maybe .remaining() so you can subscribe multiple?

    program.add_subparser(subscribe_command);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        cerr << err.what() << endl;
        cerr << program;
        return;
    }

    if (program.is_subcommand_used(subscribe_command)) {
        // FIXME: now actually use the argument
        cerr << "should subscribe to " << subscribe_command.get<string>("pattern") << endl;
    }
    else {
        cerr << "no command given" << endl;
    }


    int i = 0;
    while(true) {
        if (toggle) {
            json cmd;

            cmd["type"]="call_service";
            cmd["domain"]=states[current_light]->getDomain();
            cmd["service"]="toggle";
            cmd["target"]["entity_id"]=current_light;

            wc.send(cmd);

            toggle = false;
        }
        // uint32_t c = rand();
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(intFromRGB(states[current_light]->getJsonState()["attributes"])), LV_PART_MAIN);
        lv_label_set_text(label, states[current_light]->getJsonState()["attributes"]["friendly_name"].get<string>().c_str());
        usleep(5*1000); // 5000 usec = 5 ms
        lv_tick_inc(5); // 5 ms
        lv_task_handler();
        if (i++ == (1000/5)) {
            cerr<<"."<<flush;
            i = 0;
        }
    }
}

void uithread_refresh(std::vector<std::string> whatchanged) // would be cool if this got told what changed
{
    // return;
    std::scoped_lock lk(entrieslock, stateslock, domainslock);

    cerr<<whatchanged.size()<<endl;
    for(const auto &changed : whatchanged) {
        cout<<"state for "<<changed<<" is "<<states[changed]->getInfo()<<endl;
        auto attrs = states[changed]->getJsonState()["attributes"];
        cout<<attrs<<endl;
        if (states[changed]->getDomain() == "light") {
            current_light = changed;
        }
        // if(attrs.count("rgb_color")) {
        //     auto rgb = attrs["rgb_color"];
        //     cout<<"RGB "<<rgb<<endl;
        //     if (rgb.size() == 3) {
        //         uint32_t color = (rgb[0].get<int>() << 16) + (rgb[1].get<int>() << 8) + (rgb[2].get<int>());
        //         cout<<" "<<color;
        //         c=color;
        //     }
        // }
        for(const auto &attr : states[changed]->attrVector()) {
            cout<<"  " << attr <<endl;
        }
    }
}
