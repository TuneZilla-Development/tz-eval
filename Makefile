# Compiler
CC = i686-w64-mingw32-gcc

# Get git version information from git if not provided
ifndef VERSION_COMMIT
VERSION_COMMIT := $(subst g,,$(shell git describe --long --dirty --tags | awk '{print $3}'))
endif

ifndef VERSION_COMMIT_FULL
VERSION_COMMIT_FULL := $(shell git rev-parse HEAD)
endif

ifndef VERSION_DIRTY
VERSION_DIRTY := $(if $(findstring dirty,$(shell git describe --long --dirty --tags)),1,0)
endif

# Version defines
#  VERSION_COMMIT		= The shortened commit hash
#  VERSION_COMMIT_FULL	= The full commit hash
#  VERSION_DIRTY		= The state of the repository (1=Uncommited changes, 0=Clean)
VDEFS = -DVERSION_COMMIT="\"$(VERSION_COMMIT)\"" -DVERSION_COMMIT_FULL="\"$(VERSION_COMMIT_FULL)\"" -DVERSION_DIRTY=$(VERSION_DIRTY)

# Compiler flags
CFLAGS = 

# Source files
SRC = src/client.c src/tasks.c src/lib/log.c src/lib/msg.c

# Object files directory
OBJDIR = build

# Object files
OBJ = $(SRC:src/%.c=$(OBJDIR)/%.o)

# Output executable
TARGET = client.exe

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	echo $(CFLAGS)
	echo $(VDEFS)
	$(CC) -Wall -I src/lib $(CFLAGS) $(VDEFS) -o $@ $^

# Rule to build object files
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) -Wall -I src/lib $(CFLAGS) $(VDEFS) -c $< -o $@

# Ensure the build directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)/lib

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)
	rm -rf $(OBJDIR)

run: all
	./$(TARGET)

.PHONY: all clean
