## Process this file with automake to produce Makefile.in

bin_PROGRAMS = judaemon

INCLUDES = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/include \
	-DPACKAGE_BIN_DIR=\""$(bindir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_LIB_DIR=\"$(libdir)\" \
	$(PACKAGE_CFLAGS) \
	$(G_CAST_CHECKS)

judaemon_SOURCES = \
	conf.c \
	component.c \
	module.c \
	judaemon.c

judaemon_LDADD = \
		$(PACKAGE_LIBS) \
		$(INTLLIBS)
