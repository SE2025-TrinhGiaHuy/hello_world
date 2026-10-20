#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define MASK(i) ((1LL) << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define fi first
#define se second

using namespace std;

const long inf = 1e9 + 7;
const long Nmax = 1e6 + 7;
const long lg = 20;
const long bs = 1003;

int n, m, k, mod;
ll p[Nmax];
bool kt[Nmax];
vector<int> prime;

void sang()
{
    memset(kt, true, sizeof kt);
    kt[0] = kt[1] = false;
    for (int i = 2; i * i <= 1e6; i++)
    {
        if (kt[i])
        {
            for (int j = i * i; j <= 1e6; j += i)
            {
                kt[j] = false;
            }
        }
    }
    for (int i = 2; i <= 1e6; i++) if (kt[i]) prime.push_back(i);
}

ll POW(int a, int b)
{
    if (b == 0) return 1;
    ll res = a;
    ll cur = a;
    b--;
    while (b > 0)
    {
        if (b & 1) res = res * cur % mod;
        cur = cur * cur % mod;
        b >>= 1;
    }
    return res;
}

ll CKN(int n, int k)
{
    return p[n] * POW(p[k], mod - 2) % mod * POW(p[n - k], mod - 2) % mod;
}

int cnt_divs(int n, int v)
{
    ll power = v;
    int res = 0;
    while (power <= n)
    {
        res += n / power;
        power *= v;
    }
    return res;
}

ll cal_ckn(int n, int k)
{
    ll res = 1;
    for (auto v : prime)
    {
        res = res * POW(v, cnt_divs(n, v) - cnt_divs(k, v) - cnt_divs(n - k, v));
        res %= mod;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("flowers.inp","r",stdin);
    freopen("flowers.out","w",stdout);
    int t;
    cin >> t >> mod;
    p[0] = 1;
    for (int i = 1; i <= 1e6; i++) p[i] = (p[i - 1] * i) % mod;
    sang();
//    cerr << prime.size();
    for (int hung = 1; hung <= t; hung++)
    {
        cin >> n >> m >> k;
        if (t > 50) cout << CKN(n - 1, k) * m % mod * POW(m - 1, k) % mod << "\n";
        else
        {
            if (mod == 998244353)
            {
                ll res = 1;
                for (int i = n - k; i <= n - 1; i++) res = (res * i) % mod;
                res = (res * POW(p[k], mod - 2)) % mod;
                cout << (res * m) % mod * POW(m - 1, k) % mod << "\n";
            }
            else cout << cal_ckn(n - 1, k) * m % mod * POW(m - 1, k) % mod << "\n";
        }
    }
}
