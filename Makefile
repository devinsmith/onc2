# Makefile for onc2

.PHONY: all clean

SRCS = oncapp.cpp oncframe.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

CXX? = g++

# Dependencies
DEP_INCLUDES = $(shell wx-config --cflags)
DEP_LIBS = $(shell wx-config --libs)

CFLAGS = -Wall -O2 -I.

EXE = onc2

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CFLAGS) -o $(EXE) $(OBJS) $(DEP_LFLAGS) $(DEP_LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $(DEP_INCLUDES) -MMD -MP -MT $@ -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXE) $(DEPS)

# Include automatically generated dependency files
-include $(DEPS)
