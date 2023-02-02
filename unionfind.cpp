#include "unionfind.hpp"

int main() {
	std::vector<int> v = {2, -1, 3, 1, -1, 7, -1, -1, 0, -1, 4};
	/* std::vector<int> v = {1, 2, -1, 5, 0, -1, -1, -1}; */
	std::vector<int> w = offline_min(v);
	fmt::print("{}\n", w);
	/* UnionFind_compressed c(5); */
	/* int i = c.union_(1, 4); */
	/* fmt::print("F: {}\n", c.F); */
	/* c.find_all(); */
	/* int j = c.union_(0, 2); */
	/* fmt::print("F: {}\n", c.F); */
	/* c.find_all(); */
	/* int k = c.union_(i, j); */
	/* fmt::print("F: {}\n", c.F); */
	/* c.find_all(); */
	/* int l = c.union_(k, 3); */
	/* fmt::print("F: {}\n", c.F); */
	/* c.find_all(); */

	/* std::cout << "BRUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU\n"; */

	/* UnionFind_interface a(5); */
	/* a.union_(1, 4); */
	/* fmt::print("F: {}\n", a.c.F); */
	/* a.find_all(); */
	/* a.union_(0, 2); */
	/* fmt::print("F: {}\n", a.c.F); */
	/* a.find_all(); */
	/* a.union_(4, 2); */
	/* fmt::print("F: {}\n", a.c.F); */
	/* a.find_all(); */
	/* a.union_(2, 3); */
	/* fmt::print("F: {}\n", a.c.F); */
	/* a.find_all(); */
}
