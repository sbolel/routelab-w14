AR = ar
CXX = g++
CXXFLAGS = -g -gstabs+ -ggdb -Wall
LDFLAGS = 

LIB_OBJS = node.o       \
           link.o       \
           topology.o   \
           event.o      \
           eventqueue.o \
           messages.o   \
	   context.o    \

EXEC_OBJS = routesim.o

OBJS = $(LIB_OBJS) $(EXEC_OBJS)


all: routesim

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $(@F)

libroutelab.a: $(LIB_OBJS)
	$(AR) ruv libroutelab.a $(LIB_OBJS)

routesim: routesim.o libroutelab.a
	$(CXX) $(LDFLAGS) routesim.o libroutelab.a -o routesim

depend:
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cc) > .dependencies

clean:
	rm -f $(OBJS) $(EXEC_OBJS:.o=) libroutelab.a

include .dependencies
