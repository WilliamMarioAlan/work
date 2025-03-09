# Compiler and flags
CXX = g++                         # 用于编译 .cpp 文件
CC = gcc                          # 用于编译 .c 文件
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude   # C++ 编译选项
CFLAGS = -std=c11 -Wall -Wextra -g -Iinclude       # C 编译选项
LDFLAGS =                         # 链接选项

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Files
CXX_SOURCES = $(wildcard $(SRCDIR)/*.cpp)    # 查找所有 .cpp 文件
C_SOURCES = $(wildcard $(SRCDIR)/*.c)        # 查找所有 .c 文件
CXX_OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(CXX_SOURCES))
C_OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(C_SOURCES))
OBJECTS = $(CXX_OBJECTS) $(C_OBJECTS)

TARGET = ./exec

# Default rule
all: $(TARGET)

# Link step
$(TARGET): $(OBJECTS)
	@$(CXX) $(LDFLAGS) -o $@ $^

# Compile C++ files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	@rm -rf $(BUILDDIR) $(TARGET)

rebuild:clean all

.PHONY: all clean rebuild
