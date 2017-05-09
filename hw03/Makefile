CXX = g++
CXXFLAGS = -O2 -pedantic -Wall -Wextra -Werror -std=c++11 -Iinclude
LDFLAGS =

EXE = huffman
TEST = huffman_test
SRCDIR = src
BINDIR = bin
TESTDIR = test

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TOBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(TESTDIR)/*.cpp)) $(filter-out $(BINDIR)/main.o, $(OBJECTS))

all: $(EXE) 

test: $(BINDIR) $(TOBJECTS)
	$(CXX) $(TOBJECTS) -o $(TEST) $(LDFLAGS)


$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE) $(TEST)
.PHONY: test
.PHONY: clean all
