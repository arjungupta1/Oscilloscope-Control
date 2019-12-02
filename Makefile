#################################
# def compile/linker flags/opts
CXX:= g++
CSTD:= -std=c++11
OPT:= -O0

# initial cflag and library linking 
CFLAGS:= $(CSTD) $(OPT) -Wall -D_GNU_SOURCE -g
LDLIBS:= -lvisa -lc -lpthread
INC_FLAGS = -I /usr/local/vxipnp/linux/include

#############################
RM= rm -rf
MKDIR= mkdir -p
#############################

# Linking protobuf 

# folders
OBJDIR	 = obj
BUILDDIR = build
SRCDIR   = src
LIBDIR   = lib 
TESTDIR  = test

INC_FLAGS += -I$(LIBDIR)
CFLAGS += $(INC_FLAGS)

# src, obj, and programs
SRCS= $(wildcard $(SRCDIR)/*.cpp)	
OBJS=$(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# # define top level for testbenches
# TESTBENCH_IMGACQ  = img_acquire_testbench
# TESTBENCH_LIMPING = img_limping_testbench
# TESTBENCH_IMGPROC = img_process_testbench

TESTSRCS  = $(wildcard $(TESTDIR)/*.cpp)
TESTOBJS  = $(TESTSRCS:$(TESTDIR)/%.cpp=$(OBJDIR)/$(TESTDIR)/%.o)
TESTPROGS = $(TESTSRCS:$(TESTDIR)/%.cpp=$(BUILDDIR)/%)

#############################
.PHONY: all build binaries clean dir setup

all: setup build binaries

# dir $(OBJS) $(TESTOBJS) $(TESTPROGS) # $(BUILDDIR)/$(TESTBENCH_IMGPROC)

setup: dir $(PROTOOBJ)
build: setup $(OBJS) $(TESTOBJS) 
binaries: build $(TESTPROGS)

dir:
	$(MKDIR) $(BUILDDIR) $(OBJDIR) $(OBJDIR)/$(TESTDIR)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ 

$(TESTOBJS): $(OBJDIR)/%.o : %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ 

$(TESTPROGS): $(BUILDDIR)/%: $(OBJS)
	$(CXX) $(CFLAGS) $(TESTDIR)/$*.cpp $^ $(PROTOOBJ)  -o $@ $(LDLIBS) 


ip-pipeline: dir test/ip-pipeline.cpp
	$(CXX) -g test/ip-pipeline.cpp -o $(BUILDDIR)/$@
	./$(BUILDDIR)/$@ 2>&1 | tee test-data/debuglog.txt


clean:
	$(RM) $(BUILDDIR) $(OBJDIR)





# LIB_FILE_NAME = libADC.so

# .PHONY: all shared static clean

# all:

# shared:

# static:

# clean:



