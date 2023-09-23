template<typename T>
using pbds_tree = __gnu_pbds::tree<T, null_type, less<T>,
      rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order: like array accessing, order_of_key
// join: (one should smaller than the other)
// split(v, b): <= v are a, > v are b
template<typename T, typename T2>
using hash_table = __gnu_pbds::gp_hash_table<T, T2>;
// ht.find(a) ht[a] = v
template<typename T>
using rope = __gnu_cxx::rope<T>;
// array stands for string &s, char *s or int *a
// push_back, pop_back, insert(pos, x)
// insert(pos, array, len): from pos, insert len elements of array
// append(array, pos, len): append len elements from pos of array
// substr(pos, len), at(pos), erase(pos, len)
// copy(pos, len, array): from pos, replace len elements from array
// Use = and + to concat substrs, += to append element
// O(log n) or O(1). Use pointer and new for persistent use:
vector<rope<int>*> r(n);
r[0] = new rope<int>();
r[i] = new rope<int>(*r[i - 1]);
r[i]->push_back(i);
