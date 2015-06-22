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
  sort(weights.begin(), weights.end());
  reverse(weights.begin(), weights.end());
  NetworKit::count sum_deg = std::accumulate(weights.begin(), weights.end(), 0);
  NetworKit::Graph G(nNodes, false, false);
  cout << "Graph initialized: " << G.toString() << endl;

  for(int u = 0; u < nNodes; u++){
    for(int v = u + 1; v < nNodes; v++){
        NetworKit::count p = (weights[u]*weights[v])/(sum_deg);
        if (p > 1)
          p = 1;
        while ((v < nNodes) && (p > 0)){
          if (p != 1){
            NetworKit::count r = ((double) rand() / (RAND_MAX));
            v = v + ceil(log(r)/log(1-p));
          }
          if (v < nNodes){
            NetworKit::count q = (weights[u]*weights[v])/sum_deg;//min() doesnt work?
            if (q > 1)
              q = 1;
            NetworKit::count r = ((double) rand() / (RAND_MAX));
            if (r < q/p)
              G.addEdge(u, v);
            p = q;
            v++;
          }

        }
    }
  }

  cout << "Graph generated: " << G.toString() << endl;
  return 0;
}
