# Usage:
# 	make run year=2025 day=10
# 	Current year: make run day=2
# 	Current day: make run
# 	To use O2: make profile ...
# 	To use O3: make profileMax ...
# 	make clean

#	To use tests, add test=1

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

year ?= $(shell date +%Y)
day ?= $(shell date +%-d)

output := $(year)/output/day$(day)
src := $(year)/day$(day)/day$(day).cpp
helper := utils/helper.cpp

build: $(output)

$(output): $(src) $(helper)
	@mkdir -p $(year)/output
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run the program
run: build
ifeq ($(test), 1)
	$(output) "$(year)/inputs/test.txt"
else
	$(output) "$(year)/inputs/day$(day).txt"
endif

profile: CXXFLAGS += -O2
profile: clean run

profileMax: CXXFLAGS += -O3
profileMax: clean run

# Clean build files
clean:
	rm -rf $(year)/output/day*

.PHONY: clean run build profile
