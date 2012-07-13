########################################################################
# This file is part of edisinfo                                        #
#                                                                      #
# Copyright 2012 Brent Sanders                                         #
#                                                                      #
# edisinfo is free software: you can redistribute it and/or modify     #
# it under the terms of the GNU General Public License as published by #
# the Free Software Foundation, either version 3 of the License, or    #
# (at your option) any later version.                                  #
#                                                                      #
# edisinfo is distributed in the hope that it will be useful,          #
# but WITHOUT ANY WARRANTY; without even the implied warranty of       #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        #
# GNU General Public License for more details.                         #
#                                                                      #
# You should have received a copy of the GNU General Public License    #
# along with edisinfo.  If not, see <http://www.gnu.org/licenses/>.    #
########################################################################

AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib


noinst_LIBRARIES = libdinfo.a
libdinfo_a_SOURCES = \
	color.c color.h \
	common.c common.h

#libdinfo_a_LDFLAGS = $(LTLIBINTL)


bin_PROGRAMS = \
	dinfo dwarn derror \
	dbegin dend \
	dindent doutdent \
	dexec dshowexec \
	derrmsg

LDADD = libdinfo.a $(top_builddir)/lib/libgnu.a


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
