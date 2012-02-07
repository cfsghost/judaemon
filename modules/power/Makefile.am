module_LTLIBRARIES = power.la
moduledir = $(libdir)/judaemon

power_la_SOURCES = \
	power.c

power_la_CFLAGS = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/include \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	$(PACKAGE_CFLAGS) \
	$(G_CAST_CHECKS)

power_la_LDFLAGS = \
	-module \
	@JUDAEMON_MODULE@
