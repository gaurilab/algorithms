
# Declaration of variables
CC = g++
CC_FLAGS = -w
# File names
#EXEC = run
SOURCES = $(wildcard *.cpp)
SOURCES += $(wildcard *.cc)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
#$(EXEC): $(OBJECTS)
#	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@


