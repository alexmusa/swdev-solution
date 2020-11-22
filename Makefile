CC=g++
CFLAGS=-O2 -I$(INCL_DIR) -std=c++14

BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj

INCL_DIR=include
LIB_DIR=lib
SRC_DIR=src

LIBS=-lm


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCL_DIR)/%.h
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $(wildcard $^) $(CFLAGS)

$(BUILD_DIR)/main: $(patsubst %,$(OBJ_DIR)/%,main.o)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: $(BUILD_DIR)/main
	

.PHONY: clean %.exe
.DEFAULT_GOAL := all

clean:
	rm -f $(OBJ_DIR)/*.o *~ core $(INCL_DIR)/*~ 


%.cpp:
	:

$(INCL_DIR)/%.h:
	:
