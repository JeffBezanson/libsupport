SRCS = hashing.c timefuncs.c ptrhash.c socket.c \
	utf8.c ios.c dirpath.c htable.c bitvector.c bitvector-ops.c \
	int2str.c dump.c libsupportinit.c arraylist.c

OBJS = $(SRCS:%.c=%.o)
DOBJS = $(SRCS:%.c=%.do)

ifneq ($(MAKECMDGOALS),debug)
XOBJS = $(OBJS)
else
XOBJS = $(DOBJS)
endif

FLAGS = -std=gnu99 -fPIC -Wall -Wno-strict-aliasing $(CFLAGS)

DEBUGFLAGS = -ggdb3 -DDEBUG
SHIPFLAGS = -O3 -DNDEBUG -falign-functions -momit-leaf-frame-pointer

DEBUGFLAGS += $(FLAGS)
SHIPFLAGS += $(FLAGS)

default: release

%.o: %.c
	$(CC) $(SHIPFLAGS) -c $< -o $@
%.do: %.c
	$(CC) $(DEBUGFLAGS) -c $< -o $@

release debug: libsupport.a

libsupport.a: $(XOBJS)
	rm -rf $@
	ar -rcs $@ $^

clean:
	rm -f *.o
	rm -f *.do
	rm -f *.a
	rm -f *~ *#
	rm -f core*
	rm -f libsupport.a
