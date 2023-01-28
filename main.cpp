#include <cstdlib>
#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <stdlib.h>
#include <algorithm>

#define GOLDEN_RATIO 1.618033988749894
const double G_INV = 1.0 / log(GOLDEN_RATIO);


#define DEBUG 1 

template <class T>
T quick_default(T a, T def){
	if (a == NULL)
		return def;
	return a;
}

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
		: degree(degree), excited(excited), inner(inner), parent(parent), child(child), left(left), right(right) {
	}

	node() : node((T) NULL, NULL, NULL, this, this, 0, false) {}

	node(T inner) : node() {
		this->inner = inner;
	}

	node(T val, node<T>* child): node(val) {
		this->child = child;
		this->degree = child->length();
		child->reparent(this);
	}

	bool lone_child(){
		bool tr = this->right == this;
		bool tl = this->left == this;
		if (tr ^ tl) {
			std::cout << "WARNING: unsure lone child!\n";
		}
		return tr && tl;
	}

	void insert_sibling(T val){ // inserts another sibling into the list
		node<T> *n = new node(val, parent, NULL, this->left, this, 0, false);

		this->left->right = n;
		this->left = n;
	}

	void reparent(node<T>* parent){ // reparents the node and its siblings
		node<T> *next = this; 
		do { next->parent = parent; next = next->right; } while (next != this);
	}

	void reset_pred(){
		this->left = this;
		this->right = this;
		this->parent = NULL;
	}

	void isolate_adopt(){
		bool is_lone = lone_child();
		if (this->parent != NULL && this->parent->child == this)
			this->parent->child = this->next_or_child();
		
		if (this->child == NULL) {
			this->right->left = this->left;
			this->left->right = this->right;
		} else if (!is_lone) {
			this->right->left = this->child->left;
			this->left->right = this->child;
			this->child->reparent(this->parent);
			this->child->left->right = this->right;
			this->child->left = this->left;
		}
		reset_pred();
	}

	void isolate_with_child(){
		bool is_lone = lone_child();
		if (this->parent != NULL && this->parent->child == this)
			this->parent->child = this->next();
		
		this->right->left = this->left;
		this->left->right = this->right;
		reset_pred();
	}


	node<T>* next(){
		return this->right == this ? NULL : this->right;
	}

	node<T>* next_or_child(){
		return quick_default(this->next(), this->child);
	}

	void remove_parent(){
		reparent(NULL);
	}

	void concat(node<T>* val){ // concatenates 2 nodes to become siblings
		val->reparent(parent);
		node<T>* last_val = val->left;
		last_val->right = this;
		val->left = this->left;

		this->left->right = val;
		this->left = last_val;
	}

	node(std::vector<T> inner): node(inner[0]) {
		for (auto it = inner.begin() + 1; it != inner.end(); ++it){
			insert_sibling(*it);
		}
	}

	int length(){
		int returning = 0; 
		node<T> *next = this;
		do { returning ++; next = next->right; } while (next != this);
		return returning;
	}

	static node<T>* init_or_insert(node<T>* list, T val){
		if (list == NULL){
			return new node<T>(val);
		}
		list->insert_sibling(val);
		return list;
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
		auto const& [smaller, larger] = std::minmax(this, other, [](node<T>* a, node<T>* b){ return a->inner < b->inner; });

		larger->isolate_with_child();
		smaller->add_children(larger);

		return smaller;
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

	void add_children(node<T>* child){
		int l = child->length();
		if (this->child == NULL){
			child->reparent(this);
			this->child = child;
		} else {
			this->child->concat(child); 
		}
		this->degree += l;
	}

	void add_single_child(T value){
		node<T>* child = new node<T>(value);
		add_children(child);
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
};

template <class T>
class fib_heap {
#if DEBUG == 1
public: // for debugging
#endif 
	int n;
	node<T> *list;
	node<T> *min;
#if DEBUG != 1
public:
#endif
	fib_heap<T>(){
		n = 0; 
		list = nullptr;
		min = nullptr;
	}
	void insert(T el){
          list = node<T>::init_or_insert(list, el);
          n++;

		  if (min == nullptr)
				min = list;
		  else if (el < min->inner)
				min = list->left; // insertion fügt links hinzu
	}

	T find_min(){
		return min->inner;
	}

	void del_min(){
		if (n-- == 0) {
			std::cout << "I have no elements left D:\n";
			return;
		}

		// minimale Element entfernen und die Kinder davon in die Liste einzufügen
		if (min == list)
			list = min->next_or_child();

		
		min->isolate_adopt();
		/* this->print(0); */
		delete min;
		if (list == NULL)
			return;
		list->remove_parent();
		/* std::cout << "after delete\n"; */
		/* this->print(0); */
		// Aufräumen der Bäume
		std::vector<node<T>*> B(ceil(log((double) n) * G_INV) + 2, NULL); // NULL init
		node<T>* next = list;
		node<T> *end = next;

		// std::cout << list->length() << "\n";
		int len = list->length();
		for (int i = 0 ; i < len ; i++){
			/* std::cout << "yyoooo right\n"; */
			/* next->right->print_only(0); */
			/* if (next == NULL){ */
			/* 	std::cout << "what\n"; */
			/* } */
			node<T>* succ = next->right;
			while (B[next->degree] != NULL) {
				/* std::cout << "merge\n"; */
				int current_degree = next->degree;
				next = next->merge(B[current_degree]);
				B[current_degree] = NULL;
			}
			B[next->degree] = next;

			/* if (next->right == NULL){ */
			/* 	std::cout << "FML\n"; */
			/* } */
			next = succ;

			/* std::for_each(B.begin(), B.end(), [](node<T>* n){ if (n == NULL) std::cout << "NULL, \n"; else n->print_only(0);  }); */
			/* std::cout << "next:\n\t"; */
			/* next->print_only(0); */
			/* std::cout << "\n\n\n\n\n\n"; */
		}

		// std::cout << "B: \n"; std::for_each(B.begin(), B.end(), [](node<T>* n){ if (n == NULL) std::cout << "NULL, \n"; else n->print_only("");  });
		min = node<T>::connect(B, true);
		list = min;

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

		if (list != NULL)
			list->print("", direction);
	}

	~fib_heap() { 
	}
};



int main(int argc, char** argv){
	fib_heap<int> test;

	fib_heap<int> fib;
	int seed = time(NULL);
	std::cout << "seed: " << seed << "\n";
	srand(seed);
	float a, b, c;
	a = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i< 1000000; i++){
		fib.insert(rand());
	}
	b = (float)clock()/CLOCKS_PER_SEC;
	for (int i = 0; i< 1000000; i++){
		/* fib.print(0); */
		/* std::cout << "MIN: " << i << ": " << fib.find_min() << "\n"; */
		fib.del_min();
	}
	c = (float)clock()/CLOCKS_PER_SEC;
	fib.print(0);
	std::cout << "</ENDE>\n";
	std::cout << (b - a) << ", " << (c - b) << "\n";



	return 0;
}
