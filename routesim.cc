#include "context.h"

#include "node.h"
#include "link.h"



int main(int argc, char **argv)
{
  bool singlestep;
  string topofile, eventfile;


  if (argc<2 || argc>3 ) {
    cerr <<"routesim topologyfile eventfile [singlestep]"<<endl;
    exit(-1);
  }
  singlestep=(argc==3);
  topofile=argv[1];
  eventfile=argv[2];
  
  SimulationContext c;

  c.LoadTopology(topofile);
  
  //cerr << c <<endl;

  c.LoadEvents(eventfile);

  c.Init();

  //cerr << c << endl;
  
  Event *e;
  while ((e=c.GetEarliestEvent())) {
    //    cerr << *e << endl;
    c.DispatchEvent(e);
  }
}
  
  
