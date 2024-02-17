/**
 * Source: cp-algo
 * Description: Computes answer for the josephus problem
 * for large n and small k in klogn
 */

int josephus(int n, int k) {
    if(n == 1) return 0;
    if(k == 1) return n - 1;
    if(k > n) return (josephus(n-1, k) + k) % n;
    int cnt = n / k, res = josephus(n - cnt, k);
    res -= n % k;
    if(res < 0) res += n;
    else res += res / (k - 1);
    return res;
}
