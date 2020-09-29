# Name of the library in all lowercase letters
PROG = cmenu

# Directories
SRC = src
HED = include
BIN = bin
VPATH := $(SRC):$(HED):$(BIN)

# Files
LIB = lib$(PROG).so
SRCS := $(wildcard $(SRC)/*.c)
HEDS := $(wildcard $(HED)/*.h)
OBJS := $(addprefix $(BIN)/,$(notdir $(SRCS:%.c=%.o)))

# Compilation options
CFLAGS := -std=c99 -Wall -Wpedantic -I$(SRC) -I$(HED) -I$(BIN) -O2

VALFLAGS := --leak-check=full --track-origins=yes --show-leak-kinds=all


##############
# Make Rules #
##############
.PHONY: all $(PROG) clean move runexample

all: $(PROG) move example

$(PROG): $(LIB)

$(LIB): $(OBJS) | $(BIN)
	gcc -g -shared $(OBJS) -o $(BIN)/$(LIB)

$(BIN)/%.o: $(SRC)/%.c $(HED)/%.h | $(BIN)
	gcc -g $(CFLAGS) -c -fpic $< -o $@

example: example_src/example.c $(LIB)
	gcc -g -L/home/joseph/lib $(CFLAGS) $< -l$(PROG) -o $@

runexample: example
	valgrind $(VALFLAGS) ./example


#############
# Utilities #
#############

clean:
	rm -f ../$(LIB) $(BIN)/*.o $(BIN)/$(LIB) $(TESTS)

move:
	mv $(BIN)/$(LIB) ../

$(BIN):
	mkdir -p $@

echo:
	@echo "Test Dir = $(TEST_DIR)"
	@echo "Tests    = $(TESTS)"

