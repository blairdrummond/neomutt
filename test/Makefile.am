## Process this file with automake to produce Makefile.in
include $(top_srcdir)/flymake.am

AUTOMAKE_OPTIONS = 1.6 foreign

EXTRA_DIST = account2.h account.txt address.h address.txt bool.h bool.txt \
	common.h initial.h initial.txt magic.h magic.txt Makefile.am mbtable.h \
	mbtable.txt number.h number.txt path.h path.txt quad.h quad.txt \
	regex.h regex.txt set.h set.txt sort.h sort.txt string.h string.txt \
	synonym.h synonym.txt

AM_CPPFLAGS = -I$(top_srcdir)

noinst_LIBRARIES = libtest.a

libtest_a_SOURCES = account.c address.c bool.c common.c initial.c magic.c mbtable.c number.c path.c quad.c regex.c set.c sort.c string.c synonym.c

