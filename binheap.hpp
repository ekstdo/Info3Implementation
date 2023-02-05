#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "data.hpp"

#ifndef BINHEAP_H 
#define BINHEAP_H

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

	int sift_up(int from) {
		int next;
		while (from > 0 && inner[from] < inner[next = (from + 1)/2 - 1] ){
			std::swap(inner[from], inner[next]);
			from = next;
		}
		return from;
	}
	bin_heap(): inner(INIT_SIZE) { n = 0; }
	int insert(T x){
		n ++;
		inner.push_back(x);
		return sift_up(n);
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

	void del_min(){
		del(0);
	}

	void dec_key(int i, T new_key){ // i being the position
		inner[i] = new_key;
		sift_up(i);
	}

	T get_inner(int i){
		return inner[i];
	}
};

template <class K, class V>
using bin_heap_KV = heap_KV<bin_heap<dataKV<K, V>>, int, K, V>;

#endif
