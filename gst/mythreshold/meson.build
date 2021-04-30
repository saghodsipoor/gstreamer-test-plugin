mythreshold_sources = [
  'plugin.c',
  'gstmythreshold.c'
]

gstmythreshold = library('gstmythreshold',
  mythreshold_sources,
  c_args : gst_plugins_good_args,
  include_directories : [configinc],
  dependencies : [gstbase_dep, gstvideo_dep, libm],
  install : true,
  install_dir : plugins_install_dir,
)
pkgconfig.generate(gstmythreshold, install_dir : plugins_pkgconfig_install_dir)
