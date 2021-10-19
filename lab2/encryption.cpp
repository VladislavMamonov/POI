#include "../lab1/CryptoLib.hpp"


void DataSplit(int64 m, vector<int64> &m_parts)
{
    int i;
    for (i = 0; m > 0; i++) {
        m_parts.push_back(m % 10);
        m /= 10;
    }
    reverse(m_parts.end() - i, m_parts.end());
}


void DataJoin(vector<int64> &m, vector<int64> m_parts)
{
    stringstream stream;
    int j = 0;

    for (int i = 0; i < m.size(); i++) {
        stream.clear();

        stream << m_parts[i + j];
        stream << m_parts[i + j + 1];
        stream << m_parts[i + j + 2];
        j += 2;

        stream >> m[i];
    }
}


vector<int64> Shamir(vector<int64> m)
{
    int64 p;
    int64 cA, dA, cB, dB;
    vector<int64> m_parts;

    do {
        p = rand();
    } while ((isPrime(p) != true) || (p <= 10));

    for (int i = 0; i < m.size(); i++) DataSplit(m[i], m_parts);

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

    for (int i = 0; i < m_parts.size(); i++) {
        x1 = FME(m_parts[i], cA, p);
        x2 = FME(x1, cB, p);
        x3 = FME(x2, dA, p);
        x4 = FME(x3, dB, p);
        x4_parts.push_back(x4);
    }

    DataJoin(m, x4_parts);
    return m;
}


vector<int64> ElGamal(vector<int64> m, int64 p, int64 g)
{
    int64 d;
    int64 c;
    vector<int64> m_res;
    vector<int64> m_parts;

    do {
        p = rand();
    } while ((isPrime(p) != true) || (p <= 10));

    for (int i = 0; i < m.size(); i++) DataSplit(m[i], m_parts);

    do
    {
        c = rand() % (p - 1);
    } while (c <= 1);

    d = FME(g, c, p);

    int64 r, e, k;

    do
    {
        k = rand() % (p - 2);
    } while (k < 1);

    r = FME(g, k, p);

    for (int i = 0; i < m_parts.size(); i++) {
        e = (FME(m_parts[i], 1, p) * FME(d, k, p)) % p;
        m_res.push_back(e * FME(r, p - 1 - c, p) % p);
    }

    DataJoin(m, m_res);
    return m;
}


vector<int64> Vernam(vector<int64> m)
{
    vector<int64> m_parts;
    vector<int64> m_res;
    vector<int64> k;
    vector<int64> e;

    for (int i = 0; i < m.size(); i++) DataSplit(m[i], m_parts);

    for (int i = 0; i < m_parts.size(); i++) {
        k.push_back(rand());
        e.push_back(m_parts[m_parts.size() - 1 - i] ^ k[i]);
    }

    for (int i = e.size() - 1; i >= 0; i--) {
        m_res.push_back(e[i] ^ k[i]);
    }

    DataJoin(m, m_res);
    return m;
}


vector<int64> RSA(vector<int64> m, int64 p, int64 q)
{
    int64 n = p * q;
    int64 fi = (p - 1) * (q - 1);
    int64 d, c;
    int64 x, y;
    vector<int64> m_res;
    vector<int64> m_parts;

    do {
        d = rand() % fi;
    } while (GCD(fi, d, x, y) != 1);

    y > 0 ? c = y : c = (y + fi);

    for (int i = 0; i < m.size(); i++) DataSplit(m[i], m_parts);

    int64 e;

    for (int i = 0; i < m_parts.size(); i++) {
        e = FME(m_parts[i], d, n);
        m_res.push_back(FME(e, c, n));
    }

    DataJoin(m, m_res);
    return m;
}
