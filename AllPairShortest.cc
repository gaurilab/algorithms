#include  "WeightedDirectedGraph.h"
#include  <limits>
#include <queue>
#include <cstdlib>
typedef vector <double> vd;
typedef vector <int> vi;
typedef vector<vd> vvd;
typedef vector<vi> vvi;

class AllPairShortestPath {
    public:
        AllPairShortestPath(const WeightedDirectedGraph &g) {
            dist.assign(g.v(), vd());
            pred.assign(g.v(), vi());
            for (int k = 0 ; k < g.v() ; ++k) {
                dist[k].assign(g.v(), std::numeric_limits<double>::max());
                pred[k].assign(g.v(), -1);
                dist[k][k] = 0;
                //pred[k][k] = k;
            }
            for (int u = 0 ; u < g.v() ; ++u) {
                const vDe edges = g.edges(u);
                for (vDe::const_iterator it = edges.begin(); it != edges.end(); ++it) {

                    int v = it->v_;
                    double w = it->w_;
                    dist[u][v] = w;
                    pred[u][v] = u;
                    
                }
            }

            for (int s = 0; s < g.v(); s++) {
                for (int t = 0; t < g.v(); t++) {
                    printf("(%4d) ",  pred[s][t]);
                }
                printf("\n");
            }
            build(g);
        }

        void build(const WeightedDirectedGraph &g) {
            for (int k = 0 ; k < g.v(); ++k) {
                for (int i =0 ; i < g.v(); ++i) {
                     if (dist[i][k] == numeric_limits<double>::max()) {
                        continue;
                      }
                    for (int j =0 ; j < g.v(); ++j) {
/*                         printf("dist[%d][%d]=[%2.2f]\n",i,j,dist[i][j]);
                         printf("dist[%d][%d]=[%2.2f]\n",i,k,dist[i][k]);
                         printf("dist[%d][%d]=[%2.2f]\n",k,j,dist[k][j]);*/
                      if (k == j ||dist[i][k] == numeric_limits<double>::max()) {
                        continue;
                      }
                      double newL = dist[i][k] + dist[k][j];
                      if (newL <  dist[i][k] || newL < dist[i][k] ) {
                        continue;
                      }
                      if ((newL - dist[i][j]) < std::numeric_limits<double>::epsilon()){
                            dist[i][j] = newL;
                            pred[i][j] = pred[k][j];
                        }
                    }
                }
                printf("----------------------------------\n");
             for (int s = 0; s < g.v(); s++) {
                for (int t = 0; t < g.v(); t++) {
                    printf("(%4d) ",  pred[s][t]);
                }
                printf("\n");
            }  
            printf("----------------------------------\n");
            }
        }

        bool hasPathTo(int u, int v) {
            return (dist[u][v] - std::numeric_limits<double>::max()) < std::numeric_limits<double>::epsilon();
        }
        double distanceTo(int u,int v) {
            return dist[u][v];
        }
        void printPath(int i, int j) {
            if (hasPathTo( i,j)) {
                printf("\n printing path from %d to %d", i,j);
                if (i == j ||j == -1 ) {
                   return;
                }
            
                printPath(i,pred[i][j]);
                printf("-> %d ",j);
            }
            //printf("\n");
        }

    private:
        vvd dist;
    public:
        vvi pred;
};

int main(int c, const char* v[]) {
    if (c < 2) {
        printf("Provide input graph");
        return -1;
    }
    WeightedDirectedGraph g(v[1]);
    cout<<g;
    AllPairShortestPath sp(g);
    // print shortest path
    for (int s = 0; s < g.v(); s++) {
        for (int t = 0; t < g.v(); t++) {
            printf("(%4.2f) ",  sp.distanceTo(s,t));
            sp.printPath(s,t);
        }
        printf("\n");
    }
    for (int s = 0; s < g.v(); s++) {
        for (int t = 0; t < g.v(); t++) {
            printf("(%4.2d) ",  sp.pred[s][t]);
        }
        printf("\n");
    }
}

