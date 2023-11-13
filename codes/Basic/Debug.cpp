#ifdef genshin
#include <experimental/iterator>
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) debug_(#a, a)
#define print(a...) print_(#a, a)
void debug_(const char *s, auto ...a) {
    cerr << "\e[1;31m(" << s << ") = (";
    int f = 0;
    (..., (cerr << (f++ ? ", " : "") << a));
    cerr << ")\e[0m\n";
}
void print_(const char *s, auto L, auto R) {
    cerr << "\e[1;33m[ " << s << " ] = [ ";
    using namespace experimental;
    copy(L, R, make_ostream_joiner(cerr, ", "));
    cerr << " ]\e[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) safe
#define print(...) safe
#endif
