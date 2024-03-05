project(
    'curl',
    'c',
    version: '8.5.0',
    license: 'curl',
    meson_version: '>=0.57.0'
)

mod = import('unstable-external_project')


conf_opts = [#'--prefix=@PREFIX@',
                       #'--libdir=@LIBDIR@',
                       # '--incdir=@INCLUDEDIR@',
                       '--disable-bindlocal',
                       '--disable-dateparse',
                       '--disable-dict',
                       '--disable-dnsshuffle',
                       '--disable-dnsshuffle',
                       '--disable-doh',
                       '--disable-file',
                       '--disable-form-api',
                       '--disable-ftp',
                       '--disable-gopher',
                       '--disable-imap',
                       '--disable-ldap',
                       '--disable-mime',
                       '--disable-mqtt',
                       '--disable-netrc',
                       '--disable-pop3',
                       '--disable-progress-meter',
                       '--disable-rtsp',
                       '--disable-smb',
                       '--disable-smtp',
                       '--disable-socketpair',
                       '--disable-telnet',
                       '--disable-tftp',
                       '--disable-tls-srp',
                       '--disable-unix-sockets',
                       '--enable-option-checking=fatal',
                       '--enable-websockets',
                       '--without-openssl',
                       '--without-brotli',
                       '--without-libidn2',
                       '--without-libpsl',
                       '--without-nghttp2',
                       '--without-nghttp3',
                       '--without-zstd',
                       '--with-random=/dev/urandom',
                       '--without-ssl'
                      ]
if get_option('default_library') == 'shared'
    conf_opts += '--enable-shared'
    conf_opts += '--disable-static'
elif get_option('default_library') == 'static'
    conf_opts += '--disable-shared'
    conf_opts += '--enable-static'
elif get_option('default_library') == 'both'
    conf_opts += '--enable-shared'
    conf_opts += '--enable-static'
endif

p = mod.add_project('configure', configure_options: conf_opts)
  

curl_dep = p.dependency('curl')
meson.override_dependency('curl', curl_dep)
