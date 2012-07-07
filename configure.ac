dnl -*- Autoconf -*-

dnl This file is part of edisinfo
dnl 
dnl Copyright 2012 Brent Sanders
dnl 
dnl edisinfo is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl 
dnl edisinfo is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with edisinfo.  If not, see <http://www.gnu.org/licenses/>.



AC_PREREQ(2.60)
AC_INIT([edisinfo], [1.0], [edisinfo@thoughtnoise.net])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.6 foreign no-define dist-bzip2 color-tests])

AC_CONFIG_SRCDIR([dinfo.c])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/dinfo.c])

dnl ----------------------------------------

dnl C language
AC_PROG_CC
gl_EARLY
gl_INIT

dnl standard depends
AC_TYPE_SIZE_T
AC_FUNC_MALLOC
AC_CHECK_HEADERS([stdlib.h string.h])
AC_CHECK_FUNCS([sprintf strlen])

dnl we need libeinfo

AC_ARG_WITH(einfo,AC_HELP_STRING([--with-einfo=PFX],[Prefix where libeinfo is installed (optional)]), einfo_prefix="$withval", einfo_prefix="")
AC_ARG_WITH(einfo-libraries,AC_HELP_STRING([--with-einfo-libraries=DIR],[Directory where einfo library is installed (optional)]), einfo_libraries="$withval", einfo_libraries="")
AC_ARG_WITH(einfo-includes,AC_HELP_STRING([--with-einfo-includes=DIR],[Directory where einfo header files are installed (optional)]), einfo_includes="$withval", einfo_includes="")
AC_ARG_ENABLE(einfotest,AC_HELP_STRING([--disable-einfotest],[Do not try to compile and run a test program for einfo program]),, enable_einfotest=yes)

if test "x$einfo_libraries" != "x" ; then
  EINFO_LIBS="-L$einfo_libraries"
elif test "x$einfo_prefix" = "xno" || test "x$einfo_prefix" = "xyes" ; then
  EINFO_LIBS=""
elif test "x$einfo_prefix" != "x" ; then
  EINFO_LIBS="-L$einfo_prefix/lib"
elif test "x$prefix" != "xNONE" ; then
  EINFO_LIBS="-L$prefix/lib"
fi

if test "x$einfo_prefix" != "xno" ; then
  EINFO_LIBS="$EINFO_LIBS -leinfo"
fi

if test "x$einfo_includes" != "x" ; then
  EINFO_CFLAGS="-I$einfo_includes"
elif test "x$einfo_prefix" = "xno" || test "x$einfo_prefix" = "xyes" ; then
  EINFO_CFLAGS=""
elif test "x$einfo_prefix" != "x" ; then
  EINFO_CFLAGS="-I$einfo_prefix/include"
elif test "x$prefix" != "xNONE"; then
  EINFO_CFLAGS="-I$prefix/include"
fi

AC_SUBST(EINFO_CFLAGS)
AC_SUBST(EINFO_LIBS)
CFLAGS="$CFLAGS $EINFO_CFLAGS"
LIBS="$LIBS $EINFO_LIBS"

dnl ----------------------------------------

AC_CONFIG_FILES([Makefile
                lib/Makefile
                src/Makefile])
AC_OUTPUT

