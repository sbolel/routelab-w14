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

void Node::SetTimeOut(const double timefromnow)
{
  context->TimeOut(this,timefromnow);
}


bool Node::Matches(const Node &rhs) const
{
  return number==rhs.number;
}


#if defined(GENERIC)
void Node::LinkUpdate(const Link *l)
{
  cerr << *this << " got a link update: "<<*l<<endl;
  //Do Something generic:
  SendToNeighbors(new RoutingMessage);
}


void Node::ProcessIncomingRoutingMessage(const RoutingMessage *m)
{
  cerr << *this << " got a routing messagee: "<<*m<<" Ignored "<<endl;
}


void Node::TimeOut()
{
  cerr << *this << " got a timeout: ignored"<<endl;
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

void Node::TimeOut()
{
  cerr << *this << " got a timeout: ignored"<<endl;
}

Node *Node::GetNextHop(const Node *destination) const
{
  // WRITE
  deque<Row>::iterator next = table.FindMatching(destination->GetNumber());
  deque<Node*>* neighbors = GetNeighbors();
  for(deque<Node*>::iterator i = m->begin(); i != m->end(); ++i){
    if((*i)->GetNumber() == next->next_node){
      return new Node((**i));
    }
  }
  return 0;
}

Table *Node::GetRoutingTable() const
{
  // WRITE
  return new Table(table);
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
  cerr << "Current cost: " << FindCost(l->GetDest()) << endl;
  SetCost(l->GetDest(), l->GetLatency());
  cerr << "Current cost: " << FindCost(l->GetDest()) << endl;
  deque<Row>::iterator it = table.m.begin();
  deque<Node*>* neighbors = GetNeighbors();
  double min;
  unsigned min_node;
  double c;
  bool changed = false;

  for( ; it != table.m.end(); ++it){
    unsigned dst = it->dest_node;
    min = 0;
    for(deque<Node*>::iterator i = neighbors->begin(); i != neighbors->end(); ++i){
      double n_to_dst = 0;
      if(dst==(*i)->GetNumber()){
        n_to_dst = 0;
      } else { //the destination we're checking is not this neighbor, lookup the dest in the neighbor's table
        if(neighborTable.find((*i)->GetNumber()) != neighborTable.end()){
          //the neighbor has an entry in the map
          for(unsigned count = 0; count < neighborTable[(*i)->GetNumber()].size(); ++count){
            //loop through the neighbor's table to find the entry for this dest
            if(neighborTable[(*i)->GetNumber()][count].dest_node == dst){
              n_to_dst = neighborTable[(*i)->GetNumber()][count].cost;
            }
          }//out of loop, check to see if we found an entry
          if(n_to_dst == 0){
            continue; //move on to next neighbor
          }
        } else {
          cout << "For some reason, there's no entry in the neighborTable for this neighbor" << endl;
          continue;
        }
      }
      c = n_to_dst + FindCost((*i)->GetNumber());
      if(min == 0 || c < min){
        min = c;
        min_node = (*i)->GetNumber();
      }
    }
    cerr << "Min: " << min << " Previous Cost: " << it->cost << endl;
    if(min != it->cost){
      //least-cost has changed
      cerr << "Least-cost has changed" << endl;
      it->cost = min;
      it->next_node = min_node;
      SendToNeighbors(new RoutingMessage(*this, Node(it->dest_node, 0, 0, 0), min));
    }
  }
  it = table.m.begin();
  for( ; it != table.m.end(); ++it){
    if(it->dest_node == l->GetDest()){
      return;
    }
  }
  table.m.push_back(Row(l->GetDest(), l->GetDest(), l->GetLatency()));
  SendToNeighbors(new RoutingMessage(*this, Node(l->GetDest(), 0, 0, 0), l->GetLatency()));
  /*
  deque<Node*> * neighbors = GetNeighbors();
  set<unsigned> updatedDists;

  double min;
  
  for(map<unsigned, vector<Row>>::iterator i = neighborTable.begin(); i != neighborTable.end(); ++i){
    vector<Row> ntable = i->second;
    for(unsigned count = 0; count < ntable.size(); ++count){
      if(updatedDists.find(ntable[count].dest_node) == updatedDists.end()){
        //if we have not already looked at this destination
        min = 0;
        for
        double this_cost = FindCost()
      }
    }
  }
  neighborTable[]
  */

}


void Node::ProcessIncomingRoutingMessage(const RoutingMessage *m)
{
  cerr << "Node "<<GetNumber()<<": "<<m->srcnode.GetNumber()<<" has new cost "<<m->cost
       <<" path to "<<m->dest.GetNumber()<<" Action: ";

  map<unsigned, vector<Row> >::iterator it = neighborTable.find(m->srcnode.GetNumber());
  if(it != neighborTable.end()){
    bool found = false;
    //rewrite the cost in the corresponding entry in the existing mapping to the new least-cost
    for(unsigned count = 0; count < neighborTable[m->srcnode.GetNumber()].size(); ++count){
      if(neighborTable[m->srcnode.GetNumber()][count].dest_node == m->dest.GetNumber()){
        //this is the right entry
        neighborTable[m->srcnode.GetNumber()][count].cost = m->cost; //rewrite cost
        found = true;
      }
    }
    //if mapping doesn't have entry for this dest, make a new one
    if (found==false){
      neighborTable[m->srcnode.GetNumber()].push_back(Row(m->dest.GetNumber(), m->dest.GetNumber(), m->cost));
    }

    //here, recalculate least-cost like in linkUpdate
    double c;
    double min = 0;
    unsigned min_node;
    deque<Node*>* neighbors = GetNeighbors();
    for(deque<Node*>::iterator i = neighbors->begin(); i != neighbors->end(); ++i){
      double n_to_dst = 0;
      if(m->dest.GetNumber()==(*i)->GetNumber()){
        n_to_dst = 0;
      } else {
        if(neighborTable.find((*i)->GetNumber()) != neighborTable.end()){
          //the neighbor has an entry in the map
          for(unsigned count = 0; count < neighborTable[(*i)->GetNumber()].size(); ++count){
            //loop through the neighbor's table to find the entry for this dest
            if(neighborTable[(*i)->GetNumber()][count].dest_node == m->dest.GetNumber()){
              n_to_dst = neighborTable[(*i)->GetNumber()][count].cost;
            }
          }//out of loop, check to see if we found an entry
          if(n_to_dst == 0){
            continue; //move on to next neighbor
          }
        } else {
          cout << "For some reason, there's no entry in the neighborTable for this neighbor" << endl;
          continue;
        }
      }
      c = n_to_dst + FindCost((*i)->GetNumber());
      if(min == 0 || c < min){
        min = c;
        min_node = (*i)->GetNumber();
      }
    }
    deque<Row>::iterator iter = table.FindMatching(m->dest.GetNumber());

    if(min != iter->cost){
      iter->cost = min;
      iter->next_node = min_node;
      SendToNeighbors(new RoutingMessage(*this, Node(iter->dest_node, 0, 0, 0), min));
    }
    
    //here, recalculate least-cost like in linkUpdate

  } else {
    //make a new neighborTable entry for this neighbor
    neighborTable[m->srcnode.GetNumber()] = vector<Row>();
    neighborTable[m->srcnode.GetNumber()].push_back(Row(m->dest.GetNumber(), m->dest.GetNumber(), m->cost));
  }
/*
  if (m->dest.GetNumber()==GetNumber()) { 
    cerr << " ourself - ignored\n";
    return;
  }
*/
}

void Node::TimeOut()
{
  cerr << *this << " got a timeout: ignored"<<endl;
}

Node *Node::GetNextHop(const Node *destination)
{
  // WRITE
  deque<Row>::const_iterator next = table.FindMatching(destination->GetNumber());
  deque<Node*>* neighbors = GetNeighbors();
  for(deque<Node*>::iterator i = neighbors->begin(); i != neighbors->end(); ++i){
    if((*i)->GetNumber() == next->next_node){
      return new Node((**i));
    }
  }
  return 0;
}

Table *Node::GetRoutingTable() const
{
  // WRITE
  return new Table(table);
}


ostream & Node::Print(ostream &os) const
{
  os << "Node(number="<<number<<", lat="<<lat<<", bw="<<bw;
  os << ", table="<<table<<")";
  return os;
}

double Node::FindCost(const unsigned dest)
{
  for(unsigned i = 0; i < costs.size(); ++i){
    if(costs[i].dest_node == dest){
      return costs[i].cost;
    }
  }
}

void Node::SetCost(const unsigned dest, const double c)
{
  for(unsigned i = 0; i < costs.size(); ++i){
    if(costs[i].dest_node == dest){
      costs[i].cost = c;
      return;
    }
  }
  costs.push_back(Row(dest, dest, c));
}
#endif
