#include  "WeightedDirectedGraph.h"
#include  <limits>
#include <queue>
#include <cstdlib>

class EdgeCompare{
    public:
        int operator() ( const pair<int, double>& p1, const pair<int, double>& p2 )
        {
            return p1.second < p2.second;
        }

};
class Dijkstra {
    public:
        Dijkstra(const WeightedDirectedGraph &g, int source) {
            distTo.assign(g.v(), std::numeric_limits<double>::max() );
            edgeTo.assign(g.v(), -1);
            distTo[source] = 0;
            printf("pushing in pq %d %f",source, distTo[source]);
            for (int t = 0 ; t < g.v(); ++t) {
                pq.push(make_pair(t, distTo[t]));
            }
            build(g);
        }

        void build(const WeightedDirectedGraph &g) 
        {
            while(!pq.empty()) {
                pair<int, double> u = pq.top();
                printf("poping from  pq %d %f\n",u.first, u.second);
                pq.pop();
                const vDe edges = g.edges(u.first);
                for (vDe::const_iterator it = edges.begin(); it != edges.end(); ++it) {
                    int v = it->v_;
                    double w = it->w_;
                    double newW =  distTo[u.first]+w;
                    if (distTo[v] > newW) {
                        distTo[v] = newW;
                        edgeTo[v] = u.first;
                        printf("pushing in pq %d %f\n",v, distTo[v]);
                        pq.push(make_pair(v, distTo[v]));
                    }
                }
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
        priority_queue<pair<int, double>,vector<pair<int, double> >, EdgeCompare> pq;
};

int main(int c, const char* v[]) {
    if (c < 3) {
        printf("Provide input graph");
        return -1;
    }
    WeightedDirectedGraph g(v[1]);
    cout<<g;
    int s = atoi(v[2]);
    Dijkstra sp(g, s);
    // print shortest path
    for (int t = 0; t < g.v(); t++) {
        if (sp.hasPathTo(t)) {
            printf("%d to %d (%.2f)  \n", s, t, sp.distanceTo(t));
        }
        else {
            printf("%d to %d no path\n", s, t);
        }
    }
}
