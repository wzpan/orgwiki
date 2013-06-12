objects = lines.o pointsz.o lstrips.o linesw.o lstipple.o

CFLAG = -lGL -lglut

CC = g++

all: $(objects)

$(objects): %.o: %.cpp
	$(CC) $(CFLAG) $< -o $@
	optirun ./$@

clean:
	-rm *.o

