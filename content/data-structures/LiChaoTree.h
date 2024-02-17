/**
 * Source: https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html
 * Description: You’re given a set S containing function of the same “type” 
 * (ex. lines, y=ax+b). The type of function need to have the transcending property 
 * (will be explained later). You need to handle two type of queries:
 * 
 * Add a function to S
 * Answer the maximum/minimum value at x=t considering all functions in S
 * 
 * Transcending Property:
 * Given two functions f(x),g(x) of that type, if f(t) is greater
 * than/smaller than g(t) for some x=t, then f(x) will be 
 * greater than/smaller than g(x) for x>t. In other words, once f(x) “win/lose” 
 * g(x), f(x) will continue to “win/lose” g(x).
 */

const int MAXN = (int) (1e5 + 5);

struct Line {
  ld m, b;
  ld operator()(ld x) { return m * x + b; }
} a[MAXN * 4];

// Insert and query are inclusive-exclusive: [L, R)
void insert(int l, int r, Line seg, int o=0) {
  if(l + 1 == r) {
    if(seg(l) > a[o](l)) a[o] = seg;
    return;
  }
  int mid= (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
  if(a[o].m > seg.m) swap(a[o], seg);
  if(a[o](mid) < seg(mid)) {
    swap(a[o], seg);
    insert(l, mid, seg, lson);
  }
  else insert(mid, r, seg, rson);
}

ld query(int l, int r, int x, int o=0) {
  if(l + 1 == r) return a[o](x);
  int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
  if(x < mid) return max(a[o](x), query(l, mid, x, lson));
  else return max(a[o](x), query(mid, r, x, rson));
}
