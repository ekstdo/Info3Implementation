
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
