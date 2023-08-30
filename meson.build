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


executable('client',
           ['src/main.cpp', 'src/back-homeassistant.cpp', 'src/front-ftxui.cpp'],
           install : true,
	   dependencies : [json_dep, thread_dep, curl_dep, ftxui_screen_dep, ftxui_dom_dep, ftxui_component_dep]
	   )

