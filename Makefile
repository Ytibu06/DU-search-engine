CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra -g

# Directories
SRCDIR = src
INCDIR = include
TESTDIR = test

# Include paths
INCLUDES = -I$(INCDIR) -I$(INCDIR)/cppjieba -I$(INCDIR)/simhash

# Source files and test files
TEST_FILES = $(TESTDIR)/simhash.cc

# Binary output paths
TEST_TARGETS = $(TESTDIR)/simhash_test

.PHONY: all test clean run-simhash

all: test

test: $(TEST_TARGETS)

$(TESTDIR)/simhash_test: $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $<

clean:
	rm -f $(TESTDIR)/*.o $(TEST_TARGETS)

run-simhash:
	cd /home/du/work/devProject/SearchEngine && ./test/simhash_test
