CC = gcc
FLAGS = -c

SOURCE = ./src
BUILDDIR = ./

EXECUTABLE = VGBC
SOURCES = $(wildcard $(SOURCE)/*.c)
OBJECTS = $(patsubst $(SOURCE)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

all: dir $(BUILDDIR)/$(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)
	
$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $< -o $@
	
$(OBJECTS):$(BUILDDIR)/%.o : $(SOURCE)/%.c
	$(CC) $(FLAGS) $< -o $@
	
clean:
	rm -f $(BUILDDIR)/*o $(BUILDDIR)/$(EXECUTABLE)