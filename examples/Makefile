#
# Makefile
#
# To make all examples, just type 'make' or 'gmake'.
#
# For a specific example, type 'make' or 'gmake' followed by the project,
# such as 'make FindRsrc'.
#
##################################################################

# Directory Information
# In your project, set INC_DIR to something like /usr/local/vxipnp/linux/include
# In your project, LIB_DIR should be unnecessary if there is a link to VISA
INC_DIR  = -I /usr/local/vxipnp/linux/include
LIB_DIR  = 

# Compiler Information
CC       = gcc
CC_FLAGS = -ansi -O1 -D_REENTRANT $(INC_DIR)

# Linker Information
LD       = gcc
LD_FLAGS = $(LIB_DIR)
LD_LIBS  = -lvisa -lc -lpthread

##################################################################

TARGETS=     \
   AsyncIO   \
   AsyncSRQ  \
   AsyncIntr \
   FindRsrc  \
   HighReg   \
   Locking   \
   LowReg    \
   RdWrt     \
   RdWrtSrl  \
   ReserveTrig \
   RouteTrig \
   ShareSys  \
   TCPIP     \
   WaitIntr  \
   WaitSRQ   \
   WaitTrig

.PHONY: $(TARGETS)

all: $(TARGETS)

##################################################################

AsyncIO: GPIB/AsyncIO

AsyncSRQ: GPIB/AsyncSRQ

AsyncIntr: VXI-VME/AsyncIntr

FindRsrc: General/FindRsrc

HighReg: VXI-VME/HighReg

Locking: General/Locking

LowReg: VXI-VME/LowReg

RdWrt: General/RdWrt

RdWrtSrl: Serial/RdWrtSrl

ReserveTrig: PXI/ReserveTrig

RouteTrig: PXI/RouteTrig

ShareSys: VXI-VME/ShareSys

TCPIP: TCPIP/tcpip

WaitIntr: VXI-VME/WaitIntr

WaitSRQ: GPIB/WaitSRQ

WaitTrig: VXI-VME/WaitTrig

clean:
	rm -f General/FindRsrc General/Locking General/RdWrt
	rm -f GPIB/AsyncIO GPIB/AsyncSRQ GPIB/WaitSRQ
	rm -f PXI/ReserveTrig PXI/RouteTrig
	rm -f Serial/RdWrtSrl
	rm -f TCPIP/tcpip
	rm -f VXI-VME/AsyncIntr VXI-VME/HighReg VXI-VME/LowReg VXI-VME/ShareSys VXI-VME/WaitIntr VXI-VME/WaitTrig
	find . -name "*.o" -exec rm -f {} \;

##################################################################

General/FindRsrc: General/FindRsrc.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

General/Locking: General/Locking.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

General/RdWrt: General/RdWrt.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

GPIB/AsyncIO: GPIB/AsyncIO.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

GPIB/AsyncSRQ: GPIB/AsyncSRQ.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

GPIB/WaitSRQ: GPIB/WaitSRQ.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

PXI/ReserveTrig: PXI/ReserveTrig.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

PXI/RouteTrig: PXI/RouteTrig.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

Serial/RdWrtSrl: Serial/RdWrtSrl.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

TCPIP/tcpip: TCPIP/tcpip.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

VXI-VME/AsyncIntr: VXI-VME/AsyncIntr.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

VXI-VME/HighReg: VXI-VME/HighReg.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

VXI-VME/LowReg: VXI-VME/LowReg.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

VXI-VME/ShareSys: VXI-VME/ShareSys.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

VXI-VME/WaitIntr: VXI-VME/WaitIntr.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@

VXI-VME/WaitTrig: VXI-VME/WaitTrig.c
	$(CC) $(CC_FLAGS) -c $< -o $@.o
	$(LD) $(LD_FLAGS) $@.o $(LD_LIBS) -o $@
