#include "node.h"
#include "error.h"


Node::Node(const unsigned n, SimulationContext *c, double b, double l) : 
    number(n), context(c), bw(b), lat(l) 
{}

Node::Node() 
{ throw GeneralException(); }

Node::Node(const Node &rhs) : 
  number(rhs.number), context(rhs.context), bw(rhs.bw), lat(rhs.lat) {}

Node & Node::operator=(const Node &rhs) 
{
  return *(new(this)Node(rhs));
}

void Node::SetNumber(const unsigned n) 
{ number=n;}

unsigned Node::GetNumber() const 
{ return number;}

void Node::SetLatency(const double l) 
{ lat=l;}

double Node::GetLatency() const 
{ return lat;}

void Node::SetBW(const double b) 
{ bw=b;}

double Node::GetBW() const 
{ return bw;}

Node::~Node()
{}

void Node::SendToNeighbors(const RoutingMessage *m)
{
}

bool Node::Matches(const Node &rhs) const
{
  return number==rhs.number;
}


void Node::ProcessIncomingRoutingMessage(const RoutingMessage *m)
{
  // WRITE
}


void Node::GetRoute(const Node *destination, RoutingTableEntry *rte) const
{
  // WRITE
}

Table *Node::GetRoutingTable() const
{
  // WRITE
  return 0;
}
