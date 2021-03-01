SRCDIR	= src
BINDIR	= bin
OBJDIR	= $(BINDIR)/obj
LIBDIR  = libs
HDRDIR	= include

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CSRC 	= $(call rwildcard,$(SRCDIR),*.c)
OBJS 	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.c.o, $(CSRC))
LIBS	= $(call rwildcard,$(LIBDIR),*.a)

EXE 	= $(BINDIR)/semu

.DEFAULT-GOAL 	= $(EXE)

WFLAGS 	=\
-pedantic-errors \
-Werror \
-Wall \
-Wextra \
-Wdisabled-optimization

CFLAGS 	= -std=c17 -I$(HDRDIR) -ggdb $(WFLAGS)
LFLAGS	= -lGL -lX11 -pthread

CC		= gcc
LD		= gcc

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	@ echo "[>			CC		$^"
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -c $^ -o $@

$(EXE): $(OBJS)
	@ echo "[>			LD		$@"
	@ mkdir -p $(@D)
	@ $(LD) $(OBJS) $(LIBS) -o $@ $(LFLAGS)

run: $(EXE)
	@ echo "[>			EX		$(EXE)\n\n<+-==--==--==--==-+>"
	@ ./bin/semu

clean:
	@ rm -rf $(EXE) $(OBJDIR) $(BINDIR)