#include <vector>
#include <fmt/core.h>
#include <iterator>
#include <list>

using adjazenzliste = std::vector<std::list<int>>;
struct elem_qz;
using querzeiger = std::list<elem_qz>::iterator;
struct elem_qz {
	querzeiger ptr;
	int elem;
};

using quer_adjazenzliste = std::vector<std::list<elem_qz>>;

quer_adjazenzliste umwandeln(adjazenzliste& A){
	int n = A.size();
	quer_adjazenzliste A_prime(n);

	for (int i = 0; i < n; i++)
		A_prime[i] = {};

	for (int i = 0; i < n; i ++){
		for (int neighbor: A[i]){
			if (i > neighbor){
				A_prime[i].push_back({A_prime[neighbor].rend().base(), neighbor});
				A_prime[neighbor].push_back({A_prime[i].rend().base(), i});
				A_prime[i].back().ptr = A_prime[neighbor].rend().base();
			}
		}
	}

	return A_prime;
}

int main(){
	adjazenzliste A = {{1, 2}, {0}, {0}};
	quer_adjazenzliste A_prime = umwandeln(A);

	for (std::list<elem_qz> l: A_prime){
		for (elem_qz k: l){
			fmt::print("{} ", k.elem);
		}
		fmt::print("\n");
	}

	elem_qz a = A_prime[0].front();
	A_prime[0].erase(A_prime[0].begin());
	A_prime[a.elem].erase(a.ptr);

	for (std::list<elem_qz> l: A_prime){
		for (elem_qz k: l){
			fmt::print("{} ", k.elem);
		}
		fmt::print("\n");
	}
}
