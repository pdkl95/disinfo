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

bin_PROGRAMS = dinfo dwarn derror dbegin dend dindent doutdent dexec dshowexec

AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib

LDADD = libdinfo.a $(top_builddir)/lib/libgnu.a

noinst_LIBRARIES = libdinfo.a
libdinfo_a_SOURCES = common.c common.h

#libdinfo_a_LDFLAGS = $(LTLIBINTL)
