/**
 * Author: Sathvik Kuthuru
 * Description: Binomial Coefficient under mod
 * Time: O(MAXN)
 */

const int MAXN = (int) (1e6 + 5);
const int MOD = (int) (1e9 + 7);

ll fact[MAXN], inv_fact[MAXN], inv[MAXN];

void precomp() {
    for(int i = 0; i <= 1; i++) {
        fact[i] = inv_fact[i] = inv[i] = 1;
    }
    for(int i = 2; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        inv_fact[i] = (inv_fact[i - 1] * inv[i]) % MOD;
    }
}

ll binomial(int n, int k) {
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}
