# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude		# -I 是 GCC 和 G++ 编译器的一个选项，用于指定 额外的头文件搜索路径（Include Path）。
LDFLAGS =  # 链接选项

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))
TARGET = ./exec

# Default rule
all: $(TARGET)

# Link step
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Compile step
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean


