#include "node.h"

Node::Node(const string n, double b, double l, Graph *g) : 
    name(n), bw(b), lat(l), graph(g) 
{}

Node::Node() 
{ throw GeneralException(); }

Node::Node(const Node &rhs) : 
  name(rhs.name), bw(rhs.bw), lat(rhs.lat), graph(rhs.graph) {}

Node & Node::operator=(const Node &rhs) 
{
  return *(new(this)Node(rhs));
}

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

void Node::SendToNeighbors(const RoutingMessage &m)
{
}

void Node::Matches(const Node &rhs)
{
  return num=rhs.num;
}
