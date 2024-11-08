project('OpenGL Project', ['c', 'cpp'], version: '1.0')

cpp_compiler = meson.get_compiler('cpp')

glfw_dep = dependency('glfw3', required: true)
include_dir = include_directories('include')

subdir('src')
