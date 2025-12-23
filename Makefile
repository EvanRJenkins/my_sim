CC = gcc
LDLIBS = -lm -lraylib
CFLAGS = -Iinclude -Wall -Wextra
SRCS = src/imaginarymath.c src/component.c src/circuit.c src/test.c
TARGET = test_my_sim

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDLIBS)

clean:
	rm -f $(TARGET)
