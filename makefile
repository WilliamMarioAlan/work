# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude		# -I 是 GCC 和 G++ 编译器的一个选项，用于指定 额外的头文件搜索路径（Include Path）。
LDFLAGS =  # 链接选项

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))
TARGET = ./exec

# Default rule
all: $(TARGET)

# Link step
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile step
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)
		$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean

