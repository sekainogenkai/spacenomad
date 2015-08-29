AC_INIT([spacenomad], [0.0], [https://bitbucket.org/sannin/spacenomad/issues])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign subdir-objects])
dnl supports subdir-objects and defines EXEEXT
AM_PROG_CC_C_O
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext])
AM_CONDITIONAL([WINDRES], [test "x${EXEEXT}" = "x.exe"])

AC_ARG_VAR([GIMP], [The GIMP binary to use for script-fu as part of the build process.])
AC_CHECK_PROGS([GIMP], [gimp-console gimp])

dnl Search for an SVG tool
svgtool_found=
AC_ARG_VAR([INKSCAPE], [Inkscape binary to use during build when rastering vectors.])
AS_IF([test "x${svtool_found}" = "x"], [AC_CHECK_PROGS([INKSCAPE], [inkscape])])
AM_CONDITIONAL([USE_INKSCAPE], [test "x${svgtool_found}" = "x" && test "x${INKSCAPE}" != "x"])
AM_COND_IF([USE_INKSCAPE], [svgtool_found=true])

AC_ARG_VAR([RSVG], [The rsvg binary to use during build when rasterizing vectors if inkscape is unavailable.])
AS_IF([test "x${svgtool_found}" = "x"], [AC_CHECK_PROGS([RSVG], [rsvg])])
AM_CONDITIONAL([USE_RSVG], [test "x${svgtool_found}" = "x" && test "x${RSVG}" != "x"])
AM_COND_IF([USE_RSVG], [svgtool_found=true])

AS_IF(
	[test "x${svgtool_found}" = "x"],
        [AC_MSG_ERROR([Unable to find a tool to rasterize SVG with. I support inkscape and rsvg.])])
dnl End search for SVG tool

AC_ARG_VAR([RASTER_DPI], [Specify the DPI to use when rendering vectors to rasters. Defaults to 120.])
AS_IF([test "x${RASTER_DPI}" = "x"], [RASTER_DPI=120])

AC_ARG_WITH([meganz-mingw-std-threads], [AS_HELP_STRING([--with-meganz-mingw-std-threads=/path/to/repo], [Enable compiling against https://github.com/meganz/mingw-std-threads.git, optionally specifying where the includes may be found.])], [], [with_meganz_mingw_std_threads=no])
AS_IF(
	[test "x$with_meganz_mingw_std_threads" != "xno"],
	[AC_DEFINE([HAVE_MEGANZ_MINGW_STD_THREADS], [1])
	AS_IF(
		[test "x$with_meganz_mingw_std_threads" != "xyes"],
		[CPPFLAGS="$CPPFLAGS '-I$with_meganz_mingw_std_threads'"])])

PKG_CHECK_MODULES([SDL2], [sdl2 SDL2_image SDL2_ttf])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
