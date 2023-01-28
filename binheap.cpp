#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

template <class T>
class bin_heap {
	std::vector<T> inner;
	int n;
	void sift_down(int from, int end) {
		sift_down(inner, from, end);
	};
	void sift_up(int from) {
		int next;
		while (from > 0 && inner[from] < inner[next = (from + 1)/2 - 1] ){
			swap(inner[from], inner[next]);
			from = next;
		}
	}
public:
	bin_heap(int N): inner(N) { n = 0; }
	void insert(T x){
		inner[++n] = x;
		sift_up(n);
	}

	T find_min(){
		return inner[0];
	}

	void del(int i){
		inner[i] = inner[n --];
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
