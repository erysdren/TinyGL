
# compiler and flags
CC ?= gcc
CFLAGS += -pedantic -Wall -Wextra

# debug
ifdef DEBUG
CFLAGS += -g -fsanitize=address,undefined
else
CFLAGS += -O3
endif

# objects
OBJS = api.o list.o vertex.o init.o matrix.o texture.o \
	misc.o clear.o light.o clip.o select.o get.o error.o \
	zbuffer.o zline.o zdither.o ztriangle.o \
	zmath.o image_util.o ostinygl.o msghandling.o \
	arrays.o specbuf.o memory.o glu.o

# include directories
INCLUDES = -I../include

# output lib
LIB = libTinyGL.a

all: clean $(LIB)

$(LIB): $(OBJS)
	rm -f $(LIB)
	ar rcs $(LIB) $(OBJS)

clean:
	rm -f *~ *.o *.a

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $*.c

clip.o: zgl.h zfeatures.h
vertex.o: zgl.h zfeatures.h
light.o: zgl.h zfeatures.h
matrix.o: zgl.h zfeatures.h
list.o: zgl.h opinfo.h zfeatures.h
arrays.c: zgl.h zfeatures.h
specbuf.o: zgl.h zfeatures.h
glx.o: zgl.h zfeatures.h
nglx.o: zgl.h zfeatures.h
zline.o: zgl.h zfeatures.h zline.h
ztriangle.o: zgl.h zfeatures.h ztriangle.h 
