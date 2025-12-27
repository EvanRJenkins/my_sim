CC = gcc
LDLIBS = -lm -lraylib
CFLAGS = -g -Iinclude -Wall -Wextra
SRCS = src/circuit.c src/functionlut.c src/nodelut.c src/msnlparser.c src/nodesolve.c src/test.c
TARGET = test_my_sim

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDLIBS)

clean:
	rm -f $(TARGET)
