#include "../lab1/CryptoLib.hpp"


void DataSplit(int64 m, int64 p, vector<int64> &m_parts)
{
    for (int i = 0; m > 0; i++) {
        m_parts.push_back(m % 10);
        m /= 10;
    }
}


int64 Shamir(int64 m)
{
    int64 p;
    int64 cA, dA, cB, dB;
    vector<int64> m_parts;

    do {
        p = rand();
    } while (isPrime(p) != true);

    if (m >= p) DataSplit(m, p, m_parts);

    int64 x, y;
    do {
        cA = rand() % (p - 1);
    } while ((GCD(cA, p - 1, x, y) != 1));

    if (y < 0) y += p - 1;
    dA = y + (p - 1);

    do {
        cB = rand() % (p - 1);
    } while ((GCD(cB, p - 1, x, y) != 1));

    if (y < 0) y += p - 1;
    dB = y + (p - 1);

    int64 x1, x2, x3, x4;
    vector<int64> x4_parts;

    if (m < p) {
        x1 = FME(m, cA, p);
        x2 = FME(x1, cB, p);
        x3 = FME(x2, dA, p);
        x4 = FME(x3, dB, p);
    } else if (m >= p) {
        stringstream x4_res;
        for (int i = m_parts.size() - 1; i >= 0; i--) {
            x1 = FME(m_parts[i], cA, p);
            x2 = FME(x1, cB, p);
            x3 = FME(x2, dA, p);
            x4 = FME(x3, dB, p);
            x4_res << x4;
        }
        x4_res >> x4;
    }

    return x4;
}


int64 ElGamal(int64 m)
{
    int64 p;

    do {
        p = rand();
    } while (isPrime(p) != true);

    do
    {
        c = rand() % (p - 1);
    } while (c <= 1);
}
