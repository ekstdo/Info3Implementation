#include <functional>
#include <list>
#include <tuple>
#include <vector>
#include <numeric>
#include <map>
#include <fmt/ranges.h>
#include "fib.hpp" // ich weiß, absolut cursed, aber egal


template <class T>
using network = std::vector<std::map<int,T>>; // node and cost

#define forall_edges(G, from, to, cost) for (int from = 0; from < G.size(); from++) for (auto const &[to, cost]: G[from])
// Berechnet "Unendlichkeit" in O(|E|)
#define infty(G, T) T infty = 1; forall_edges(G, from, to, cost) infty += cost;

template <class T>
class bellman_ford {
	std::vector<T> &d;
	network<T> &G;
	int s;
public:

	void relax(int from, int to) {
		if (d[to] > d[from] + G[from][to])
			d[to] = d[from] + G[from][to];
	}

	bellman_ford(network<T>& G_, const int s_, std::vector<T>& d_) : G(G_), d(d_), s(s_) {
		d.resize(G.size());
		infty(G, T);
		for (int i = 0; i < G.size(); i++)
			d[i] = i == s? 0 : infty;

		for (int i = 0; i < G.size(); i++)
			forall_edges(G, from, to, cost)
				relax(from, to);
	}
};


template <class T>
class dijkstra {
	std::vector<T> &d;
	network<T>& G;
	fib_heap_KV<T, int> queue; // Kosten als Key, Knoten als Value/Id
	int s;

public:
	dijkstra(network<T>& G_, const int s_, std::vector<T>& d_): G(G_), d(d_), s(s_) {
		infty(G, T);
		d.resize(G.size());
		std::cout << "size: " << G.size() << "\n";
		for (int i = 0; i < G.size(); i++){ // Abstände initialisieren
			d[i] = i == s ? 0 : infty;
			queue.insert(d[i], i);
		}

		while (!queue.is_empty()){
			T u = queue.extract_min();
			for (auto const& [to, cost]: G[u])
				relax(u, to, cost);
		}
	}

	void relax(int from, int to, int cost) {
		T acc_cost = cost + d[from];
		if (d[to] > acc_cost) {
			d[to] = acc_cost;
			queue.dec_key(to, acc_cost);
		}
	}
};


