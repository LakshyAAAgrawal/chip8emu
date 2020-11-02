# Makefile and project structure used from - https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
CC := g++ # This is the main compiler
#CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := bin/c8emu
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -Werror -std=c++11
LIB := # -lncurses -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
INC := -I include

LLVMBUILDDIR := llvm/build
LLVMTARGETDIR := llvm/linked
LLVMTARGET := llvm/linked/c8emu.ll
LLVMINTERMEDIATE := $(patsubst $(SRCDIR)/%,$(LLVMBUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.ll))
LLVMCC := clang
LLVMLINKER := llvm-link
LLVMCFLAGS := $(CFLAGS) -fpic -fpie -fPIE -fPIC

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

llvm: $(LLVMINTERMEDIATE)
	@mkdir -p $(LLVMTARGETDIR)
	@echo " Linking..."
	@echo " $(LLVMLINKER) -S -v -o $(LLVMTARGET) $(LIB) $^"; $(LLVMLINKER) -S -v -o $(LLVMTARGET) $(LIB) $^

$(LLVMBUILDDIR)/%.ll: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(LLVMBUILDDIR)
	@echo " $(LLVMCC) $(LLVMCFLAGS) $(INC) -S -emit-llvm -o $@ $<"; $(LLVMCC) $(LLVMCFLAGS) $(INC) -S -emit-llvm -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(LLVMBUILDDIR) $(LLVMTARGET)"; $(RM) -r $(BUILDDIR) $(TARGET) $(LLVMBUILDDIR) $(LLVMTARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
