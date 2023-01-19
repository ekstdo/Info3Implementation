#include <vector>
#include <list>
#include <iostream>

struct graph {
	std::vector<std::list<int>> edges;

	std::list<int> adjacent_nodes(int i) const {
		return edges[i];
	}
};

class dfs {
	enum node_state { visited, visiting, unvisited };
	const graph &G;
	std::vector<node_state> states;
	std::vector<int> &previous;
	std::vector<int> &start, &finished;
	int t;

	void dfs_visit(const int u){
		states[u] = visiting;
		start[u] = ++t;
		for(int v: G.adjacent_nodes(u)){
			if (states[v] == unvisited) {
				previous[v] = u;
				dfs_visit(v);
			}
		}
		finished[u] = ++t;
		states[u] = visited;
	}

public:
	dfs(const graph &G_, std::vector<int>& previous_, std::vector<int>& starting_, std::vector<int>& finished_):
			G(G_), previous(previous_), start(starting_), finished(finished_), states(G.edges.size(), unvisited) {
		previous.resize(G.edges.size());
		start.resize(G.edges.size());
		finished.resize(G.edges.size());
		std::fill(previous.begin(), previous.end(), -1);
		t = 0;
		for (int i = 0; i < G.edges.size(); i++){
			if (states[i] == unvisited) 
				dfs_visit(i);
		}
	}
};

class dfs_iterativ {
	enum node_state { visited, visiting, unvisited };
	const graph &G;
	std::vector<node_state> states;
	std::vector<int> &previous;
	std::vector<int> &start, &finished;
	int t;

	void dfs_visit(int u){
		std::vector<int> stack = {u};
		while (stack.size() != 0){
			u = stack.back();
			stack.pop_back();

			states[u] = visiting;
			start[u] = ++t;
			for(int v: G.adjacent_nodes(u)){
				if (states[v] == unvisited) {
					previous[v] = u;
					stack.push_back(v);
				}
			}
			finished[u] = ++t;
			states[u] = visited;
		}
	}

public:
	dfs_iterativ(const graph &G_, std::vector<int>& previous_, std::vector<int>& starting_, std::vector<int>& finished_):
			G(G_), previous(previous_), start(starting_), finished(finished_), states(G.edges.size(), unvisited) {
		previous.resize(G.edges.size());
		start.resize(G.edges.size());
		finished.resize(G.edges.size());
		std::fill(previous.begin(), previous.end(), -1);
		t = 0;

		for (int i = 0; i < G.edges.size(); i++){
			if (states[i] == unvisited) 
				dfs_visit(i);
		}
	}
};

int main(){
	std::vector<int> previous, starting, finished;
	graph G = { {  { 1, 2 }, {0, 2}, {0, 1}, {} } };
	dfs d(G, previous, starting, finished);
	for (int i: previous) 
		std::cout << i << ", "; 
	std::cout <<"\n";
	dfs_iterativ d2(G, previous, starting, finished);
	for (int i: previous) 
		std::cout << i << ", "; 
	std::cout <<"\n";
}
