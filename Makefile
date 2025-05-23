CC=g++
CFLAGS=-c -Wall

LDFLAGS =  -Wno-deprecated
EX_LDFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated

SOURCES=main.cpp menu.cpp display.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=project 

all: $(EXECUTABLE)
	./$(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@ $(EX_LDFLAGS) $(INSTALLED_DEPS)

main.o: main.cpp menu.h display.h util.h
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(INSTALLED_DEPS)

menu.o: menu.cpp menu.h display.h util.h
	$(CC) $(CFLAGS) $<  $(LDFLAGS) $(INSTALLED_DEPS)

display.o :display.cpp display.h util.h
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(INSTALLED_DEPS)

clean:
	rm *.o project 
