# @(#) Make documentation
# $Id: Makefile,v 1.1.1.1 2007-12-20 15:53:44 wingorodov Exp $

.PHONY: all

DOXYGEN= /usr/local/bin/doxygen

all:
	${DOXYGEN}
	make -C html

clean:
	make -C html clean
