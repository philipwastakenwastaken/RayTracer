TARGET = main
LIBS = 
CC = g++
OBJDIR = obj
SRCDIR = src
CFLAGS = -g -O3 -Wall -std=c++17
VPATH = src

.PHONY: default all clean

default: $(TARGET)
all: default

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard $(SRCDIR)/*.h)
OBJECTS = $(subst $(SRCDIR), $(OBJDIR), $(SOURCES:.cpp=.o))

print-%  : ; @echo $* = $($*) # for printing variables. ex usage: make print-SOURCES

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

clean:
	-rm -f $(OBJDIR)/*.o
	-rm -f $(TARGET)

run: main
	./main