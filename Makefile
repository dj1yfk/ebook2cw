# ebook2cwgui Makefile, Fabian Kurz, DJ1YFK, http://fkurz.net/ham/ebook2cw.html
#
# $Id$

VERSION=0.1.0
DESTDIR ?= /usr

all: ebook2cwgui

ebook2cwgui:
	g++ ebook2cwgui.cpp main.cpp \
	       	-Wall `wx-config --libs --cxxflags` -o ebook2cwgui

win32:
	g++ -static ebook2cwgui.cpp main.cpp \
	       	-Wall `/wx/wx-config --libs --cxxflags` -o ebook2cwgui

install:
	install -d -v                      $(DESTDIR)/bin/
	install -d -v                      $(DESTDIR)/share/man/man1/
	install -s -m 0755 ebook2cwgui     $(DESTDIR)/bin/
	install    -m 0644 ebook2cwgui.1   $(DESTDIR)/share/man/man1/
	
uninstall:
	rm -f $(DESTDIR)/bin/ebook2cwgui
	rm -f $(DESTDIR)/share/man/man1/ebook2cwgui.1

clean:
	rm -f ebook2cwgui ebook2cwgui.exe *~ *.mp3 *.ogg

dist:
	sed 's/v[0-9].[0-9].[0-9]/v$(VERSION)/g' README > README2
	rm -f README
	mv README2 README
	rm -f releases/ebook2cwgui-$(VERSION).tar.gz
	rm -rf releases/ebook2cwgui-$(VERSION)
	mkdir ebook2cwgui-$(VERSION)
	cp ebook2cwgui.cpp ebook2cwgui.h main.cpp main.h ChangeLog \
		ebook2cwgui.1 README COPYING Makefile \
		ebook2cwgui-$(VERSION)
	tar -zcf ebook2cwgui-$(VERSION).tar.gz ebook2cwgui-$(VERSION)
	mv ebook2cwgui-$(VERSION) releases/
	mv ebook2cwgui-$(VERSION).tar.gz releases/
	md5sum releases/*.gz > releases/md5sums.txt
	chmod a+r releases/*

