## Compiler
CC=g++
## Linker
LD=$(CC)
## Flags
CPPFLAGS = -Wall -g -DLINUX
LFLAGS = -lglut -L/usr/lib -L/usr/X11R6/lib -lXi -lXmu -lGL -lGLU -lm

TARGETS = $(PROGFILES:.cpp=)

PROGFILES = \
        assn1.cpp \
	line.cpp \
	$(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=): assn1.o line.o
	$(CC) -o assn1 assn1.o line.o ${LFLAGS}

depend :
	makedepend ${PROGFILES}
# DO NOT DELETE
