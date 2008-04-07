# @(#) Set HTML documentation
# $Id: Makefile,v 1.1.1.1 2007-12-20 15:53:44 wingorodov Exp $

.PHONY: all install clean 

BASE= libcxx
WEBDIR= /usr/local/share/src/${BASE}
INSTALL= install -m 644

all:
	@echo "What?"

install:
	@rm -rfv ${WEBDIR}/*
	@ls *.html *.png *.css *.gif | while read FILE; \
	do\
		${ECHO} "${INSTALL} $$FILE ${WEBDIR}" ;\
		${INSTALL} $$FILE ${WEBDIR} ;\
	done;

clean clear:
	rm -rfv *.html class*.png struct*.png *.gif tabs.css
