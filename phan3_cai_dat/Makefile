CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
TARGET   = tudien
SRCDIR   = src
INCDIR   = include

SRCS = $(SRCDIR)/main.cpp \
       $(SRCDIR)/HashTable.cpp \
       $(SRCDIR)/FileIO.cpp \
       $(SRCDIR)/Menu.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c -o $@ $<

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

.PHONY: all clean
