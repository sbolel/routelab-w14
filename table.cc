#include "table.h"

#if defined(GENERIC)
ostream & Table::Print(ostream &os) const 
{
  // WRITE THIS
  os << "Table()";
  return os;
}
#endif

#if defined(LINKSTATE)

#endif

#if defined(DISTANCEVECTOR)

deque<Row>::iterator Table::FindMatching(const unsigned dest) 
{
  for(deque<Row>::iterator i = m.begin(); i != m.end(); ++i){
    if(i->dest_node == dest){
      return i;
    }
  }
  return m.end();
}

Row *Table::GetNext(const unsigned dest) 
{
  deque<Row>::iterator i = FindMatching(dest);
  Row* nextHopRow = new Row(i->dest_node, i->next_node, i->cost);
  return nextHopRow; ////////////PLACE HOLDER FOR UNTIL I FIGURE OUT WHY THE FUCK WE'RE RETURNING A ROW*//////////////////
  ////////////WE'RE JUST RETURNING A COPY OF THE ROW WITH MATCHING DEST HERE//////////////////
}

void Table::SetNext(const unsigned dest, const Row &r)
{
  deque<Row>::iterator i = FindMatching(dest);
  cout << "Table SetNext called with dest: " << dest << "and r: " << r << endl;
}

Row::Row(const unsigned dest, const unsigned next, const double c) :
  dest_node(dest), next_node(next), cost(c)
{}

ostream & Row::Print(ostream &os) const 
{
  os <<"Row(dest="<<dest_node<<", next="<<next_node<<", cost="<<cost<<")";
  return os;
}

ostream & Table::Print(ostream &os) const 
{
  os<<"Table(rows={";
  for (deque<Row>::const_iterator i=m.begin();i!=m.end();++i) { 
    os <<(*i)<<", ";
  }
  os<<"})";
  return os;
}
    
#endif
