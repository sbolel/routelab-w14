#include "context.h"

#include "node.h"
#include "link.h"

class MyNode : public Node
{

};



int main(int argc, char *argv)
{
  bool singlestep;
  string topofile, eventfile;


  if (argc<2 || argc>3 ) {
    cerr <<"routelab topologyfile eventfile [singlestep]"<<endl;
    exit(-1);
  }
  singlestep=(argc==3);
  topofile=argv[1];
  eventfile=argv[2];
  
  SimulationContext<MyNode,Link> c;

  c.LoadTopology(topofile);
  c.LoadEvents(eventfile);
  
  Event<MyNode,Link> *e;
  while ((e=c.GetEarliestEvent())) {
    cerr << *e << endl;
    c.DispatchEvent(e);
  }
}
  
  
