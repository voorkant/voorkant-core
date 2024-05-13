project(
    'client',
    ['cpp', 'c'],
    version: '0.1',
    default_options: ['warning_level=3', 'cpp_std=c++20'],
)

cpp = meson.get_compiler('cpp')

json_dep = dependency('nlohmann_json')

thread_dep = dependency('threads')

curl_dep = dependency(
    'libcurl',
    version: '>=8.5',
    allow_fallback: true,
    default_options: [
        'websockets=enabled',
        'tests=disabled',
        'bindlocal=disabled',
        'dict=disabled',
        'shuffle-dns=disabled',
        'doh=disabled',
        'file=disabled',
        'form-api=disabled',
        'ftp=disabled',
        'gopher=disabled',
        'imap=disabled',
        'ldap=disabled',
        'ldaps=disabled',
        'mime=disabled',
        'mqtt=disabled',
        'netrc=disabled',
        'pop3=disabled',
        'progress-meter=disabled',
        'psl=disabled',
        'sspi=disabled',
        'rtsp=disabled',
        'rtmp=disabled',
        'smb=disabled',
        'smtp=disabled',
        'socketpair=disabled',
        'telnet=disabled',
        'tftp=disabled',
        'tls-srp=disabled',
        'unixsockets=disabled',
        'openssl=disabled',
        'brotli=disabled',
        'http2=disabled',
        'zstd=disabled',
        'ssl=disabled',
        'ntlm=disabled',
        'kerberos-auth=disabled',
        'aws=disabled',
        'idn=disabled',
        'gss-api=disabled',
        'ssh=disabled',
        'tool=disabled',
        'default_library=static',
    ],
)



brew_prefix = '/opt/homebrew/include'
brew = find_program('brew', required: false)
if brew.found()
    cmd_brew_prefix = run_command('brew', '--prefix', check: false)
    if cmd_brew_prefix.returncode() == (0)
        brew_prefix = cmd_brew_prefix.stdout().strip()
    endif
endif


cmake = import('cmake')
cmake_options = cmake.subproject_options()
cmake_options.append_compile_args(
    'c',
    '-DLV_CONF_INCLUDE_SIMPLE',
    '-DLV_LVGL_H_INCLUDE_SIMPLE',
    '-DLV_CONF_PATH=' + meson.current_build_dir() + '/../src/lv_conf.h',
    '-I' + meson.current_build_dir() + '/../src',
    '-I' + meson.current_build_dir() + '/../subprojects/lvgl',
    '-I/' + brew_prefix + '/include',
)
cmake_options.append_compile_args(
    'cpp',
    '-DLV_CONF_INCLUDE_SIMPLE',
    '-DLV_LVGL_H_INCLUDE_SIMPLE',
    '-DLV_CONF_PATH=' + meson.current_build_dir() + '/../src/lv_conf.h',
    '-I' + meson.current_build_dir() + '/../src',
    '-I' + meson.current_build_dir() + '/../subprojects/lvgl',
    '-I/' + brew_prefix + '/include',
)

if get_option('front-lvgl').enabled()
    if get_option('lvgl-driver') == 'sdl'
        sdl2_dep = dependency('sdl2')
        cmake_options.append_compile_args('c', '-DVOORKANT_LVGL_SDL')
        cmake_options.append_compile_args('cpp', '-DVOORKANT_LVGL_SDL')
        lvgl_backend_define = '-DVOORKANT_LVGL_SDL'
    elif get_option('lvgl-driver') == 'fbdev'
        sdl2_dep = []
        cmake_options.append_compile_args('c', '-DVOORKANT_LVGL_FBDEV')
        cmake_options.append_compile_args('cpp', '-DVOORKANT_LVGL_FBDEV')
        lvgl_backend_define = '-DVOORKANT_LVGL_FBDEV'
    endif

    lvgl_proj = cmake.subproject('lvgl', options: cmake_options)
    lvgl_dep = lvgl_proj.dependency('lvgl')

    lvgl_drivers_proj = cmake.subproject('lv_drivers', options: cmake_options)
    lvgl_drivers_proj2 = cmake.subproject('lv_drivers', options: cmake_options)
    lvgl_drivers_dep = lvgl_drivers_proj.dependency('lv_drivers')
    quickjs_options = cmake.subproject_options()
    quickjs_options.add_cmake_defines({'BUILD_QJS_LIBC': true})
    quickjs_options.add_cmake_defines({'BUILD_STATIC_QJS_EXE': true}) # FIXME: remove
    quickjs_proj = cmake.subproject('quickjs', options: quickjs_options)
    quickjs_dep = quickjs_proj.dependency('qjs')
endif

incdir = include_directories('./src/')

openssl_dep = dependency('openssl')
zlib_dep = dependency('zlib')

if cpp.links(
    '''int main(int argc, char **argv) { return 0; }''',
    args: '-latomic',
    name: 'libatomic',
)
    libatomic = declare_dependency(link_args: '-latomic')
else
    libatomic = []
endif


if get_option('front-ftxui').enabled()
    ftxui_screen_dep = dependency('ftxui-screen')
    ftxui_dom_dep = dependency('ftxui-dom')
    ftxui_component_dep = dependency('ftxui-component')

    executable(
        'client-ftxui',
        [
            'src/main.cpp',
            'src/logger.cpp',
            'src/Backend.cpp',
            'src/HAEntity.cpp',
            'src/WSConn.cpp',
            'src/front-ftxui.cpp',
            'src/generated/domains.hpp',
        ],
        install: true,
        dependencies: [
            json_dep,
            thread_dep,
            curl_dep,
            ftxui_screen_dep,
            ftxui_dom_dep,
            ftxui_component_dep,
            openssl_dep,
            zlib_dep,
            libatomic,
        ],
    )
endif

executable(
    'client-cli',
    [
        'src/main.cpp',
        'src/logger.cpp',
        'src/Backend.cpp',
        'src/Observer.hpp',
        'src/HAEntity.cpp',
        'src/WSConn.cpp',
        'src/front-cli.cpp',
        'src/generated/domains.hpp',
    ],
    install: true,
    dependencies: [
        json_dep,
        thread_dep,
        curl_dep,
        openssl_dep,
        zlib_dep,
        libatomic,
    ],
)

if get_option('front-lvgl').enabled()
    date_dep = dependency('date')
    tz_dep = dependency('tz')

    executable(
        'client-lvgl',
        [
            'src/main.cpp',
            'src/logger.cpp',
            'src/Backend.cpp',
            'src/HAEntity.cpp',
            'src/WSConn.cpp',
            'src/uicomponents/imgs/colorwheel24.c',
            'src/uicomponents/imgs/colortemp24.c',
            'src/uicomponents/imgs/brightness24.c',
            'src/uicomponents/imgs/white24.c',
            'src/uicomponents/uirgblight.cpp',
            'src/uicomponents/UILogBox.cpp',
            'src/uicomponents/uiapexcard.cpp',
            'src/uicomponents/UIComponents.cpp',
            'src/front-lvgl.cpp',
            'src/lv_conf.h',
            'src/generated/domains.hpp',
        ],
        install: true,
        dependencies: [
            json_dep,
            thread_dep,
            curl_dep,
            lvgl_dep,
            lvgl_drivers_dep,
            sdl2_dep,
            openssl_dep,
            zlib_dep,
            libatomic,
            date_dep,
            tz_dep,
            quickjs_dep,
        ],
        include_directories: incdir,
        cpp_args: [
            '-DLV_CONF_PATH=' + meson.current_build_dir() + '/../src/lv_conf.h',
            lvgl_backend_define,
        ],
    )
endif
