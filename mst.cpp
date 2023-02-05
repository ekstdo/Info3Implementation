#include <vector>
#include <tuple>
#include "unionfind.hpp"
#include "sssp.hpp"

template <class T>
using edge = std::tuple<int, int, T>;

template <class T>
std::vector<edge<T>> kruskal(network<T>& N) {
	unionfind_compressed uf(N.size());
	std::vector<edge<T>> edge_list;
	std::vector<edge<T>> resulting;

	forall_edges(N, from, to, cost){
		edge_list.push_back(std::make_pair(from, to, cost));
	}

	edge_list.sort(edge_list.begin(), edge_list.end(), [](edge<T> l, edge<T> r) { return std::get<2>(l) < std::get<2>(r); });

	while (!edge_list.empty()) {
		edge<T> e = edge_list.pop();
		int u = std::get<0>(e);
		int v = std::get<1>(e);

		if (uf.find(u) != uf.find(v)) {
			resulting.push_back(e);
			uf.union_(uf.find(u), uf.find(v));
		}
	}

	return resulting;
}

template <class T>
std::vector<edge<T>> prim(network<T>& N){
	std::vector<int> d(N.size());
	fib_heap_KV<T, int> queue;

	std::vector<edge<T>> resulting;

	infty(N, T);

	for (int i = 0; i < N.size(); i ++){
		d[i] = infty;
		queue.insert(d[i], i);
	}

	std::vector<edge<T>> link;
	while (!queue.empty()){
		int u = queue.extract_min();
		if (d[u] < infty) resulting.push_back(link[u]);
		for (const auto& [to, cost]: N[u]) {
		}
	}
}
