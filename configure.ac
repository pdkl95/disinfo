dnl -*- Autoconf -*-

dnl This file is part of disinfo
dnl 
dnl Copyright 2012 Brent Sanders
dnl 
dnl disinfo is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl 
dnl disinfo is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with disinfo.  If not, see <http://www.gnu.org/licenses/>.

AC_PREREQ([2.68])

AC_INIT([disinfo],[0.3.3],[disinfo@thoughtnoise.net])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.6 foreign no-define dist-bzip2 color-tests])

dnl AC_CONFIG_SRCDIR([dinfo.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/dinfo.c])

dnl ----------------------------------------

dnl C language
AC_PROG_CC
gl_EARLY
gl_INIT

dnl libraries
AC_PROG_LIBTOOL


dnl standard depends
AC_TYPE_SIZE_T
AC_FUNC_MALLOC
AC_CHECK_HEADERS([stdlib.h string.h])
AC_CHECK_FUNCS([sprintf strlen])

dnl other libraries not covered by gnulib
AX_WITH_CURSES

dnl ----------------------------------------

AC_CONFIG_FILES([Makefile
                lib/Makefile
                src/Makefile])
AC_OUTPUT

