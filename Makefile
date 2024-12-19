CC = gcc
CFLAGS = -Wall -g
OBJ = Creature.o Item.o Player.o Room.o Main.o GameCommands.o MenuCommands.o
TARGET = game.exe

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /f /q $(OBJ) $(TARGET)

rebuild: clean $(TARGET)