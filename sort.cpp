#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <fmt/ranges.h>

template <class T>
std::vector<T> insertion_sort(std::vector<T>& vec){
	int n = vec.size();

	for (int k = 1; k < n; k++){
		T x = vec[k];

		int i = k - 1;
		while (i >= 0 && x < vec[i]){
			vec[i + 1] = vec[i];
			i--;
		}
		vec[i+1] = x;
	}

	return vec;
}


template <class T>
std::vector<T> merge(std::vector<T> &A, int p, int q, int r){
	std::vector<T> B;
	B.reserve(r - p);
	int i, j;
	for (i = p; i < q; i++) B[i - p] = A[i];
	for (j = r; i < r; i++) B[--j - p] = A[i];
	i = 0; j = r - 1 - p;
	for (int k = p; k < r; k++) A[k] = B[i] < B[j] ? B[i++] : B[j--];
	return A;
}

template <class T>
std::vector<T> merge_sort(std::vector<T> &A, int p, int r){
	if (p < r - 1) {
		int q = (p + r) / 2;
		merge_sort(A, p, q);
		merge_sort(A, q, r);
		merge(A, p, q, r);
	}
	return A;
}

template <class T>
int partition(std::vector<T> &A, int p, int r, int t){
	T x = A[t];
	A[t] = A[p];

	int i = p;
	for (int j = p + 1; j < r; j ++)
		if (A[j] < x)
			std::swap(A[++i], A[j]);
	
	A[p] = A[i];
	A[i] = x;

	return i;
}

int rand_between(int left, int right){ // left inclusive, right exclusive
	return rand() % (right - left) + left;
}

template <class T>
std::vector<T> quick_sort(std::vector<T> &A, int p, int r){
	if (p < r - 1){
		int i = partition(A, p, r, rand_between(p, r));
		quick_sort(A, p, i);
		quick_sort(A, i + 1, r);
	}
	return A;
}

template <class T>
void sift_down(std::vector<T> &A, int el, int end);
template <class T>
std::vector<T> heapify(std::vector<T> &A);

template <class T>
std::vector<T> heap_sort(std::vector<T>& A){
	heapify(A);
	for (int a = A.size() - 1 ; a >= 0; a--){
		std::swap(A[a], A[0]);
		sift_down(A, 0, a - 1);
	}
	return A;
}

template <class T>
void sift_down(std::vector<T> &A, int el, int end){
	while (1){
		int child = 2 * el + 1;
		if (child > end)
			break;
		if (child < end && A[child + 1] < A[child])
			child ++;
		if (A[el] > A[child]){
			std::swap(A[el], A[child]);
			el = child;
		} else break;
	}
}

template <class T>
std::vector<T> heapify(std::vector<T> &A){
	int n =  A.size();
	for (int i = n/2 + 1; i >= 0; i--)
		sift_down(A, i, n -1);
	return A;
}

std::vector<int> counting_sort(std::vector<int> &A){
	int n = A.size();

	int low, high;
	low = high = A[0];

	for (int i = 1; i < n; i++){
		if (A[i] < low) low = A[i];
		if (A[i] > high) high = A[i];
	}

	std::vector<int> M = std::vector<int>(high - low + 1);
	for (int i = 0; i < n; i++)
		M[A[i]]++;

	std::vector<int> B = std::vector<int>(n);
	for (int i = 1; i <= high - low; i ++)
		M[i] += M[i - 1];

	for (int i = 0; i < n; i++)
		B[M[A[i]]-- - 1] = A[i];

	return B;
}

template <class T>
std::vector<T> counting_sort(std::vector<T> &A){
	int n = A.size();

	int low, high;
	low = high = A[0].key;

	for (int i = 1; i < n; i++){
		if (A[i].key < low) low = A[i].key;
		if (A[i].key > high) high = A[i].key;
	}

	std::vector<int> M = std::vector<int>(high - low + 1);
	for (int i = 0; i < n; i++)
		M[A[i].key]++;

	std::vector<T> B = std::vector<T>(n);
	for (int i = 1; i <= high - low; i ++)
		M[i] += M[i - 1];

	for (int i = 0; i < n; i++)
		B[M[A[i].key]--] = A[i];

	return B;
}

void radix_sort(std::vector<int>& A, int basis){
	int n = A.size(), high = *std::max_element(A.begin(), A.end());
	std::vector<int> B(n);
	for (int k = 1; k < high; k *= basis){
		for (int i = 0; i < n; i++){
			B[i] = (A[i] / k) % basis;
			fmt::print("aaaa\n");
			B = counting_sort(B);
		}
	}
}

template<class T>
void radix_sort(std::vector<T>& A, int basis){
	int n = A.size(), high = std::max_element(A.begin(), A.end(), [](T a, T b){ return a.bigkey < b.bigkey;});
	for (int k = 0; k < high; k *= basis){
		for (int i = 0; i < n; i++){
			A[i].key = (A[i].bigkey / k) % basis;
			A = counting_sort(A);
		}
	}
}

template<class T>
void radix_sort(std::vector<T>& A){
	radix_sort(A, A.size());	
}


int main(){
	std::vector<int> L;
	srand(time(NULL));
	for (int i = 0; i < 100; i ++){
		L.push_back(random() );
	}
	fmt::print("{}\n", L);
	radix_sort(L, 10);
	fmt::print("{}\n", L);
}
	/*
	merge(v, 0, q, v.size());
	for (int i : v){ 
		std::cout << i << " ";
	}
	std::cout <<"\n";
	*/

	/*for (int i : merge_sort(v_clone, 0, v_clone.size())){ 
		std::cout << i << " ";
	}
	std::cout <<"\n";*/

	/* for (int i : counting_sort(v_clone)){ */ 
	/* 	std::cout << i << " "; */
	/* } */
	/* std::cout <<"\n"; */



	/*
	int res = partition(v_clone, 0, v_clone.size(), 1);
	for (int i : v_clone){ 
		std::cout << i << " ";
	}
	std::cout << "\n" << res <<"\n";
	*/
