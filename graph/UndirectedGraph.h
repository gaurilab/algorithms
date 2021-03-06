#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>
#include <stdexcept>


using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

class Graph {

	public:
	Graph():V(0),E(0) { }
	Graph(int v) :V(v),E(0) { }
	Graph(const char* file) {
		ifstream in;
		in.open(file);
		in>>V;
		adj.assign(V, vi());
		int e;
		in>>e;
		int v, w;
		while(e--) {
			in>>v>>w;
			addEdge(v,w);
		}
	}

	void addEdge(int u, int v) {
		inRange(u);
		inRange(v);
		adj[u].push_back(v);
		adj[v].push_back(u);
		++E;
	}
	
	friend ostream& operator<<(ostream& o, const Graph&g) {
		o<<g.toString();
		return o;
	}

	private:
	string toString() const{
		stringstream s;
		s<<V<<" "<<E<<"\n";
		for (int v = 0 ; v < V; ++v) {
			s<<v<<" : ";
			for(int e = 0 ; e < adj[v].size(); ++e){
				s<<adj[v][e]<< " ";
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
	vvi adj;
	int V;
	int E;
};

