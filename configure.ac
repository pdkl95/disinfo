dnl -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.

AC_INIT([edisinfo], [1.0], [edisinfo@thoughtnoise.net])
AM_INIT_AUTOMAKE([foreign no-define dist-bzip2 color-tests])

AC_CONFIG_SRCDIR([dinfo.c])

AC_PREREQ(2.60)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/dinfo.c])

dnl ----------------------------------------

dnl C language
AC_PROG_CC

dnl library support
AC_PROG_RANLIB

dnl standard depends
AC_TYPE_SIZE_T
AC_FUNC_MALLOC
AC_CHECK_HEADERS([stdlib.h string.h])
AC_CHECK_FUNCS([strlen sprintf])

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


# AC_MSG_CHECKING(for libeinfo)
# if test "x$einfo_prefix" = "xno" ; then
#   no_einfo="disabled"
#   enable_einfotest="no"
# else
#   no_einfo=""
# fi


# if test "x$enable_einfotest" = "xyes" ; then
#   ac_save_CFLAGS="$CFLAGS"
#   ac_save_LIBS="$LIBS"
#   CFLAGS="$CFLAGS $EINFO_CFLAGS"
#   LIBS="$LIBS $EINFO_LIBS"
# dnl Now check if the installed Einfo is sufficiently new.
#   rm -f conf.einfotest
#   AC_TRY_RUN([
# #include <stdio.h>
# #include <stdlib.h>
# #include <string.h>
# #include <einfo.h>

# void test() {
#   einfo("test");
# }

# int main ()
# {
#   system("touch conf.einfotest");
#   return 0;
# }

# ],, no_einfo=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
#      CFLAGS="$ac_save_CFLAGS"
#      LIBS="$ac_save_LIBS"
# fi

# if test "x$no_einfo" = "xdisabled" ; then
#    AC_MSG_RESULT(no)
#    ifelse([$2], , :, [$2])
# elif test "x$no_einfo" = "x" ; then
#    AC_MSG_RESULT(yes)
#    ifelse([$1], , :, [$1])
# else
#    AC_MSG_RESULT(no)
#    if test -f conf.einfotest ; then
#      :
#    else
#      echo "*** Could not run einfo test program, checking why..."
#      CFLAGS="$CFLAGS $EINFO_CFLAGS"
#      LIBS="$LIBS $EINFO_LIBS"
#      AC_TRY_LINK([
# #include <stdio.h>
# #include <einfo/einfo.h>
# ],   [ return 0; ],
#      [ echo "*** The test program compiled, but did not run. This usually means"
#      echo "*** that the run-time linker is not finding OpenRC's libeinfo or finding the wrong"
#      echo "*** the wrong version. If it is not finding libeinfo, you'll need to set your"
#      echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
#      echo "*** to the installed location  Also, make sure you have run ldconfig if that"
#      echo "*** is required on your system"],
#      [ echo "*** The test program failed to compile or link. See the file config.log for the"
#      echo "*** exact error that occured. This usually means libeinfo was incorrectly installed"
#      echo "*** or that you have moved libeinfo since it was installed."
#      echo "***"
#      echo "*** libeinfo is part of the OpenRC package - is it installed?"])
#      CFLAGS="$ac_save_CFLAGS"
#      LIBS="$ac_save_LIBS"
#    fi
#    EINFO_CFLAGS=""
#    EINFO_LIBS=""
#    ifelse([$2], , :, [$2])
# fi
# rm -f conf.einfotest


AC_SUBST(EINFO_CFLAGS)
AC_SUBST(EINFO_LIBS)
CFLAGS="$CFLAGS $EINFO_CFLAGS"
LIBS="$LIBS $EINFO_LIBS"

dnl ----------------------------------------

AC_CONFIG_FILES([Makefile
                src/Makefile])
AC_OUTPUT
