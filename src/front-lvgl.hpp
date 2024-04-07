#ifndef FRONT_LVGL_HPP
#define FRONT_LVGL_HPP

#include "main.hpp"
#include <iostream>
#include <src/widgets/lv_slider.h>
#include <string>
#include <unistd.h>
#include "ext/argparse/include/argparse/argparse.hpp"

// FIXME: the shape of this `if defined`/`elif defined`/.. error maybe itself could be a macro?

#if defined(VOORKANT_LVGL_SDL)
#include <sdl/sdl_common.h>
#include "sdl/sdl.h"
#elif defined(VOORKANT_LVGL_FBDEV)
#include <display/fbdev.h>
#include <indev/evdev.h>
#else
#error "no useful VOORKANT_LVGL_* found"
#endif

#include <lvgl.h>
#include <src/core/lv_disp.h>
#include <utility>
#include "sdl/sdl.h"

// FIXME the includes for all the components should maybe be in uicomponents.hpp itself?
#include "uicomponents/UIComponents.hpp"
#include "uicomponents/uirgblight.hpp"
#include "uicomponents/UICamera.hpp"
#include <generated/domains.hpp>

using std::string;
// using std::map;

using std::cerr;
using std::cout;
using std::endl;
using std::flush;

#endif