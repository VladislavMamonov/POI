#include "CryptoLib.hpp"


unsigned long long int ipow(unsigned long long int a, unsigned long long int n)
{
    unsigned long long int r = 1;

    for (unsigned long long int i = 0; i < n; i++) r *= a;

    return r;
}


bool isPrime(unsigned long long int p)
{
   if (p <= 1) return false;

   unsigned long long int b = pow(p, 0.5);

   for (unsigned long long int i = 2; i <= b; ++i) {
      if ((p % i) == 0) return false;
   }

   return true;
}



unsigned long long int FME(unsigned long long int a, unsigned long long int x, unsigned long long int p)
{
    if (p <= 0) {
        cout << "incorrect p" << endl;
        return -1;
    }

    unsigned long long int y;
    vector<unsigned long long int> bin;
    vector<unsigned long long int> num_decomposition;
    vector<unsigned long long int> mod_p;


    //Шаг 1. Разложим x на степени 2, записав его в двоичном виде
    unsigned long long int last_bit;
    unsigned long long int x_temp = x;

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
    unsigned long long int res;
    vector<unsigned long long int> multiplier;

    for (unsigned long long int i = 0; i < bin.size(); i++)
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


unsigned long long int DH(Clients pair)
{
    unsigned long long int q;
    unsigned long long int p;
    srand(time(NULL));

    unsigned long long int range = ipow(10, 9);
    do {
        q = rand() % range;
        p = 2 * q + 1;
    } while (isPrime(q) == false || (isPrime(p) == false));

    int g = 2;

    while (true) {
        if (FME(g, q, p) != 1) break;
        g++;
    }

    unsigned long long int Xa = rand() % ULLONG_MAX;
    unsigned long long int Xb = rand() % ULLONG_MAX;
    unsigned long long int Xc = rand() % ULLONG_MAX;

    unsigned long long int Ya = FME(g, Xa, p);
    unsigned long long int Yb = FME(g, Xb, p);
    unsigned long long int Yc = FME(g, Xc, p);

    // Формируем общий секретный ключ A с B

    switch (pair)
    {
        case A_B: {
            unsigned long long int Zab = FME(Yb, Xa, p);
            unsigned long long int Zba = FME(Ya, Xb, p);
            return Zab;
            break;
        }

        case A_C: {
            unsigned long long int Zac = FME(Yc, Xa, p);
            unsigned long long int Zca = FME(Ya, Xc, p);
            return Zac;
            break;
        }

        case B_C: {
            unsigned long long int Zbc = FME(Yc, Xb, p);
            unsigned long long int Zcb = FME(Yb, Xc, p);
            return Zbc;
            break;
        }

        default:
            cout << "Unknown pair" << endl;
            return -1;
            break;
    }
}
