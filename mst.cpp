#include <vector>
#include <tuple>
#include "unionfind.hpp"
#include "sssp.hpp"

template <class T>
using edge = std::tuple<int, int, T>;

template <class T>
std::vector<std::tuple<int, int>> kruskal(network<T> N) {
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

