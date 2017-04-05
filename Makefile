BIN_NAME = list

CC = gcc
CPPCHECK = cppcheck
STD = c99

SRC_EXT = c

SRC_PATH = ./
DEST_PATH = ./bin
CPPC_SUPRESS = ./cppchecksupression.txt

COMPILE_FLAGS = -std=$(STD) -Wall -Wextra -Wshadow -pedantic
CPPC_FLAGS = --enable=all --suppressions-list=$(CPPC_SUPRESS) \
							--inconclusive --std=$(STD)

SRC = $(wildcard $(SRC_PATH)*.$(SRC_EXT))

all: check compile

compile:
	$(CC) -o $(DEST_PATH)/$(BIN_NAME) $(SRC) $(COMPILE_FLAGS)
	
check:
	$(CPPCHECK) $(CPPC_FLAGS) $(SRC)

clean:
	rm $(DEST_PATH)/$(BIN_NAME)
