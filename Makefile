# ebook2cw Makefile -- Fabian Kurz, DJ5CW -- http://fkurz.net/ham/ebook2cw.html

VERSION=0.8.5
DESTDIR ?= /usr

# Set to NO to compile without Lame/Ogg-vorbis support
USE_LAME?=YES
USE_OGG?=YES

CFLAGS:=$(CFLAGS) -D DESTDIR=\"$(DESTDIR)\" -D VERSION=\"$(VERSION)\"

ifeq ($(USE_LAME), YES)
		CFLAGS:=$(CFLAGS) -D LAME
		LDFLAGS:=$(LDFLAGS) -lmp3lame 
endif
ifeq ($(USE_OGG), YES)
		CFLAGS:=$(CFLAGS) -D OGGV
		LDFLAGS:=$(LDFLAGS) -lvorbis -lvorbisenc -logg
endif

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	LDFLAGS += -lintl
endif

all: ebook2cw

ebook2cw: ebook2cw.c codetables.h
	$(CC) ebook2cw.c -pedantic -Wall -Wno-format-truncation -lm $(LDFLAGS) $(CFLAGS) -o ebook2cw
	msgfmt -o po/de.mo po/de.po

cgi: ebook2cw.c codetables.h
	$(CC) -static ebook2cw.c $(LDFLAGS) -lm $(CFLAGS) -D CGI -o cw.cgi

cgibuffered: ebook2cw.c codetables.h
	$(CC) -static ebook2cw.c $(LDFLAGS) -lm $(CFLAGS) -D CGI -D CGIBUFFERED -o cw.cgi

static:
	$(CC) -static ebook2cw.c $(LDFLAGS) -lm $(CFLAGS) -o ebook2cw

install:
	install -d -v                      $(DESTDIR)/share/man/man1/
	install -d -v                      $(DESTDIR)/bin/
	install -d -v                      $(DESTDIR)/share/doc/ebook2cw/
	install -d -v                      $(DESTDIR)/share/doc/ebook2cw/examples/
	install -d -v                      $(DESTDIR)/share/locale/de/LC_MESSAGES/
	install -s -m 0755 ebook2cw        $(DESTDIR)/bin/
	install    -m 0644 ebook2cw.1      $(DESTDIR)/share/man/man1/
	install    -m 0644 README          $(DESTDIR)/share/doc/ebook2cw/
	install    -m 0644 ebook2cw.conf   $(DESTDIR)/share/doc/ebook2cw/examples/
	install    -m 0644 isomap.txt      $(DESTDIR)/share/doc/ebook2cw/examples/
	install    -m 0644 utf8map.txt     $(DESTDIR)/share/doc/ebook2cw/examples/
	install    -m 0644 po/de.mo        $(DESTDIR)/share/locale/de/LC_MESSAGES/ebook2cw.mo
	
uninstall:
	rm -f $(DESTDIR)/bin/ebook2cw
	rm -f $(DESTDIR)/share/man/man1/ebook2cw.1
	rm -rf $(DESTDIR)/share/doc/ebook2cw

clean:
	rm -f ebook2cw *~ *.mp3 *.ogg *.cgi ebook2cw.exe po/*.mo

dist:
	sed 's/v[0-9].[0-9].[0-9]/v$(VERSION)/g' README > README2
	rm -f README
	mv README2 README
	rm -f releases/ebook2cw-$(VERSION).tar.gz
	rm -rf releases/ebook2cw-$(VERSION)
	mkdir ebook2cw-$(VERSION)
	mkdir ebook2cw-$(VERSION)/po
	cp ebook2cw.c codetables.h ChangeLog ebook2cw.1 \
			ebook2cw.conf isomap.txt utf8map.txt \
			ebook2cw.bat \
			README COPYING Makefile ebook2cw-$(VERSION)
	cp po/*.po ebook2cw-$(VERSION)/po
	tar -zcf ebook2cw-$(VERSION).tar.gz ebook2cw-$(VERSION)
	mv ebook2cw-$(VERSION) releases/
	mv ebook2cw-$(VERSION).tar.gz releases/
	md5sum releases/*.gz > releases/md5sums.txt
	chmod a+r releases/*

