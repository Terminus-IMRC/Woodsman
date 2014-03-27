PROG=Woodsman
SRCS=main.c will_and_die.c tale.c tale_index.c tale_draft.c msbits.c weight.c bits_utils.c X.c string_utils.c
OBJS=$(SRCS:%.c=%.c.o)
ALLDEP=$(MAKEFILE_LIST)

all: $(PROG)

CC:=cc
HEADERFLAGS:=-I.
OPTFLAGS:=-O0 -g
WARNFLAGS:=-ansi -pedantic -Wall -Wextra -W -Wundef -Wcast-qual -Winline -Wno-long-long -fsigned-char
LINKFLAGS=-lm
RM:=rm -r -f
WC:=wc -c -l

COMPILE.c=$(CC) $(HEADERFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(DEPFLAGS) $(ADDCFLAGS) $(CFLAGS) -c
LINK.o=$(CC) $(OPTFLAGS) $(WARNFLAGS) $(LINKFLAGS) $(LDFLAGS)

$(PROG): $(OBJS) $(ALLDEP)
	$(LINK.o) $(OUTPUT_OPTION) $(OBJS)

%.c.o: %.c $(ALLDEP)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

run: $(PROG)
	./$(PROG)

.PHONY: line
line:
	$(WC) $(SRCS) $(MAKEFILE_LIST)

.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJS)
	$(RM) $(TOCLEAN)
