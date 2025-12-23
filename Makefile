CC = gcc
LDLIBS = -lm -lraylib
CFLAGS = -Iinclude -Wall -Wextra
SRCS = src/imag.c src/comp.c src/test.c
TARGET = test_my_sim

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDLIBS)

clean:
	rm -f $(TARGET)
