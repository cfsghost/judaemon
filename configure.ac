AC_PREREQ(2.57)
AC_INIT(judaemon, 0.1)
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_CC_C_O
AC_PROG_LIBTOOL

AC_HEADER_STDC
# Checks for libraries.
pkg_modules="clutter-1.0 \
             xrandr \
             json-glib-1.0"

PKG_CHECK_MODULES(PACKAGE, [$pkg_modules])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

JUDAEMON_MODULE="-avoid-version \
-rpath \$(libdir)/judaemon \
-no-undefined "'-export-symbols-regex "^[[^_]].*"'
AC_SUBST(JUDAEMON_MODULE)

AC_ARG_ENABLE(debug,
              AC_HELP_STRING([--enable-debug], [Enable debugging]),
              CFLAGS="$CFLAGS -g -D_DEBUG")

GETTEXT_PACKAGE=$PACKAGE
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Gettext package.])

ALL_LINGUAS=""
AC_SUBST(ALL_LINGUAS)
AM_GLIB_GNU_GETTEXT

AC_OUTPUT([
  Makefile
  include/Makefile
  include/judaemon/Makefile
  src/Makefile
  modules/Makefile
  modules/power/Makefile
  data/Makefile
  po/Makefile
])
