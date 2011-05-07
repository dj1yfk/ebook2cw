CXX = g++

PROGRAM = ebook2cwgui

OBJECTS = $(PROGRAM).o

all:    $(PROGRAM)

$(PROGRAM):
	$(CXX) -static -o $(PROGRAM) main.cpp ebook2cwgui.cpp `/wx/wx-config --libs --cxxflags`
	strip ebook2cwgui.exe

clean:
	rm -f *~ *.mp3 $(PROGRAM).exe

