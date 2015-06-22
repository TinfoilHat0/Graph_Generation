#include <NetworKit/graph/Graph.h>
using namespace std;
int main(int argc, char** argv)
{
  int nNodes = atoi(argv[1]);
  double p = atof(argv[2]);

  NetworKit::Graph G(nNodes, false, false);
  cout << "Graph initialized: " << G.toString() << endl;
  for(int i=0; i < nNodes; i++){
    for(int j=i+1; j<nNodes; j++){
      double r = ((double) rand() / (RAND_MAX));
      if (r < p)
        G.addEdge(i, j);
    }
  }
  cout << "Graph generated: " << G.toString() << endl;


  return 0;
}
