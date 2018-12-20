CXXFLAGS += -std=c++11

# Based on https://stackoverflow.com/a/287313/795068
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:.cpp=.d)

BINS = EdgeConnectivity

CFLAGS += -MMD
CXXFLAGS += -MMD

all: $(BINS)

EdgeConnectivity: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(DEPS) $(BINS)

-include $(DEPS)
