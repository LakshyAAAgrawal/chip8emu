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
LLVMBCTARGET := llvm/linked/c8emu.bc
LLVMBINTARGET := llvm/linked/c8emu
LLVMINTERMEDIATE := $(patsubst $(SRCDIR)/%,$(LLVMBUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
LLVMCC := wllvm++
LLVMLINKER := wllvm++
LLVMCFLAGS := $(CFLAGS)
WLLVMEXTRACTBC := extract-bc
LLVMDECOMP := llvm-dis
export LLVM_COMPILER=clang

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

llvm: $(LLVMTARGET)

$(LLVMTARGET): $(LLVMINTERMEDIATE)
	@mkdir -p $(LLVMTARGETDIR)
	@echo " Linking..."
	@echo " $(LLVMLINKER) -o $(LLVMBINTARGET) $(LIB) $^"; $(LLVMLINKER) -o $(LLVMBINTARGET) $(LIB) $^
	@echo " $(WLLVMEXTRACTBC) $(LLVMBINTARGET)"; $(WLLVMEXTRACTBC) $(LLVMBINTARGET)
	@echo " $(LLVMDECOMP) $(LLVMBCTARGET) -o $(LLVMTARGET)"; $(LLVMDECOMP) $(LLVMBCTARGET) -o $(LLVMTARGET)

$(LLVMBUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(LLVMBUILDDIR)
	@echo " $(LLVMCC) $(LLVMCFLAGS) $(INC) -c -o $@ $<"; $(LLVMCC) $(LLVMCFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(LLVMBUILDDIR) $(LLVMTARGETDIR)"; $(RM) -r $(BUILDDIR) $(TARGET) $(LLVMBUILDDIR) $(LLVMTARGETDIR)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
