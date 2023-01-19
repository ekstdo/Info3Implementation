#include <functional>
#include <list>
#include <tuple>
#include <vector>
#include <numeric>
#include <map>


template <class T>
using network = std::vector<std::map<int,T>>; // node and cost

#define forall_edges(G, from, to, cost) for (int from = 0; from < G.size(); from++) for (auto const &[to, cost]: G[from])

template <class T>
class bellman_ford {
	std::vector<T> &d;
	network<T> &G;
	int s;

	void init(){
		d.resize(G.size());
		T infty = 1;
		forall_edges(G, from, to, cost) {
			infty += cost;
		}
		for (int i = 0; i < G.size(); i++){
			d[i] = i == s? 0 : infty;
		}
	}

	void relax(int from, int to) {
		if (d[to] > d[from] + G[from][to])
			d[to] = d[from] + G[from][to];
	}

	bellman_ford(const network<T>& G_, const int s_, std::vector<T>& d_) : G(G_), d(d_) {
		s = s_;
		init();

		for (int i = 0; i < G.size(); i++) {
			forall_edges(G, from, to, cost)
				relax(from, to);
		}
	}
};

int main(){

}
