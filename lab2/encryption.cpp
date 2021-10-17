#include "../lab1/CryptoLib.hpp"


void DataSplit(int64 m, vector<int64> &m_parts)
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
    } while ((isPrime(p) != true) || (p <= 10));

    if (m >= p) DataSplit(m, m_parts);

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


int64 ElGamal(int64 m, int64 p, int64 g)
{
    int64 d;
    int64 c;
    int64 m_res;
    vector<int64> m_parts;

    do {
        p = rand();
    } while ((isPrime(p) != true) || (p <= 10));

    if (m >= p) DataSplit(m, m_parts);

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
    if (m < p) {
        e = (FME(m, 1, p) * FME(d, k, p)) % p;
        m_res = e * FME(r, p - 1 - c, p) % p;
    } else if (m >= p) {
        stringstream m_res_str;
        for (int i = m_parts.size() - 1; i >= 0; i--) {
            e = (FME(m_parts[i], 1, p) * FME(d, k, p)) % p;
            m_res = e * FME(r, p - 1 - c, p) % p;
            m_res_str << m_res;
        }
        m_res_str >> m_res;
    }

    return m_res;
}


void Vernam(int64 m, vector<int64> &m_decrypted)
{
    vector<int64> m_parts;
    vector<int64> k;
    vector<int64> e;

    DataSplit(m, m_parts);

    for (int i = 0; i < m_parts.size(); i++) {
        k.push_back(rand());
        e.push_back(m_parts[m_parts.size() - 1 - i] ^ k[i]);
    }

    for (int i = 0; i < e.size(); i++) {
        m_decrypted.push_back(e[i] ^ k[i]);
    }
}


int64 RSA(int64 m, int64 p, int64 q)
{
    int64 n = p * q;
    int64 fi = (p - 1) * (q - 1);
    int64 d, c;
    int64 x, y;
    int64 m_res;
    vector<int64> m_parts;

    do {
        d = rand() % fi;
    } while (GCD(fi, d, x, y) != 1);

    y > 0 ? c = y : c = (y + fi);

    if (m >= n) DataSplit(m, m_parts);

    int64 e;

    if (m < n) {
        e = FME(m, d, n);
        m_res = FME(e, c, n);
    } else if (m >= n) {
        stringstream m_res_str;
        for (int i = m_parts.size() - 1; i >= 0; i--) {
            e = FME(m_parts[i], d, n);
            m_res = FME(e, c, n);
            m_res_str << m_res;
        }
        m_res_str >> m_res;
    }
    return m_res;
}
