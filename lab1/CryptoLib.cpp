#include "CryptoLib.hpp"


int64_t ipow(int a, int n)
{
    int64_t r = 1;

    for (int i = 0; i < n; i++) r *= a;

    return r;
}


int FME(int a, int x, int p)
{
    if (p <= 0) {
        cout << "incorrect p" << endl;
        return -1;
    }

    int y;
    vector<int> bin;
    vector<int> num_decomposition;
    vector<int> mod_p;


    //Шаг 1. Разложим x на степени 2, записав его в двоичном виде
    int last_bit;
    int x_temp = x;

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
    int res;
    int degree_decomp;

    for (int i = 0; ipow(2, i) <= x; i++)
    {
        bool check_eq = false;
        for (long unsigned int j = 0; j < num_decomposition.size(); j++) {
            if (ipow(2, i) == num_decomposition[j]) check_eq = true;
        }

        if (check_eq == false) continue;

        if (i == 0) {
            res = ipow(a, ipow(2, i)) % p;
            mod_p.push_back(res);
            continue;
        }

        degree_decomp = ipow(2, i) / 2;
        res = (ipow(a, degree_decomp) % p * ipow(a, degree_decomp) % p) % p;
        mod_p.push_back(res);
    }

    // Шаг 3. Используем свойства модульного умножения, чтобы свести воедино полученные значения mod p
    int mod_p_mul = 1;
    for (long unsigned int i = 0; i < mod_p.size(); i++) {
        mod_p_mul *= mod_p[i];
    }

    y = mod_p_mul % p;

    return y;
}
