#include "../lab1/CryptoLib.hpp"


int64 Shamir(int64 m)
{
    int64 p;
    int64 cA, dA, cB, dB;

    do {
        p = rand();
    } while (isPrime(p) != true);

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

    x1 = FME(m, cA, p);
    x2 = FME(x1, cB, p);
    x3 = FME(x2, dA, p);
    x4 = FME(x3, dB, p);

    return x4;
}
