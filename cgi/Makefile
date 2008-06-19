# cw-cgi Makefile -- Fabian Kurz, DJ1YFK 

VERSION=0.0.1
DESTDIR ?= /usr

all: cw-cgi

cw-cgi: cw-cgi.c codetables.h
	gcc cw-cgi.c -pedantic -Wall -lm -lmp3lame -D VERSION=\"$(VERSION)\" -o cw-cgi

static:
	gcc -static cw-cgi.c -lmp3lame -lm -D VERSION=\"$(VERSION)\" -o cw-cgi

clean:
	rm -f cw-cgi *~

dist:
	sed 's/v[0-9].[0-9].[0-9]/v$(VERSION)/g' README > README2
	rm -f releases/cw-cgi-$(VERSION).tar.gz
	rm -rf releases/cw-cgi-$(VERSION)
	mkdir cw-cgi-$(VERSION)
	cp cw-cgi.c codetables.h ChangeLog cw-cgi.1 \
			README COPYING Makefile cw-cgi-$(VERSION)
	tar -zcf cw-cgi-$(VERSION).tar.gz cw-cgi-$(VERSION)
	mv cw-cgi-$(VERSION) releases/
	mv cw-cgi-$(VERSION).tar.gz releases/
	md5sum releases/*.gz > releases/md5sums.txt
	chmod a+r releases/*

