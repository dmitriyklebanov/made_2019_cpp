#Compiler and Linker
CC          := g++

# Decide whether the commands will be shwon or not
VERBOSE = TRUE

#The Directories, Source, Includes, Objects, Binary
SRCDIR      := src
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

#The Target Binary Program Sources
TARGETS_SOURCES := $(SRCDIR)/format/.tests/format_tests.cpp

#Flags, Libraries and Includes
CFLAGS      := -fopenmp -Wall -std=c++14 -g
LIB         := -fopenmp -lm
INC         := -I $(SRCDIR) -I /usr/local/include
INCDEP      := -I $(SRCDIR)

#---------------------------------------------------------------------------------
#Internal targets ans variables
#---------------------------------------------------------------------------------

FIND_EXCEPT_TARGETS = $(foreach filename, $(TARGETS_SOURCES), $(addprefix ! -wholename , $(filename)))
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT) $(FIND_EXCEPT_TARGETS))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
TARGETS_OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(TARGETS_SOURCES:.$(SRCEXT)=.$(OBJEXT)))
TARGETS_BINARIES := $(patsubst $(SRCDIR)/%,$(TARGETDIR)/%,$(TARGETS_SOURCES:.$(SRCEXT)=))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =
else
    HIDE = @
endif

#Defauilt Make
all: $(TARGETS_BINARIES)

#Remake
remake: cleaner all

#Make the Directories
directories:
	$(HIDE) @mkdir -p $(TARGETDIR)
	$(HIDE) @mkdir -p $(BUILDDIR)

#Clean only Objects
clean:
	$(HIDE) @$(RM) -rf $(BUILDDIR)

#Full Clean, Objects and Binaries
cleaner: clean
	$(HIDE) @$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))
-include $(TARGETS_OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	$(HIDE) echo Compiling $@
	$(HIDE) @mkdir -p $(dir $@)
	$(HIDE) $(CC) $(CFLAGS) $(INC) -c -o $@ $<
	$(HIDE) @$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	$(HIDE) @cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	$(HIDE) @sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	$(HIDE) @sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	$(HIDE) @rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Build
$(TARGETS_BINARIES): $(OBJECTS) $(TARGETS_OBJECTS)
	$(HIDE) echo Building $@
	$(HIDE) @mkdir -p $(dir $@)
	$(HIDE) $(CC) $(CFLAGS) $(INC) -o $@ $(patsubst $(TARGETDIR)/%,$(BUILDDIR)/%,$@.$(OBJEXT)) $(OBJECTS)

#Non-File Targets
.PHONY: all remake clean cleaner

#---------------------------------------------------------------------------------
#Custom targets
#---------------------------------------------------------------------------------

test: bin/format/.tests/format_tests
	./bin/format/.tests/format_tests
