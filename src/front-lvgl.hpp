#ifndef FRONT_LVGL_HPP
#define FRONT_LVGL_HPP

#include "main.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include "ext/argparse/include/argparse/argparse.hpp"

// FIXME: the shape of this `if defined`/`elif defined`/.. error maybe itself could be a macro?

#if defined(VOORKANT_LVGL_SDL)
// no includes necessary in lvgl9?
#elif defined(VOORKANT_LVGL_FBDEV)
#include <display/fbdev.h>
#include <indev/evdev.h>
#else
#error "no useful VOORKANT_LVGL_* found"
#endif

#include <lvgl.h>
#include <utility>
#include "uicomponents/UIComponents.hpp"
#include "uicomponents/uirgblight.hpp"
#include "uicomponents/uiapexcard.hpp"
#include <generated/domains.hpp>

using std::string;
// using std::map;

using std::cerr;
using std::cout;
using std::endl;
using std::flush;

#endif