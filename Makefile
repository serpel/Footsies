CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -L . -lsteam_api
include Rosalila/Sources.mk
ROSALILA_FOOTSIES_SOURCES=RosalilaFootsies/Footsies.cpp RosalilaFootsies/Character.cpp RosalilaFootsies/Stage/Stage.cpp RosalilaFootsies/Stage/Layer.cpp RosalilaFootsies/Move.cpp RosalilaFootsies/Frame.cpp
SOURCES=main.cpp $(ROSALILA_SOURCES) $(ROSALILA_FOOTSIES_SOURCES)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Footsies

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(EXECUTABLE)
