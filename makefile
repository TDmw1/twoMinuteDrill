# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Object files
OBJ = main.o player.o play_logic.o field_goal.o overtime.o

# Executable name
EXEC = game

# Default target: build the executable
all: $(EXEC)

# Rule to link the object files into the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Rule to compile each .c file into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean up object files and the executable
clean:
	rm -f $(OBJ) $(EXEC)

