#include <NetworKit/graph/Graph.h>
using namespace std;
int main(int argc, char** argv)
{
  int nNodes = atoi(argv[1]);
  double p = atof(argv[2]);
  NetworKit::Graph G(nNodes, false, false);
  cout << "Graph initialized: " << G.toString() << endl;

  for(int u = 0; u < nNodes; u++){
    int v = u + 1;
    while (v < nNodes){
        double r = ((double) rand() / (RAND_MAX));
        v += ceil(log(r)/log(1-p));
        if (v < nNodes){
          G.addEdge(u, v);
          v++;
        }
    }
  }

  cout << "Graph generated: " << G.toString() << endl;
  return 0;
}
