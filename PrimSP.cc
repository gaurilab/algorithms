#include  "WeightedUndirectedGraph.h"
#include  <limits>
#include  <queue>
#include  <cstdlib>
#include <cassert>

//comparator to compare the priority_queue elements based on the distance
class EdgeCompare{
    public:
        int operator() ( const WeightedEdge &p1, const WeightedEdge& p2 ) {
            return p1.weight() >  p2.weight();
        }
};

class PrimSP {
    public:
        PrimSP(const WeightedUndirectedGraph &g){
            visited.assign(g.v(), false);
            weight = 0;
            for (int i = 0 ; i < g.v(); ++i) {
                if (!visited[i]) prim(g, i);
            }
        }

        void prim(const WeightedUndirectedGraph &g , int v) {   
            visited[v] = true;

            const vDe edges = g.edges(v);
            for (vDe::const_iterator it = edges.begin(); it != edges.end(); ++it) {
                if (!visited[it->other(v)]) {
                    printf("Inserting  edge in PQ %d %d %f\n", it->either(), 
                            it->other(it->either()),
                            it->weight());
                    pq.push(*it);
                }
            }

            while (!pq.empty()) {
                WeightedEdge e = pq.top();
                pq.pop();

                int s = e.either();
                int t = e.other(s);

                printf("Popped edge in PQ %d %d %f\n", e.either(), 
                        e.other(e.either()),
                        e.weight());

                if (visited[s] && visited[t]) continue;

                assert(visited[s] ||visited[t]);

                printf("Pushing edge in SP tree %d %d %f\n", e.either(), 
                        e.other(e.either()),
                        e.weight());

                tree.push_back(e);
                
                const int nextv = visited[s] ? t : s;
                visited[nextv] = true;

                const vDe edges = g.edges(nextv);
                for (vDe::const_iterator it = edges.begin(); it != edges.end(); ++it) {
                    if (!visited[it->other(nextv)]) {
                        printf("Inserting  edge in PQ %d %d %f\n", it->either(), 
                                it->other(it->either()),
                                it->weight());
                        pq.push(*it);
                    }
                }
                weight += e.weight();
            }
        }
        double W() {
            return weight;
        }
#if 1
        friend ostream & operator<<(ostream& o , const PrimSP &sp) {
            for (vector<WeightedEdge>::const_iterator it = sp.tree.begin();
                it != sp.tree.end() ; ++it) 
            o<<*it<<endl;
        }
#endif
    private:
        vector<bool> visited;
        vector<WeightedEdge> tree;
        priority_queue<WeightedEdge, vector<WeightedEdge> , EdgeCompare>  pq;
        double weight;
};

int main(int c, const char* v[]) {
    if (c < 2) {
        printf("Provide input graph");
        return -1;
    }
    WeightedUndirectedGraph g(v[1]);
    cout<<g;
    PrimSP sp(g);
    cout<<sp.W()<<endl;
    cout<<sp;

}
