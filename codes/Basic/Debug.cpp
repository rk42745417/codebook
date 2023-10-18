#ifdef genshin
#define debug(x) cerr << "\e[1;31m" << #x << " = " << (x) << "\e[0m\n"
#define print(x) _my_debug(#x, begin(x), end(x))
template<typename T, typename T2> ostream& operator<<(ostream &os, const pair<T, T2> &obj) {
    return os << '{' << obj.first << ',' << obj.second << '}';
}
template<typename T> void _my_debug(const char *s, T l, T r) {
    cerr << "\e[1;33m" << s << " = [";
    while (l != r) {
        cerr << *l;
        cerr << (++l == r ? ']' : ',');
    }
    cerr << "\e[0m\n";
}
#else
#define debug(x) 48763
#define print(x) 48763
#endif
