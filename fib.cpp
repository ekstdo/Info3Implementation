#include "fib.hpp"
#include <fmt/ranges.h>



int main(int argc, char** argv){
	std::vector<int> nums;
	fib_heap_IKV<int, int, int> fib;
	int seed = time(NULL);
	std::cout << "seed: " << seed << "\n";
	srand(seed);
	float a, b, c, d;
	
	for (int i = 0; i< 10000000; i++){
		nums.push_back(rand());
	}
	a = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i< 10000000; i++){
		fib.insert(i, nums[i], 0);
	}
	b = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i < 10000000; i++){
		int index = random() % nums.size();
		int val = nums[index];
		fib.dec_key(index, val /2);
		nums[index] = val / 2;
	}
	c = (float)clock()/CLOCKS_PER_SEC;
	while (!fib.is_empty()){
		/* fib.print(0); */
		/* std::cout << "MIN: " << i << ": " << fib.find_min() << "\n"; */
		fib.del_min();
	}
	d = (float)clock()/CLOCKS_PER_SEC;
	// fib.print(0);
	std::cout << "</ENDE>\n";
	std::cout << "inserts: " << (b - a) << ", dec_keys: " << (c - b) << ", del_mins: " << (d - c) << "\n";



	return 0;
}
