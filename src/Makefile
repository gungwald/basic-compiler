# Builds BASIC compiler: basiccomp

# Requirements:
# 1. Gmake must be used
# 2. The cc65 compiler must be properly setup
# 3. The AppleWin emulator is required for testing

ifndef CC65_TARGET
	CC65_TARGET:=apple2enh
endif

ifeq ($(OS),Windows_NT)
    COPY=copy
else
    COPY=cp
endif

PGM=basiccomp
DISK_VOL=$(PGM)
DISK=$(PGM).dsk
BASE_DISK=../storage/prodos-2.0.3-boot.dsk
AC=java -jar ../lib/AppleCommander-ac-1.4.0.jar

CC=cl65
AS=ca65
OBJS=$(PGM).o binarytree.o
HDRS=binarytree.h
CFLAGS=-O -t $(CC65_TARGET) -DTRACE
LDFLAGS=-t $(CC65_TARGET) # -S $6000 to make both hi-res pages available

# Extra stuff
BASIC_AUX_TYPE=0x0801
READ_TIME_LOAD_ADDR=0x0260
SYS_LOAD_ADDR=0x2000
BIN_LOAD_ADDR=0x0803

########################################

all: $(DISK)

$(DISK): $(PGM)
	$(RM) $(DISK)
	$(COPY) $(BASE_DISK) $(DISK)
	$(AC) -as $(DISK) BC BIN < $(PGM) || $(RM) $(DISK)

$(PGM): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

test: $(DISK)
	applewin -d1 $(DISK)
	#$(APPLEWIN) -s7 empty -d1 $(DISK)

clean:
	$(RM) *.o $(PGM) $(DISK)
