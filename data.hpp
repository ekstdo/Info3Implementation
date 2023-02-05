#include <iostream>
#include <unordered_map>


template <class K, class V>
struct dataKV {
	K key;
	V value;

	bool operator<=(const dataKV<K, V>& rhs){ return key <= rhs.key; }
	bool operator>=(const dataKV<K, V>& rhs){ return key >= rhs.key; }
	bool operator<(const dataKV<K, V>& rhs){ return key < rhs.key; }
	bool operator>(const dataKV<K, V>& rhs){ return key > rhs.key; }

	V get_id() { return value; }
};

template <class I, class K, class V>
struct dataIKV {
	I id;
	K key;
	V value;

	bool operator<=(const dataIKV<I, K, V>& rhs){ return key <= rhs.key; }
	bool operator>=(const dataIKV<I, K, V>& rhs){ return key >= rhs.key; }
	bool operator<(const dataIKV<I, K, V>& rhs){ return key < rhs.key; }
	bool operator>(const dataIKV<I, K, V>& rhs){ return key > rhs.key; }

	I get_id() { return id; }
};


template <class H, class N, class I, class K, class V>
class heap_IKV {
public:
	H heap;
	std::unordered_map<V, N> lookup;

	heap_IKV(): heap(), lookup() {}

	void insert(I id, K key, V val){
		if (lookup.find(id) != lookup.end()) {
			std::cout << "id " << id << " already exists D:<\n";
			return;
		}
		lookup[id] = heap.insert({id, key, val});
	}

	bool is_empty(){
		return heap.n == 0;
	}

	V find_min(){
		return heap.find_min().value;
	}

	void del_min(){
		lookup.erase(heap.min->inner.id);
		heap.del_min();
	}

	void dec_key(I id, K key_new){
		auto n = lookup.find(id);
		if (n == lookup.end()) {
			std::cout << "Id " << id << " doesn't exist!\n";
			return;
		}
		heap.dec_key(n->second, {id, key_new, heap.get_inner(n->second).value});
	}

	V extract_min(){
		V min_val = find_min();
		del_min();
		return min_val;
	}
};

template <class H, class N, class K, class V>
class heap_KV {
public:
	H heap;
	std::unordered_map<V, N> lookup;

	heap_KV() : heap(), lookup() {}

	void insert(K key, V val){
		if (lookup.find(val) != lookup.end()) {
			std::cout << "id/val " << val << " already exists D:<\n";
			return;
		}
		lookup[val] = heap.insert({key, val});
	}

	V find_min(){
		return heap.find_min().value;
	}

	void del_min(){
		lookup.erase(find_min());
		heap.del_min();
	}

	void dec_key(V val, K key_new){
		auto n = lookup.find(val);
		if (n == lookup.end()) {
			std::cout << "Id " << val << " doesn't exist!\n";
			return;
		}
		heap.dec_key(n->second, {key_new, heap.get_inner(n->second).value});
	}

	bool is_empty() {
		return heap.n == 0;
	}

	V extract_min(){
		V min_val = find_min();
		del_min();
		return min_val;
	}
};
