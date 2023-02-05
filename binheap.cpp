#include "binheap.hpp"

int main(){
	bin_heap_KV<int, int> binheap;
	std::vector<int> nums;

	int seed = time(NULL);
	std::cout << "seed: " << seed << "\n";
	srand(seed);

	float a, b, c, d;

	
	for (int i = 0; i< 10000000; i++){
		nums.push_back(rand());
	}
	a = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i < 10000000; i++){
		binheap.insert(random(), i);
	}

	b = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i < 10000000; i++){
		int index = random() % nums.size();
		int val = nums[index];
		binheap.dec_key(index, val /2);
		nums[index] = val / 2;
	}
	c = (float)clock()/CLOCKS_PER_SEC;
	while (!binheap.is_empty()){
		binheap.del_min();
	}
	d = (float)clock()/CLOCKS_PER_SEC;
	std::cout << "</ENDE>\n";
	std::cout << "inserts: " << (b - a) << ", dec_keys: " << (c - b) << ", del_mins: " << (d - c) << "\n";
}
