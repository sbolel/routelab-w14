#include "node.h"
#include "context.h"
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
  context->SendToNeighbors(this,m);
}

void Node::SendToNeighbor(const Node *n, const RoutingMessage *m)
{
  context->SendToNeighbor(this,n,m);
}

deque<Node*> *Node::GetNeighbors()
{
  return context->GetNeighbors(this);
}


bool Node::Matches(const Node &rhs) const
{
  return number==rhs.number;
}


#if defined(GENERIC)
void Node::LinkUpdate(const Link *l)
{
  cerr << *this << " got a link update: "<<*l<<endl;
  SendToNeighbors(new RoutingMessage);
  //WRITE
}


void Node::ProcessIncomingRoutingMessage(const RoutingMessage *m)
{
  cerr << *this << " got a routing messagee: "<<*m<<" Ignored "<<endl;
}


Node *Node::GetNextHop(const Node *destination) const
{
  return 0;
}

Table *Node::GetRoutingTable() const
{
  return new Table;
}


ostream & Node::Print(ostream &os) const
{
  os << "Node(number="<<number<<", lat="<<lat<<", bw="<<bw<<")";
  return os;
}

#endif

#if defined(LINKSTATE)

const unsigned Node::maxttl=5;

void Node::LinkUpdate(const Link *l)
{
  // Add To table and update graph
  // Now flood to rest of network
  cerr << *this<<": Link Update: "<<*l<<endl;
  RoutingMessage *m = new RoutingMessage(*this,*l,maxttl,seqno++);
  SendToNeighbors(m);
}


void Node::ProcessIncomingRoutingMessage(const RoutingMessage *m)
{
  cerr << *this << " Routing Message: "<<*m;
  if (m->srcnode.Matches(*this)) {
    // skip, one of ours
    cerr << " IGNORED"<<endl;
  } else {
    // update our table
    if (m->ttl==0) { 
      cerr << " DROPPED, TTL=0"<<endl;
    } else {
      // Forward to neighbors
      RoutingMessage *out=new RoutingMessage(*m);
      out->ttl--;
      cerr << " FORWARDED"<<endl;
      SendToNeighbors(out);
    }
  }
}


Node *Node::GetNextHop(const Node *destination) const
{
  // WRITE
  return 0;
}

Table *Node::GetRoutingTable() const
{
  // WRITE
  return 0;
}


ostream & Node::Print(ostream &os) const
{
  os << "Node(number="<<number<<", lat="<<lat<<", bw="<<bw<<")";
  return os;
}
#endif


#if defined(DISTANCEVECTOR)

void Node::LinkUpdate(const Link *l)
{
  // update our table
  // send out routing mesages
  cerr << *this<<": Link Update: "<<*l<<endl;
  table.SetNext(l->GetDest(),Row(l->GetDest(),l->GetDest(),l->GetLatency()));
  RoutingMessage *m = new RoutingMessage(*this,Node(l->GetDest(),0,0,0),l->GetLatency());
  SendToNeighbors(m);
}


void Node::ProcessIncomingRoutingMessage(const RoutingMessage *m)
{
  cerr << "Node "<<GetNumber()<<": "<<m->srcnode.GetNumber()<<" has new cost "<<m->cost
       <<" path to "<<m->dest.GetNumber()<<" Action: ";

  if (m->dest.GetNumber()==GetNumber()) { 
    cerr << " ourself - ignored\n";
    return;
  }

  Row *rd=table.GetNext(m->dest.GetNumber());
  Row *rs=table.GetNext(m->srcnode.GetNumber());

  if (rs==0) { 
    // Unlikely since we must have gotten a link update
    cerr << " UNKNOWN NEIGHBOR - ignored"<<endl;
    return;
  }
  double newcost = rs->cost+m->cost;
  cerr << " our cost is "<<newcost;
  bool doupdate=false;

  if (rd==0) {
    // New destination
    doupdate=true;
    cerr <<" New destination - updating and sending\n";
  }

  if (rd && newcost<rd->cost) {
    doupdate=true;
    cerr <<" New lower cost - updating and sending\n";
  }

  if (rd && rd->next_node==m->dest.GetNumber()) { 
    doupdate=true;
    cerr << " Changed cost on existing node - updating and sending\n";
  }

  if (doupdate) {
    table.SetNext(m->dest.GetNumber(),Row(m->dest.GetNumber(),m->srcnode.GetNumber(),newcost));
    // news to us, let's resend it
    RoutingMessage *mout=new RoutingMessage(*m);
    mout->srcnode=*this;
    mout->cost+=newcost;
    SendToNeighbors(mout);
  } else {
    cerr <<" ignored\n";
  }
}


Node *Node::GetNextHop(const Node *destination) const
{
  Row *r = ((Node *)this)->table.GetNext(destination->GetNumber());
  if (r==0) {
    return 0;
  } else {
    Node *n=new Node(r->next_node,0,0,0);
    delete r;
    return n;
  }
}

Table *Node::GetRoutingTable() const
{
  return new Table(table);
}


ostream & Node::Print(ostream &os) const
{
  os << "Node(number="<<number<<", lat="<<lat<<", bw="<<bw;
  os << ", table="<<table<<")";
  return os;
}
#endif
