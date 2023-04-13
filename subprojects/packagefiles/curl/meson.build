project('curl', 'c',
  meson_version : '>=0.56.0',
)

mod = import('unstable-external_project')

p = mod.add_project('configure',
  configure_options : [#'--prefix=@PREFIX@',
                       #'--libdir=@LIBDIR@',
                       # '--incdir=@INCLUDEDIR@',
                       # '--enable-foo',
                       '--with-openssl',
                       '--enable-websockets'
                      ],
)

curl_dep = p.dependency('curl')
meson.override_dependency('curl', curl_dep)
