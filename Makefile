PROG:=Woodsman
SRCS:=main.c will_and_die.c tale.c tale_index.c tale_draft.c msbits.c weight.c bits_utils.c X.c string_utils.c bf.c dpf.c
OBJS:=$(SRCS:%.c=%.c.o)
DEPS:=$(SRCS:%.c=%.c.d)
ALLDEP=$(MAKEFILE_LIST_SANS_DEPS)
TARGETS:=all $(PROG) %.c.o %.c.d clean line
NONEED_DEP_TARGETS+=clean line

all: $(PROG)

dpf.c.o: WARNFLAGS+=-Wno-unused-parameter

EXTRA_TARGETS:=$(filter-out $(TARGETS), $(MAKECMDGOALS))
ifneq '$(EXTRA_TARGETS)' ''
 $(error No rule to make target `$(word 1, $(EXTRA_TARGETS))')
else
 # check whether NONEED_DEP_TARGETS are in MAKECMDGOALS
 ifeq '$(filter-out $(NONEED_DEP_TARGETS), $(MAKECMDGOALS))' '$(MAKECMDGOALS)'
  sinclude $(DEPS)
 else
  # if so and there are more than 1 targets in MAKECMDGOALS, it would cause dependency files missing so say error
  ifneq '$(words $(MAKECMDGOALS))' '1'
   $(error Specify only one target if you want to make target that needs no dependency file)
  endif
 endif
endif

MAKEFILE_LIST_SANS_DEPS:=$(filter-out %.c.d, $(MAKEFILE_LIST))

CC:=cc
HEADERFLAGS:=-I.
OPTFLAGS:=-O0 -g
WARNFLAGS:=-ansi -pedantic -Wall -Wextra -Werror -W -Wundef -Wcast-qual -Winline -Wno-long-long -fsigned-char
LINKFLAGS=-lm
RM:=rm -r -f
WC:=wc -c -l

COMPILE.c=$(CC) $(HEADERFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(ADDCFLAGS) $(CFLAGS) -c
COMPILE.dep=$(CC) $(HEADERFLAGS) $(OPTFLAGS) $(WARNFLAGS) $(ADDCFLAGS) $(CFLAGS) -MM -MP -MT $<.o -MF $@
LINK.o=$(CC) $(OPTFLAGS) $(WARNFLAGS) $(LINKFLAGS) $(LDFLAGS)

$(PROG): $(OBJS) $(ALLDEP)
	$(LINK.o) $(OUTPUT_OPTION) $(OBJS)

%.c.o: %.c $(ALLDEP)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

%.c.d: %.c $(ALLDEP)
	$(COMPILE.dep) $<

.PHONY: line
line:
	$(WC) $(SRCS) $(MAKEFILE_LIST_SANS_DEPS)

.PHONY: clean
clean:
	$(RM) $(PROG) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(TOCLEAN)
