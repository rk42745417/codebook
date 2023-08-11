// Return Z value of string s in O(|S|)
// Note that z[0] = |S|
vector<int> Zalgo(const string &s) {
  vector<int> z(s.size(), (int) s.size());
  for (int i = 1, l = 0, r = 0; i < z[0]; ++i) {
    int j = clamp(r - i, 0, z[i - l]);
    while (i + j < z[0] && s[i + j] == s[j])
        j++;
    if (i + (z[i] = j) > r)
        r = i + z[l = i];
  }
  return z;
}
