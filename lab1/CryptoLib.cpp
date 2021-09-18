#include "CryptoLib.hpp"


uint64 ipow(uint64 a, uint64 n)
{
    uint64 r = 1;

    for (uint64 i = 0; i < n; i++) r *= a;

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


int GCD(int a, int b, int &x, int &y)
{
    if (a < b) {
        int a_temp = a;
        a = b;
        b = a_temp;
    }

    int u1 = a; int u2 = 1; int u3 = 0;
    int v1 = b; int v2 = 0; int v3 = 1;
    int t1; int t2; int t3;
    int q;
    int gcd;

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
    uint64 x;
    uint64 m;
    uint64 k;
    vector<uint64> b;
    vector<uint64> g;
    uint64 i;
    uint64 j;

    m = sqrtl(p) + 1;
    k = sqrtl(p) + 1;

    for (uint64 i = 0; i <= (m - 1); i++) {
        b.push_back((ipow(a, i) * y) % p);
    }

    for (uint64 j = 1; j <= k; j++) {
        g.push_back(ipow(a, (j * m)) % p);
    }

    bool break_flag = false;

    for (i = 0; i < b.size(); i++) {
        if (break_flag == true) { i -= 1; break; }
        for (j = 0; j < g.size(); j++) {
            if (b[i] == g[j]) {
                j += 1;
                break_flag = true;
                break;
            }
        }
    }

    x = j * m - i;

    return x;
}
