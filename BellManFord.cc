#include "WeightedDirectedGraph.h"
#include <limits>
#include <stack>
#include <cstdlib>



class BellManShortestPath {
    public:
        BellManShortestPath(const WeightedDirectedGraph &g, int source) {
            distTo.assign(g.v(), std::numeric_limits<double>::max() );
            edgeTo.assign(g.v(), -1);
            distTo[source] = 0;
            build(g);
        }

        void build(const WeightedDirectedGraph &g) 
        {
            int n = g.v();
            for (int  i = 1 ; i <= n; ++i) {
                bool negativecycle = (n == i);
                bool updated = false;
                for (int u = 0 ; u < n; ++u) {
                    const vDe edges = g.edges(u);
                    for (vDe::const_iterator it = edges.begin(); it != edges.end(); ++it) {
                        int v = it->v_;
                        double w = it->w_;
                        double newW =  distTo[u]+w;
                        if (distTo[v] > newW) {
                            if (negativecycle) { 
                                int p = v;
                                cycle.push(p);
                                p = edgeTo[p];
                                while(p != v) {
                                    cycle.push(p);
                                }
                            }
                            distTo[v] = newW;
                            edgeTo[v] = u;
                            printf("updating  in %d %f\n",v, distTo[v]);
                            updated = true;
                        }
                    }

                }
                if (!updated) {
                        break;
                }   
            }
        }

        void printPath(int v) {
            if (hasPathTo(v)) {
                int   p = v;
                while (p != -1) {
                    printf("%d<- ", p);
                    p = edgeTo[p];
                }
                printf("\n");
            }
        }

        bool hasPathTo(int v) {
            return (distTo[v] >= 0 );
        }
        double distanceTo(int v) {
            return distTo[v];
        }
    private:
        vector<double> distTo;
        vi edgeTo;
        stack<int> cycle;
      
};

int main(int c, const char* v[]) {
    if (c < 3) {
        printf("Provide input graph");
        return -1;
    }
    WeightedDirectedGraph g(v[1]);
    cout<<g;
    int s = atoi(v[2]);
    BellManShortestPath sp(g, s);
    // print shortest path
    for (int t = 0; t < g.v(); t++) {
        if (sp.hasPathTo(t)) {
            printf("%d to %d (%.2f)  \n", s, t, sp.distanceTo(t));
            sp.printPath(t);
        }
        else {
            printf("%d to %d no path\n", s, t);
        }
    }
}
