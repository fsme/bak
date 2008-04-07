#
#
# $Id$

CXXFLAGS +=\
	-ggdb3\
	-I/usr/local/include\
	-I/usr/local/include/libcxx\
	-L/usr/local/lib

LDLIBS +=\
	-lcxx\
	-lmemcache

PROGS= bak

all: $(PROGS)

BAKSRC = bak.cc buffer.hpp

bak:  $(BAKSRC)
	$(CXX) $(CXXFLAGS) $@.cc $(LDLIBS) -o $@

clean clear:
	rm -rfv *.core $(PROGS)

