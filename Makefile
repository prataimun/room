CC=g++-4.9
CXX=g++-4.9

CXX_FLAGS=-std=c++14 -Wall
LD_FLAGS= -lglut -lGL -lGLU

INC_PATH=inc
SRC_PATH=src
OBJ_PATH=obj
LIB_PATH=lib
BIN_PATH=bin

OBJ=$(OBJ_PATH)/main.o $(OBJ_PATH)/room.o $(OBJ_PATH)/person.o

$(BIN_PATH)/room : $(OBJ)
	$(CXX) -o $(BIN_PATH)/room $(OBJ) $(LD_FLAGS)

$(OBJ_PATH)/main.o : $(SRC_PATH)/main.cpp $(INC_PATH)/room.h $(INC_PATH)/person.h
	$(CXX) -c $(CXX_FLAGS) -I$(INC_PATH) $(SRC_PATH)/main.cpp -o $(OBJ_PATH)/main.o
$(OBJ_PATH)/room.o : $(SRC_PATH)/room.cpp $(INC_PATH)/room.h
	$(CXX) -c $(CXX_FLAGS) -I$(INC_PATH) $(SRC_PATH)/room.cpp -o $(OBJ_PATH)/room.o
$(OBJ_PATH)/person.o : $(SRC_PATH)/person.cpp $(INC_PATH)/person.h
	$(CXX) -c $(CXX_FLAGS) -I$(INC_PATH) $(SRC_PATH)/person.cpp -o $(OBJ_PATH)/person.o

clean:
	rm -f $(OBJ_PATH)/*.o

cleanall: clean
	rm -f $(BIN_PATH)/room
