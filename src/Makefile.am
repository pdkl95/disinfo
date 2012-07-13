########################################################################
# This file is part of disinfo                                        #
#                                                                      #
# Copyright 2012 Brent Sanders                                         #
#                                                                      #
# disinfo is free software: you can redistribute it and/or modify     #
# it under the terms of the GNU General Public License as published by #
# the Free Software Foundation, either version 3 of the License, or    #
# (at your option) any later version.                                  #
#                                                                      #
# disinfo is distributed in the hope that it will be useful,          #
# but WITHOUT ANY WARRANTY; without even the implied warranty of       #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        #
# GNU General Public License for more details.                         #
#                                                                      #
# You should have received a copy of the GNU General Public License    #
# along with disinfo.  If not, see <http://www.gnu.org/licenses/>.    #
########################################################################

AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib


noinst_LIBRARIES = libcommon.a libindent.a

libcommon_a_SOURCES = \
	color.c color.h \
	common.c common.h

libindent_a_SOURCES = \
	indent.c indent.h
libindent_a_LIBADD = libcommon.a

bin_PROGRAMS = \
	dinfo dwarn derror \
	dbegin dend \
	dindent doutdent \
	dexec dshowexec \
	derrmsg

LDADD = libcommon.a $(top_builddir)/lib/libgnu.a

LIBS_INDENT = libindent.a ${LDADD}

dindent_LDADD = $(LIBS_INDENT)
doutdent_LDADD = $(LIBS_INDENT)


EXTRA_DIST = mkerrors.sh
BUILT_SOURCES = error_code_macros.h

ERRNO_DEPS = \
	/usr/include/asm-generic/errno-base.h \
	/usr/include/asm-generic/errno.h

error_code_macros.h: mkerrors.sh $(ERRNO_DEPS)
	@echo '*** Generating the "errno" macros from the local errno.h ***'
	cd $(top_builddir)/src && $(top_srcdir)/src/mkerrors.sh $@ $(ERRNO_DEPS)
	@echo '*** Successfully extracted $() unique errno values! ***'


distclean-local: distclean-local-error_code_macros
distclean-local-error_code_macros:
	rm -f $(top_builddir)/src/error_code_macros.h
