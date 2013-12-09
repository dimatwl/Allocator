CC=g++
CFLAGS=-Wall

SOURCES = main.cpp buffer_allocator.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
DEPS = make.dep
TARGET = executable

RM=rm -f

all: $(TARGET) $(clean_after_build)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -pg $< 


$(DEPS): $(SOURCES)
	$(CC) -MM $(SOURCES) > $(DEPS)

-include $(DEPS)

clean_after_build:
	$(RM) $(OBJECTS) $(DEPS)

clean:
	$(RM) $(OBJECTS) $(TARGET) $(DEPS)