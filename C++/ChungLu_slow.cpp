#include <NetworKit/graph/Graph.h>
#include <NetworKit/generators/PowerlawDegreeSequence.h>

using namespace std;
int main(int argc, char** argv)
{
  NetworKit::count nNodes = atoi(argv[1]);
  double gamma = atof(argv[2]);
  NetworKit::PowerlawDegreeSequence sequencer(nNodes/10, nNodes-1, gamma);
  sequencer.run();
  vector<NetworKit::count> weights = sequencer.getDegreeSequence(nNodes);
  NetworKit::count sum_deg = std::accumulate(weights.begin(), weights.end(), 0);
  NetworKit::count sum_deg_mean = sum_deg/nNodes;
  NetworKit::Graph G(nNodes, false, false);
  cout << "Graph initialized: " << G.toString() << endl;

  for(int u = 0; u < nNodes; u++){
    for(int v = u + 1; v < nNodes; v++){
        NetworKit::count r = ((double) rand() / (RAND_MAX));
        NetworKit::count p = (weights[u]*weights[v])/(sum_deg_mean*nNodes);
        if (p > 1)
          p = 1;
        if (r < p)
          G.addEdge(u, v);
    }
  }

  cout << "Graph generated: " << G.toString() << endl;
  return 0;
}
