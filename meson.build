project('client', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

cpp = meson.get_compiler('cpp')

json_dep = dependency('nlohmann_json')

thread_dep = dependency('threads')

ftxui_screen_dep = dependency('ftxui-screen')
ftxui_dom_dep = dependency('ftxui-dom')
ftxui_component_dep = dependency('ftxui-component')

curl_dep = dependency('curl')


brew_prefix='/opt/homebrew/include'
brew = find_program('brew', required: false)
if brew.found()
  cmd_brew_prefix = run_command('brew', '--prefix', check:false)
  if cmd_brew_prefix.returncode() == 0
    brew_prefix = cmd_brew_prefix.stdout().strip()
  endif
endif


cmake = import('cmake')
cmake_options = cmake.subproject_options()
cmake_options.append_compile_args('c',
  '-DLV_CONF_INCLUDE_SIMPLE',
  '-DLV_LVGL_H_INCLUDE_SIMPLE',
  '-DLV_CONF_PATH=' + meson.current_build_dir() +'/../src/lv_conf.h',
  '-I'+meson.current_build_dir()+'/../src', '-I'+meson.current_build_dir()+'/../subprojects/lvgl',
  '-I/'+brew_prefix+'/include'
  )
cmake_options.append_compile_args('cpp',
  '-DLV_CONF_INCLUDE_SIMPLE',
  '-DLV_LVGL_H_INCLUDE_SIMPLE',
  '-DLV_CONF_PATH=' + meson.current_build_dir() +'/../src/lv_conf.h',
  '-I'+meson.current_build_dir()+'/../src', '-I'+meson.current_build_dir()+'/../subprojects/lvgl',
  '-I/'+brew_prefix+'/include'
  )

lvgl_proj = cmake.subproject('lvgl', options: cmake_options)
lvgl_dep = lvgl_proj.dependency('lvgl')

lvgl_drivers_proj = cmake.subproject('lv_drivers', options: cmake_options)
lvgl_drivers_dep = lvgl_drivers_proj.dependency('lv_drivers')


sdl2_dep = dependency('sdl2')
incdir = include_directories('./src/')

executable('client-ftxui',
           ['src/main.cpp', 'src/Backend.cpp', 'src/HAEntity.cpp','src/WSConn.cpp','src/front-ftxui.cpp', 'src/generated/domains.hpp'],
           install : true,
     dependencies : [json_dep, thread_dep, curl_dep, ftxui_screen_dep, ftxui_dom_dep, ftxui_component_dep]
     )

 executable('client-cli',
            ['src/main.cpp', 'src/Backend.cpp', 'src/HAEntity.cpp','src/WSConn.cpp','src/front-cli.cpp', 'src/generated/domains.hpp'],
            install : true,
       dependencies : [json_dep, thread_dep, curl_dep]
       )

executable('client-lvgl-sdl',
           ['src/main.cpp', 'src/Backend.cpp', 'src/HAEntity.cpp', 'src/WSConn.cpp', 'src/front-lvgl.cpp', 'src/lv_conf.h', 'src/generated/domains.hpp'],
          install : true,
      dependencies : [json_dep, thread_dep, curl_dep, lvgl_dep, lvgl_drivers_dep, sdl2_dep],
      include_directories: incdir,
      cpp_args : '-DLV_CONF_PATH='+meson.current_build_dir()+'/../src/lv_conf.h'
)
