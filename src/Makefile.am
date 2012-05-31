bin_PROGRAMS = dinfo dwarn derror dbegin dend dindent doutdent dexec

AM_CPPFLAGS = -I$(top_builddir)/lib -I$(top_srcdir)/lib

LDADD = libdinfo.a $(top_builddir)/lib/libgnu.a

noinst_LIBRARIES = libdinfo.a
libdinfo_a_SOURCES = common.c common.h

#libdinfo_a_LDFLAGS = $(LTLIBINTL)
