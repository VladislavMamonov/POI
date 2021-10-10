#include "CryptoLib.hpp"


int64 ipow(int64 a, int64 n)
{
    int64 r = 1;

    for (int64 i = 0; i < n; i++) r *= a;

    return r;
}


bool isPrime(uint64 p)
{
   if (p <= 1) return false;

   uint64 b = pow(p, 0.5);

   for (uint64 i = 2; i <= b; ++i) {
      if ((p % i) == 0) return false;
   }

   return true;
}


uint64 FME(uint64 a, uint64 x, uint64 p)
{
    if (p <= 0) {
        cout << "incorrect p" << endl;
        return -1;
    }

    uint64 y;
    vector<uint64> bin;
    vector<uint64> num_decomposition;
    vector<uint64> mod_p;


    //Шаг 1. Разложим x на степени 2, записав его в двоичном виде
    uint64 last_bit;
    uint64 x_temp = x;

    while (x_temp != 0)
    {
        last_bit = x_temp & 1;
        bin.push_back(last_bit);
        x_temp = x_temp >> 1;
    }

    for (long unsigned int i = 0; i < bin.size(); i++) {
        if (bin[i] == 1) {
            num_decomposition.push_back(ipow(2, i));
        }
    }


    // Шаг 2. Вычисляем mod p степеней двойки ≤ x
    uint64 res;
    vector<uint64> multiplier;

    for (uint64 i = 0; i < bin.size(); i++)
    {
        if (i == 0) {
            res = a % p;
            mod_p.push_back(res);
            if (bin[i] == 1) multiplier.push_back(res);
            continue;
        }

        res = ((mod_p[i - 1] % p) * (mod_p[i - 1] % p)) % p;
        mod_p.push_back(res);
        if (bin[i] == 1) multiplier.push_back(res);
    }

    // Шаг 3. Используем свойства модульного умножения, чтобы свести воедино полученные значения mod p
    y = multiplier[0];
    for (long unsigned int i = 0; i < multiplier.size() - 1; i++) {
        y = (y * multiplier[i + 1]) % p;
    }
    y %= p;

    return y;
}


int64 GCD(int64 a, int64 b, int64 &x, int64 &y)
{
    if (a < b) {
        int64 a_temp = a;
        a = b;
        b = a_temp;
    }

    int64 u1 = a; int64 u2 = 1; int64 u3 = 0;
    int64 v1 = b; int64 v2 = 0; int64 v3 = 1;
    int64 t1; int64 t2; int64 t3;
    int64 q;
    int64 gcd;

    while ((u1 && v1) != 0)
    {
        q = u1 / v1;

        t1 = u1 % v1;
        t2 = u2 - q * v2;
        t3 = u3 - q * v3;

        u1 = v1; u2 = v2; u3 = v3;
        v1 = t1; v2 = t2; v3 = t3;

        x = u2; y = u3;
    }

    gcd = a * x + b * y;

    return gcd;
}


uint64 DH(uint64 q, uint64 p,
    uint64 g, uint64 Xa,
    uint64 Xb, uint64 Xc, Clients pair)
{
    uint64 Ya = FME(g, Xa, p);
    uint64 Yb = FME(g, Xb, p);
    uint64 Yc = FME(g, Xc, p);

    // Формируем общий секретный ключ
    switch (pair)
    {
        case A_B: {
            uint64 Zab = FME(Yb, Xa, p);
            uint64 Zba = FME(Ya, Xb, p);
            return Zab;
            break;
        }

        case A_C: {
            uint64 Zac = FME(Yc, Xa, p);
            uint64 Zca = FME(Ya, Xc, p);
            return Zac;
            break;
        }

        case B_C: {
            uint64 Zbc = FME(Yc, Xb, p);
            uint64 Zcb = FME(Yb, Xc, p);
            return Zbc;
            break;
        }

        default:
            cout << "Unknown pair" << endl;
            return -1;
            break;
    }
}


uint64 BSGS(uint64 a, uint64 p, uint64 y)
{
    uint64 n = (uint64) sqrt(p + .0) + 1;
    map<uint64, uint64> vals;
    for (int i = n; i >= 1; --i) {
        vals[FME(a, i * n, p)] = i;
    }
    for (int i = 0; i <= n; ++i) {
        int cur;
        if (i == 0) cur = y % p;
        else cur = (FME(a, i, p) * y) % p;

        if (vals.count(cur)) {
            uint64 res = vals[cur] * n - i;
            if (res < p) return res;
        }
    }
    return 0;
}


bool miller_rabin_test(unsigned long long int n, int r)
{
    if (n == 2 || n == 3) return true;
    if (n < 2 || n % 2 == 0) return false;

    unsigned long long int t = n - 1;

    int s = 0;

    while (t % 2 == 0)
    {
        t /= 2;
        s++;
    }

    for (int i = 0; i < r; i++)
    {
        unsigned long long int a = rand() % (n - 2) + 2;

        unsigned long long int x = FME(a, t, n);

        if(x == 1 || x == n - 1) continue;

        for (int j = 1; j < s; j++)
        {
            x = FME(x, 2, n);

            if (x == 1) return false;
            if (x == n - 1) break;
        }

        if (x != n - 1) return false;
    }

    return true;
}


unsigned long long int rand_prime()
{
    unsigned long long int t;
    do
    {
        t = rand();
    } while (!(miller_rabin_test(t, 10)));

    return t;
}
