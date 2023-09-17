CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=test_function.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=application.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
