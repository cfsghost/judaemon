module_LTLIBRARIES = xrandr.la
moduledir = $(libdir)/judaemon

xrandr_la_SOURCES = \
	xrandr.c

xrandr_la_CFLAGS = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/include \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	$(PACKAGE_CFLAGS) \
	$(G_CAST_CHECKS)

xrandr_la_LDFLAGS = \
	-module \
	@JUDAEMON_MODULE@
