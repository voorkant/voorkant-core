project('client', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

cpp = meson.get_compiler('cpp')

add_global_arguments('-DLV_CONF_PATH=/home/peter/projects/home/toon-ha/client/src/lv_conf.h', language : 'c')

json_dep = dependency('nlohmann_json')

thread_dep = dependency('threads')

ftxui_screen_dep = dependency('ftxui-screen')
ftxui_dom_dep = dependency('ftxui-dom')
ftxui_component_dep = dependency('ftxui-component')

curl_dep = dependency('curl')


cmake = import('cmake')

lvgl_proj = cmake.subproject('lvgl')
lvgl_dep = lvgl_proj.dependency('lvgl')

executable('client-ftxui',
           ['src/main.cpp', 'src/back-homeassistant.cpp', 'src/front-ftxui.cpp'],
           install : true,
     dependencies : [json_dep, thread_dep, curl_dep, ftxui_screen_dep, ftxui_dom_dep, ftxui_component_dep]
     )

executable('client-cli',
           ['src/main.cpp', 'src/back-homeassistant.cpp', 'src/front-cli.cpp'],
           install : true,
      dependencies : [json_dep, thread_dep, curl_dep]
      )

executable('client-lvgl-sdl',
           ['src/main.cpp', 'src/back-homeassistant.cpp', 'src/front-lvgl.cpp', 'src/lv_conf.h'],
          install : true,
      dependencies : [json_dep, thread_dep, curl_dep, lvgl_dep],
      cpp_args : '-DLV_CONF_PATH=/home/peter/projects/home/toon-ha/client/src/lv_conf.h'
      )
