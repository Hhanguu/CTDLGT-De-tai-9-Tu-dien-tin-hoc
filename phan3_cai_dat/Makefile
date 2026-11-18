CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic
TARGET   = tudien
TARGET_1000 = tudien_1000
SRCDIR   = src
INCDIR   = include

SRCS = $(SRCDIR)/main.cpp \
       $(SRCDIR)/HashTable.cpp \
       $(SRCDIR)/FileIO.cpp \
       $(SRCDIR)/Menu.cpp

OBJS = $(SRCS:.cpp=.o)

SRCS_1000 = $(SRCDIR)/main_1000.cpp \
            $(SRCDIR)/HashTable.cpp \
            $(SRCDIR)/FileIO.cpp \
            $(SRCDIR)/Menu.cpp

OBJS_1000 = $(SRCS_1000:.cpp=.o)

BENCH_TARGET = benchmark
BENCH_SRCS   = bench/benchmark.cpp
BENCH_OBJS   = $(BENCH_SRCS:.cpp=.o)

all: $(TARGET) $(TARGET_1000)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_1000): $(SRCDIR)/main_1000.o $(SRCDIR)/HashTable.o $(SRCDIR)/FileIO.o $(SRCDIR)/Menu.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Benchmark chi can HashTable + FileIO, khong keo theo main/menu
bench: $(BENCH_TARGET)

$(BENCH_TARGET): $(BENCH_OBJS) $(SRCDIR)/HashTable.o $(SRCDIR)/FileIO.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c -o $@ $<

bench/%.o: bench/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/*.o bench/*.o $(TARGET) $(TARGET_1000) $(BENCH_TARGET)

.PHONY: all bench clean
