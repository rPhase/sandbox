CC = gcc
CFLAGS = -O -Wall -g
ASFLAGS = -g -gstabs
CXXFLAGS = -O -Wall -g
LDFLAGS = -g
CSRC = main.c
CCSRC = 
EXE = main
ASRC = link.S

$(EXE):	$(CSRC:.c=.o) $(ASRC:.S=.o)

%.d: %.c
	$(CC) $^ -MM -MF $@

%.d: %.S
	$(CC) $^ -MM -MF $@

clean:	
	rm -f $(EXE) $(CSRC:.c=.o) $(ASRC:.S=.o) $(CSRC:.c=.d) $(ASRC:.S=.d)

include $(CSRC:.c=.d)
include $(ASRC:.S=.d)
