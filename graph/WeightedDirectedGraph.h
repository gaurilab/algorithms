#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>
#include <stdexcept>

using namespace std;
typedef vector<int> vi;

class DirectedEdge {
    public:
        DirectedEdge(int u,int v, double w):u_(u), v_(v), w_(w){ } 
        int u_, v_;
        double w_;

};
typedef vector<DirectedEdge> vDe;
typedef vector<vDe> vvDe;

class WeightedDirectedGraph {

    public:
        WeightedDirectedGraph():V(0),E(0) { }
        WeightedDirectedGraph(int v) :V(v),E(0) { }
        WeightedDirectedGraph(const char* file) {
            ifstream in;
            in.open(file);
            in>>V;
            adj.assign(V, vDe());
            int e;
            in>>e;
            int u,v;
            double w;
            while(e--) {
                in>>u>>v>>w;
                addEdge(u,v,w);
            }
        }

        void addEdge(int u, int v, double w) {
            inRange(u);
            inRange(v);
            printf("Adding edge %d %d %f\n",u, v,w);
            adj[u].push_back(DirectedEdge(u,v,w));
            ++E;
        }

        friend ostream& operator<<(ostream& o, const WeightedDirectedGraph &g) {
            o<<g.toString();
            return o;
        }

        int v() const {return V;}
        int e() const {return E;}

        const vDe& edges(int v) const{
            return adj[v];
        }

    private:
            string toString() const{
                stringstream s;
                s<<V<<" "<<E<<"\n";
                for (int v = 0 ; v < V; ++v) {
                    s<<v<<" : ";
                    for(int e = 0 ; e < adj[v].size(); ++e){
                        s<<adj[v][e].u_<< "->"<<adj[v][e].v_<<" "<<adj[v][e].w_<<" ";
                    }
                    s<<"\n";
                }
                return s.str();
            }
            void inRange(int v) {
                if (v >= V || v< 0) {
                    stringstream s;
                    s<<"Vertex "<<v<<" is not between 0 and "<<V<<"\n";
                    throw new out_of_range(s.str());
                }
            }
            vvDe adj;
            int V;
            int E;
};

