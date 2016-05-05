#ifndef __WEIGHTED_UNDIRECTED_GRAPH__
#define __WEIGHTED_UNDIRECTED_GRAPH__

#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;
typedef vector<int> vi;

class WeightedEdge {
    public:
        int either() const {
            return min(u_, v_);
        }
        int other(int u) const {
           if (u == u_) return v_;
           if (u == v_) return u_;
           assert(0);
        }
        double weight() const { return w_;}

        friend ostream& operator<<(ostream& o, const WeightedEdge& w) {
            o<<"("<<w.u_<<"-"<<w.v_<<")";
            return o;
        }

        WeightedEdge(int u,int v, double w):u_(u), v_(v), w_(w){ } 
        int u_, v_;
        double w_;

};

typedef vector<WeightedEdge> vDe;
typedef vector<vDe> vvDe;

class WeightedUndirectedGraph {
    public:
        WeightedUndirectedGraph():V(0),E(0) { }
        WeightedUndirectedGraph(int v) :V(v),E(0) { }
        WeightedUndirectedGraph(const char* file) {
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
            adj[u].push_back(WeightedEdge(u,v,w));
            adj[v].push_back(WeightedEdge(v,u,w));
            ++E;
        }

        friend ostream& operator<<(ostream& o, const WeightedUndirectedGraph &g) {
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

#endif
