project('SimpleIniParser', 'cpp',
    default_options : [ 'buildtype=release', 'default_library=static' ],
    license         : 'ISC',
    version         : '3.0.0',
)

sources = []
subdir('source')

library(meson.project_name(), sources,
    include_directories : 'include',

    cpp_args : [ '-Wall', '-Wextra', '-Werror', '-std=gnu++20' ],
)
