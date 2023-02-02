#include <vector>
#include <fmt/ranges.h>
#include <numeric>
#include <stack>
#include <algorithm>

#ifndef UNIONFIND_H
#define UNIONFIND_H

class unionfind_compressed {
public:
	std::vector<int> F, size;
	int n;
	unionfind_compressed(int n): F(n), size(n, 1), n(n) {
		std::iota (std::begin(F), std::end(F), 0);
	}

	int union_(int v, int w) {
		if (size[v] < size[w]) {
			F[v] = w; // die kleinere Gruppe wird umbenannt
			size[w] += size[v];
			return w;
		} else {
			F[w] = v;
			size[v] += size[w];
			return v;
		}
	}

	int find(int v){
		std::stack<int> s;
		while (F[v] != v) {
			s.push(v);
			v = F[v];
		}

		while (!s.empty()) { F[s.top()] = v; s.pop(); }
		return v;
	}

	void find_all(){
		for (int i = 0; i < n; i ++){
			fmt::print("{} ", find(i));
		}
		fmt::print("\n");
	}
};

class UnionFind_interface {
public:
	unionfind_compressed c;
	int n;
	std::vector<int> to_real, to_renamed;
	UnionFind_interface(int n): c(n), to_real(n), to_renamed(n), n(n) {
		std::iota(std::begin(to_real), std::end(to_real), 0);
		std::iota(std::begin(to_renamed), std::end(to_renamed), 0);
	}

	void union_(int v, int w){
		int v_real = to_real[v];
		int w_real = to_real[w];
		int w_out = c.union_(v_real, w_real);
		if (w_real != w_out) {
			to_renamed[v_real] = w;
			to_real[w] = v_real;
		}
	}

	int find(int v){
		return to_renamed[c.find(to_real[v])];
	}

	void find_all(){
		for (int i = 0; i < n; i ++){
			fmt::print("{} ", find(i));
		}
		fmt::print("\n");
	}
};

std::vector<int> offline_min(std::vector<int>& eingabe) {
	// D wird als -1 dargestellt
	int n = *std::max_element(eingabe.begin(), eingabe.end());
	UnionFind_interface uf(n + 2);
	std::vector<int> ndelete(n + 1, -1);
	int numOfDeletes = 0;

	// die Anzahl an Deletes zählen
	for (int i: eingabe)
		if (i == -1) 
			numOfDeletes++;
		else 
			ndelete[i] = numOfDeletes;

	std::vector<int> resulting(numOfDeletes, -1);

	// die Positionen rausfinden
	for (int i = 0; i <= n; i ++){
		if (ndelete[i] == -1) 
			continue;

		int position = uf.find(ndelete[i]);
		if (position < numOfDeletes)
			resulting[position] = i;
		uf.union_(position, uf.find(position + 1));
	}

	return resulting;
}

#endif
