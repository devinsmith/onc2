# Makefile for onc2

.PHONY: all clean

SRCS = oncapp.cpp oncframe.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

CXX? = g++

# Dependencies
#WX_CONFIG = wx-config
# Gtk3+
WX_CONFIG = wx-config-gtk3

DEP_INCLUDES = $(shell $(WX_CONFIG) --cflags)
DEP_LIBS = $(shell $(WX_CONFIG) --libs)

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
