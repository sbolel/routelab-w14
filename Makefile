CXX = g++
CXXFLAGS = -g -gstabs+ -ggdb -Wall
LDFLAGS = 

LIB_OBJS = node.o       \
           link.o       \
           topology.o   \
           eventqueue.o \
	   context.o    \

EXEC_OBJS = routesim.o

OBJS = $(LIB_OBJS) $(EXEC_OBJS)


all: routesim

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $(@F)

routesim: routesim.o libroutelab.a
	$(CXX) $(LDFLAGS) routesim.o libroutelab.a -o routelab

depend:
	$(CXX) $(CXXFLAGS) -MM $(OBJS:.o=.cc) > .dependencies

clean:
	rm -f $(OBJS) $(EXEC_OBJS:.o=) libroutelab.a

include .dependencies
