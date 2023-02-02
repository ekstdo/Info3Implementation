#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#define INIT_SIZE 5

template <class T>
class bin_heap {
public:
	std::vector<T> inner;
	int n;
	void sift_down(int from, int end) {
		while (1){
			int child = 2 * from + 1;
			if (child > end)
				break;
			if (child < end && inner[child + 1] < inner[child])
				child ++;
			if (inner[from] > inner[child]){
				std::swap(inner[from], inner[child]);
				from = child;
			} else break;
		}
	}

	void sift_up(int from) {
		int next;
		while (from > 0 && inner[from] < inner[next = (from + 1)/2 - 1] ){
			std::swap(inner[from], inner[next]);
			from = next;
		}
	}
	bin_heap(): inner(INIT_SIZE) { n = 0; }
	void insert(T x){
		n ++;
		inner.push_back(x);
		sift_up(n);
	}

	T find_min(){
		return inner[0];
	}

	void del(int i){
		inner[i] = inner[n --];
		inner.pop_back();
		if (i <= n) {
			sift_down(i, n);
			sift_up(i);
		}
	}

	void decrease_key_by_index(int i, int new_key){
		inner[i] = new_key;
		sift_up(i);
	}

	void decrease_key(int old_key, int new_key){
		for (int i = 0; i < inner.size(); i++){
			if (inner[i].key == old_key){
				decrease_key_by_index(i, new_key);
			}
		}
	}
};


int main(){
	bin_heap<int> binheap;
	std::vector<int> nums;

	int seed = time(NULL);
	std::cout << "seed: " << seed << "\n";
	srand(seed);

	float a, b, c, d;

	
	for (int i = 0; i< 1000000; i++){
		nums.push_back(rand());
	}
	a = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i < 1000000; i++){
		binheap.insert(random());
	}

	b = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i < 1000000; i++){
		int index = random() % nums.size();
		binheap.decrease_key_by_index(index, binheap.inner[index] / 2);
	}
	c = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i < 1000000; i++){
		binheap.del(0);
	}
	d = (float)clock()/CLOCKS_PER_SEC;
	std::cout << "</ENDE>\n";
	std::cout << "inserts: " << (b - a) << ", dec_keys: " << (c - b) << ", del_mins: " << (d - c) << "\n";
}
