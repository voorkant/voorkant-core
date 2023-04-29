project('client', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

cpp = meson.get_compiler('cpp')

# this dep could likely be cleaner
#pahopp_inc = include_directories('./libs/paho.mqtt.cpp/build/_install/include')
#pahopp_lib = cpp.find_library('paho-mqttpp3',
#  dirs : [ join_paths(meson.current_source_dir(), 'libs/paho.mqtt.cpp/build/_install/lib/') ])
# paho_dep = declare_dependency(link_with : paho_lib, 
#   include_directories : paho_inc)

#paho_liba = cpp.find_library('paho-mqtt3a', required: true)
#paho_libc = cpp.find_library('paho-mqtt3c', required: true)
#paho_libas = cpp.find_library('paho-mqtt3as', required: true)
#paho_libcs = cpp.find_library('paho-mqtt3cs', required: true)

json_dep = dependency('nlohmann_json')

thread_dep = dependency('threads')

ftxui_screen_dep = dependency('ftxui-screen')
ftxui_dom_dep = dependency('ftxui-dom')
ftxui_component_dep = dependency('ftxui-component')

curl_dep = dependency('curl')


executable('client',
           'main.cpp',
           install : true,
	   #           dependencies : [pahopp_lib, paho_liba, paho_libc, paho_libas, paho_libcs, thread_dep, curl_dep],
	   dependencies : [json_dep, thread_dep, curl_dep, ftxui_screen_dep, ftxui_dom_dep, ftxui_component_dep]
	   #include_directories : [pahopp_inc])
	   )
