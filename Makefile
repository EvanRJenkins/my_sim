CC = gcc
LDLIBS = -lm -lraylib
CFLAGS = -Iinclude -Wall -Wextra
SRCS = src/component.c src/circuit.c src/line.c src/functiontable.c src/msnlparser.c src/test.c
TARGET = test_my_sim

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDLIBS)

clean:
	rm -f $(TARGET)
