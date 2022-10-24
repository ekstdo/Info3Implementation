#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

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
void swap(T& x, T& y){
	T t = x; x = y; y = t;
}

template <class T>
int partition(std::vector<T> &A, int p, int r, int t){
	T x = A[t];
	A[t] = A[p];

	int i = p;
	for (int j = p + 1; j < r; j ++)
		if (A[j] < x)
			swap(A[++i], A[j]);
	
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
		swap(A[a], A[0]);
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
			swap(A[el], A[child]);
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

#define DEBUG 1 

template <class T>
class node {

#if DEBUG == 1 
public:
#endif 
	T inner;
	int degree;
	bool excited;
	node<T> *parent, *child, *left, *right;
#if DEBUG != 1 
public: 
#endif 
	node(T inner, node<T> *parent, node<T> *child, node<T> *left, node<T> *right, int degree, bool excited) 
		: degree(degree), excited(excited) {
		this->inner = inner;
		this->parent = parent;
		this->child = child;
		this->left = left;
		this->right = right;
	}

	node() { this->left = this; this->right = this; this->degree = 0; }

	node(T inner) {
		this->inner = inner;
		this->parent = NULL;
		this->child = NULL;
		this->left = this;
		this->right = this;
		this->degree = 0;
	}

	node(std::vector<T> inner){
		node<T> *next = this; 
		node<T> *previous = this;
		for (T elem: inner){
			next->inner = elem;
			next->parent = NULL;
			next->child = NULL;
			next->left = previous;
			previous = next;
			
			next->right = new node();
			next = next->right;
		}
		previous->right = this;
		this->left = previous;
		this->degree = 0;
	}

	node(T val, node<T>* child){
		this->left = this; 
		this->right = this;
		this->inner = val;
		this->child = child;
		this->parent = nullptr;
		this->degree = child->length();
		child->reparent(this);
	} 

	int length(){
		int returning = 0; 
		node<T> *next = this;
		do { returning ++; next = next->right; }
		while (next != this);
		return returning;
	}

	static void connect( std::vector<node<T>*> inner ){ 
		node<T>* prev = inner.back();
		for (node<T>* n : inner) {
			n->left = prev;
			n->left->right = n;
			prev = n;
		}
	}

	static node<T>* connect( std::vector<node<T>*> inner, bool nullskip ){ 
		int i = inner.size() - 1;
		while (inner[i] == NULL) {
			i --;
			inner.pop_back();
		}
		node<T>* prev = inner[i];
		node<T>* min = inner[i];
		for (node<T>* n : inner) {
			if (nullskip && n == NULL) continue;
			if (n->inner < min->inner) min = n;
			n->left = prev;
			n->left->right = n;
			prev = n;
		}

		return min;
	}

	node<T>* merge(node<T> *other){
		node<T> *larger;
		node<T> *smaller;
		if (this->inner < other->inner) {
			larger = other;
			smaller = this;
		} else {
			larger = this;
			smaller = other;
		}
		if (smaller->child == NULL) {
			larger->left = larger;
			larger->right = larger;
			smaller->child = larger;
		} else {
			larger->right = smaller->child; // einfügen in die Liste des Kleineren
			larger->left = smaller->child->left;
			smaller->child->left->right = larger;
			smaller->child->left = larger;
		}

		larger->parent = smaller;
		smaller->degree += 1;
		return smaller;
	}

	void reparent(node<T>* parent){
		node<T> *next = this; 
		do { next->parent = parent; next = next->right; } while (next != this);
	}

	void print_only(int direction) { 
		std::string cur_prefix = "└──";
		std::string this_prefix = "    ";
		std::cout << cur_prefix << " " << this->inner << ":   " << this->degree << "\n";
		if (this->child != NULL) {
			this->child->print(this_prefix, direction);
		}
	}

	void print(std::string prefix, int direction) {
		node<T> *next = this;
		int counter = 0;
		do {
			if (counter == 10 || prefix.length() > 15) {
				std::cout << prefix << "└── ...\n";
				break;
			}

			std::string cur_prefix = (direction == 0? next->right : next->left) == this ? "└──" : "├──";
			std::string next_prefix =  (direction == 0? next->right : next->left) == this? "    " : "│   ";
			std::cout << prefix << cur_prefix << " " << next->inner << ":   " << next->degree << (next->excited ? "⏹" : "") << "  ← ";
			if (next->parent == NULL) std::cout << "◌" ; else std::cout << next->parent->inner; std::cout << "\n";
			if (next->child != NULL) {
				next->child->print(prefix + next_prefix, direction);
			}


			if (direction == 0)
				next = next->right;
			else 
				next = next->left;
			counter ++;
		} while (next != this);
	}

	void add_child(node<T>* child){
		if (this->child == NULL)
			this->child = child;
		else {
			child->left = this->child->left;
			child->right = this->child;
			this->child->left->right = child;
			this->child->left = child;
		}
		child->parent = this;
		this->degree++;
	}

	void add_child(T value){
		node<T>* child = new node<T>(value);
		add_child(child);
	}

	void remove_child(node<T>* some_child) {
		// should have at least one child before calling this function 
		if (this->child == this->child->left){ // if it has only one child
			this->child = NULL;
			return;
		}
		if (this->child == some_child) // if that child is exactly the child you want to remove
			this->child = some_child->right; 

		some_child->right->left = some_child->left;
		some_child->left->right = some_child->right; 
		some_child->parent = NULL;
	}

	void remove_siblings() { 
		this->left->right = this->right; 
		this->right->left = this->left; 
		if (this->parent != NULL) {
			if (this->parent->child == this) 
				this->parent->child = this->right == this ? NULL : this->right;

			this->parent = NULL;
		}
		this->left = this; 
		this->right = this;
	}

	~node() { 
		delete child; 

		delete right; 
	}

};

template <class T>
class fib_heap {
#if DEBUG == 1
public: // for debugging
#endif 
	int n;
	node<T> *list;
	node<T> *min;

	node<T> *merge_single(node<T>* l, node<T> r){
		node<T> *higher;
		node<T> *lower;
		if (l->inner < r->inner){
		}
		higher->right = lower->child;
		higher->left = lower->child->left;
		l->child = r;
		return lower;
	}
#if DEBUG != 1
public:
#endif
	fib_heap<T>(){
		n = 0; 
		list = nullptr;
		min = nullptr;
	}

	void test(){ 
		node<int>* node_test_child = new node<int>(std::vector<int>{5, 18, 12, 8});
		node_test_child->right->add_child(26);
		node_test_child->left->add_child(8);
		node_test_child->left->add_child(17);
		node<int>* node_test = new node<int>(3, node_test_child);
		node<int>* node15 = new node<int>(15);
		node<int>* node7 = new node<int>(7);
		node7->add_child(12);
		node<int>::connect(std::vector<node<int> *> {node7, node15, node_test});
		this->n = 11;
		this->min = node_test;
		this->list = node7;

	}

	void insert(T el){
          node<T> *new_list =
              new node<T>(el, NULL, NULL, NULL, list, 0, false); // right wurde gesetzt
          node<T> *left = n == 0 ? new_list : list->left;
		  left->right = new_list;
          new_list->left = left;
		  list->left = new_list;
          // Implementierung als zyklische doppelt verkettete Liste
          // right ist also immer NULL
          list = new_list;
          n++;

          if (el < min->inner)
            min = list;
	}

	T find_min(){
		return min->inner;
	}

	void del_min(){
		// minimale Element entfernen und die Kinder davon in die Liste einzufügen
		node<T> *next; // das Element rechts vom Minimum
		if (min->degree == 0) {
			next = min->right;
		} else {
			next = min->child;
			min->child->reparent(NULL);
			min->child->left->right = min->right;
		}
		min->left->right = next;
		next->left = min->left;
		if (list == min){
			list = next;
		}

		delete min;

		// Aufräumen der Bäume
		std::vector<node<T>*> B(n); // NULL init
		node<T> *end = next;

		//std::cout << list->length() << "\n";
		int len = list->length();
		for (int i = 0 ; i < len ; i++){
			while (B[next->degree] != NULL) {
				int current_degree = next->degree;
				node<T> *real_next = next->right;

				next = next->merge(B[current_degree]);
				next->right = real_next;
				B[current_degree] = NULL;
			}
			B[next->degree] = next;

			next = next->right;

			// std::for_each(B.begin(), B.end(), [](node<T>* n){ if (n == NULL) std::cout << "NULL, \n"; else n->print_only("");  });
			// std::cout << "\n\n\n\n\n\n";
		}

		// std::cout << "B: \n"; std::for_each(B.begin(), B.end(), [](node<T>* n){ if (n == NULL) std::cout << "NULL, \n"; else n->print_only("");  });
		min = node<T>::connect(B, true);
		list = min;

		n--;
	}

	void dec_key(node<T> *n, T new_val){ 
		if (new_val > n->inner) {
			std::cout << "supplied value is larger than existing value\n";
			return;
		}
		n->inner = new_val; 
		if (n->parent == NULL) {
			if (n->inner < min->inner) 
				min = n; // bei einem Wurzelknoten auf min achten
			return;
		}
		if (n->parent->inner < n->inner)
			return; // heap Eigenschaft wird nich verletzt 
		
		node<T>* parent = n->parent;
		parent->remove_child(n);

		add(n);
		n->excited = false;
		if (parent->excited) 
			cutout(parent);
		else 
			parent->excited = true;
	}

	void cutout(node<T> *n) { 
		if (n->parent == NULL) return; // nothing to do here ._. 
		node<T> *parent = n->parent;
		n->excited = false;
		parent->remove_child(n);
		add(n); 
		if (parent->excited)
			cutout(parent);
		else 
			parent->excited = true;
	}

	void add(node<T>* node) {
		if (this->list == NULL) {
			node->right = node;
			node->left = node;
		} else {
			node->right = this->list; 
			node->left = this->list->left;
			node->left->right = node; 
			node->right->left = node;
		}
		node->parent = NULL;
	}

	void print(int direction){
		std::cout << "fib heap: " << n << "\n";

		list->print("", direction);
	}

	~fib_heap() { 
	}
};


void test_fib_heap(){ 
	fib_heap<int> fib;
	fib.test();
/*	fib.print(0);*/
/*	fib.print(1); */

/* 	𝑖𝑛𝑡 𝑛 = 𝑓𝑖𝑏.𝑓𝑖𝑛𝑑ₘ𝑖𝑛(); */
	fib.del_min();

/* 	𝑠𝑡𝑑∶∶𝑐𝑜𝑢𝑡 << "𝑟𝑒𝑠𝑢𝑙𝑡∶ " << 𝑛 << "\𝑛"; */ 

	fib.print(0);
/* 	/1* 𝑓𝑖𝑏.𝑝𝑟𝑖𝑛𝑡(1); *1/ */

/* 	𝑛 = 𝑓𝑖𝑏.𝑓𝑖𝑛𝑑ₘ𝑖𝑛(); */
/* 	𝑠𝑡𝑑∶∶𝑐𝑜𝑢𝑡 << "𝑟𝑒𝑠𝑢𝑙𝑡∶ " << 𝑛 << "\𝑛"; */ 

/* 	𝑓𝑖𝑏.𝑑𝑒𝑙ₘ𝑖𝑛(); */
/* 	𝑓𝑖𝑏.𝑝𝑟𝑖𝑛𝑡(0); */

/* 	𝑓𝑖𝑏.𝑖𝑛𝑠𝑒𝑟𝑡(3); */
/* 	𝑓𝑖𝑏.𝑖𝑛𝑠𝑒𝑟𝑡(7); */
	/* 	𝑓𝑖𝑏.𝑖𝑛𝑠𝑒𝑟𝑡(11); */
/* 	𝑓𝑖𝑏.𝑖𝑛𝑠𝑒𝑟𝑡(55); */
/* 	𝑓𝑖𝑏.𝑝𝑟𝑖𝑛𝑡(0); */

/* 	𝑓𝑖𝑏.𝑑𝑒𝑙ₘ𝑖𝑛(); */
/* 	𝑓𝑖𝑏.𝑝𝑟𝑖𝑛𝑡(0); */

	// fib.dec_key(fib.list->left, 12); //  sollte die msg ausprinten 
	// fib.dec_key(fib.list->right, 12); // sollte eifnach so funktionieren
	/*fib.dec_key(fib.list->right, 1); // sollte das neue min setzen
	int n = fib.find_min(); // sollte 1 sein 
	std::cout << n << "\n";*/
	// fib.dec_key(fib.list->left->child, 2); // sollte dann zu ner Wurzel werden
	// fib.dec_key(fib.list->left->child->right, 2); // sollte dann zu ner Wurzel mit Kind werden
	
	// fib.dec_key(fib.list->left->child->right, 2); // sollte zu einer Wurzel ohne neuem Kind werden
	fib.dec_key(fib.list->child->left, 2);
	fib.print(0);
	fib.dec_key(fib.list->child, 3);
	fib.print(0);
}


int main(int argc, char** argv){
	std::vector<int> v = {2,4, 3, 2, 3,1, 8, 0};
	std::vector<int> v_clone = v;
	int q = v.size();
	for (int i : insertion_sort(v)){ 
		std::cout << i << " ";
	}
	std::cout << "\n";

	fib_heap<int> test;

	std::vector<int> w = {2, 4, 6, 7};
	v.insert(v.end(), w.begin(), w.end());


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

	for (int i : counting_sort(v_clone)){ 
		std::cout << i << " ";
	}
	std::cout <<"\n";



	/*
	int res = partition(v_clone, 0, v_clone.size(), 1);
	for (int i : v_clone){ 
		std::cout << i << " ";
	}
	std::cout << "\n" << res <<"\n";
	*/

	test_fib_heap();

	return 0;
}
