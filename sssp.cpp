#include "sssp.hpp"

int main(){
	int seed = 5000;
	int num_nodes = 10;
	int num_edges = 50;
	srand(5000);
	network<int> random_network(num_nodes);
	for (int i = 0; i < num_edges; i++) {
		int ind = random() % num_nodes;
		int ind2 = random() % num_nodes;
		ind2 = ind2 == ind ? (ind2 + 1) % num_nodes : ind2;
		random_network[ind][ind2] = random() % 100;
	}

	fmt::print("{}\n", random_network);

	std::vector<int> d;
	std::vector<int> d2;
	bellman_ford<int>(random_network, 0, d);
	fmt::print("{}\n", d);
	dijkstra<int>(random_network, 0, d2);
	fmt::print("{}\n", d2);
}
