CC = gcc
CFLAGS = -O0 -Wall -g
ASFLAGS = -g -gstabs
CXXFLAGS = -O0 -Wall -g
LDFLAGS = -g
CSRC = main.c
CCSRC = 
EXE = main
INCGENEXE = nodeIncGen
INC = node.inc
ASRC = makeNode.S printList.S insertIntoList.S 

$(EXE):	$(CSRC:.c=.o) $(ASRC:.S=.o)

$(INC): $(INCGENEXE)
	./$(INCGENEXE) > $@

$(INCGENEXE):	nodeIncGen.c node.h

%.d: %.c
	$(CC) $^ -MM -MF $@

%.d: %.S $(INC)
	$(CC) $^ -MM -MF $@

clean:	
	rm -f $(EXE) $(CSRC:.c=.o) $(ASRC:.S=.o) $(CSRC:.c=.d) $(ASRC:.S=.d) $(INC)

include $(CSRC:.c=.d)
include $(ASRC:.S=.d)
