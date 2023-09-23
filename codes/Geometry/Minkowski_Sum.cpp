// If we want to calculate the minkowski sum of vectors,
// sort <v_i, -v_i, v_{i + 1}, -v_{i + 1}, ...> by polar angle order
// The prefiex sum of vectors is a convex polygon and is the minkowski sum
// To get the new origin, compare the max (x, y) of the convex and the sum of positive (x, y) of the vectors

// A, B are convex hull rotated to min by (X, Y)
// i.e. rotate(A.begin(), min_element(all(A)), A.end())
vector<point> Minkowski(vector<point> A, vector<point> B) {
    vector<point> C(1, A[0] + B[0]), s1, s2;
    const int N = (int) A.size(), M = (int) B.size();
    for(int i = 0; i < N; ++i)
        s1.push_back(A[(i + 1) % N] - A[i]);
    for(int i = 0; i < M; i++)
        s2.push_back(B[(i + 1) % M] - B[i]);
    for(int i = 0, j = 0; i < N || j < M;)
        if (j >= N || (i < M && cross(s1[i], s2[j]) >= 0))
            C.push_back(C.back() + s1[i++]);
        else
            C.push_back(C.back() + s2[j++]);
    return convex_hull(C);
}
