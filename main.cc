#include "context.h"


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
  
  Context c;

  c.LoadTopology(topofile);
  c.LoadEvents(eventfile);
  
  Event *e;
  while ((e=c.GetNextEvent())) {
    e->Dispatch();
    e->Disassociate();
    delete e;
  }
}
  
  
