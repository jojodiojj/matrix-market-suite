CC=			gcc
CFLAGS=			-g -Wall -Wno-unused-function -O2 
WRAP_MALLOC=		-DUSE_MALLOC_WRAPPERS
DFLAGS=			-DHAVE_PTHREAD $(WRAP_MALLOC)

PROG=			MM-Suite

SUBDIRS= io operations utils

SUBCLEAN = $(addsuffix .clean,$(SUBDIRS))

OBJECTS= io/CreateDenseMatrixSymmetric.o io/CreateDenseVector.o \
	utils/utils.o utils/mmio.o operations/DMxV.o

LIBS = -lblas
INCLUDES =

.PHONY: all

.SUFFIXES:.c .o .cc

.c.o:
	$(CC) -c $(CFLAGS) $(DFLAGS) $(INCLUDES) $< -o $@

all:$(PROG)
	

.PHONY: subdirs $(SUBDIRS)
.PHONY: clean $(SUBCLEAN)

subdirs: $(SUBDIRS)


$(SUBDIRS):
	$(MAKE) -C $@
	
MM-Suite: MM-Suite.o subdirs
	$(CC) $(CFLAGS) $(DFLAGS) $(AOBJS) MM-Suite.o $(OBJECTS) -o $@  $(LIBS)


clean: $(SUBCLEAN)
	rm $(PROG) *.o

$(SUBCLEAN): %.clean:
	$(MAKE) -C $* clean
