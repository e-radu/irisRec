TARGET = irisRec_v1
CC = gcc
CFLAGS = -Wall -fexceptions -g
LIBS = -lSDL2

.PHONY: default all clean

default: $(TARGET)
all: default

DEPS = irisTop.h irisRec.h sobel.h segIris.h SDL_display.h capturev4l2.h haarEncode.h hamMatching.h hough.h resIris.h
OBJ = irisTop.o irisRec.o sobel.o segIris.o SDL_display.o capturev4l2.o haarEncode.o hamMatching.o hough.o resIris.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJ)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
