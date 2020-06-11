CC		:= g++
# C_FLAGS := -std=c++17 -Wall -Wextra  -g
C_FLAGS := -std=c++17 -Wall -Wextra -static-libstdc++ -static-libgcc -g
BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lglad -lglfw3dll

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

PYTHON := E:\Users\29444\AppData\Local\Programs\Python\Python38\include


$(BIN)/$(EXECUTABLE): $(SRC)/main.cpp particle.o texture.o water.o math.o background.o rock.o metaball.o
	$(CC) $(C_FLAGS) -I$(INCLUDE) -I$(PYTHON) -L$(LIB)  $^ -o $@ lib\python38.lib $(LIBRARIES)

particle.o : $(SRC)/particle.cpp $(INCLUDE)/particle.h
	$(CC) $(C_FLAGS) -I$(INCLUDE)  $^ -c 

texture.o : $(SRC)/texture.cpp $(INCLUDE)/texture.h
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -c

water.o: $(SRC)/water.cpp $(INCLUDE)/water.h
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -c

math.o: $(SRC)/Math.cpp 
	$(CC) $(C_FLAGS) $^ -c

background.o : $(SRC)/background.cpp $(INCLUDE)/background.h
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -c

rock.o : $(SRC)/rock.cpp $(INCLUDE)/rock.h
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -c

metaball.o : $(SRC)/metaball.cpp $(INCLUDE)/metaball.h
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -c