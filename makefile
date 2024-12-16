CC = gcc
CFLAGS = `pkg-config --cflags gtk4` -Wall -Wextra -g
LIBS = `pkg-config --libs gtk4`

SRC = src/main.c src/ui.c src/contact_manager.c src/diary_manager.c src/notifications.c src/utils.c
OBJ = $(SRC:.c=.o)
TARGET = build/connect_track_pro

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
