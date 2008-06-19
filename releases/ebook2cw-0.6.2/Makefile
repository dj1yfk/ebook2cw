# ebook2cw Makefile -- Fabian Kurz, DJ1YFK -- http://fkurz.net/ham/ebook2cw.html

VERSION=0.6.2
DESTDIR ?= /usr

all: ebook2cw

ebook2cw: ebook2cw.c
	gcc ebook2cw.c -pedantic -Wall -lm -lmp3lame -D VERSION=\"$(VERSION)\" -o ebook2cw

static:
	gcc -static ebook2cw.c -lmp3lame -lm -D VERSION=\"$(VERSION)\" -o ebook2cw

install:
	install -d -v                  $(DESTDIR)/share/man/man1/
	install -d -v                  $(DESTDIR)/bin/
	install -s -m 0755 ebook2cw    $(DESTDIR)/bin/
	install    -m 0644 ebook2cw.1  $(DESTDIR)/share/man/man1/
	
uninstall:
	rm -f $(DESTDIR)/bin/ebook2cw
	rm -f $(DESTDIR)/share/man/man1/ebook2cw.1

clean:
	rm -f ebook2cw *~ *.mp3

dist:
	sed 's/v[0-9].[0-9].[0-9]/v$(VERSION)/g' README > README2
	rm -f README
	mv README2 README
	rm -f releases/ebook2cw-$(VERSION).tar.gz
	rm -rf releases/ebook2cw-$(VERSION)
	mkdir ebook2cw-$(VERSION)
	cp ebook2cw.c codetables.h ChangeLog ebook2cw.1 \
			README COPYING Makefile ebook2cw-$(VERSION)
	tar -zcf ebook2cw-$(VERSION).tar.gz ebook2cw-$(VERSION)
	mv ebook2cw-$(VERSION) releases/
	mv ebook2cw-$(VERSION).tar.gz releases/
	md5sum releases/*.gz > releases/md5sums.txt
	chmod a+r releases/*

