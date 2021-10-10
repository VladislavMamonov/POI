#include "CryptoLib.hpp"


int main()
{
    srand(time(NULL));
    uint64 FME_res;
    FME_res = FME(999999998, 999999999, 999999999);
    cout << "FME: " << FME_res << endl;

    int64 GCD_a = rand(); int64 GCD_b = rand(); int64 GCD_x; int64 GCD_y;
    int64 gcd;
    gcd = GCD(GCD_a, GCD_b, GCD_x, GCD_y);
    cout << "GCD: x = " << GCD_x << ", y = " << GCD_y << ", gcd = " << gcd << endl;


    // DH
    uint64 q;
    uint64 p;

    uint64 range = ipow(10, 9);
    do {
        q = rand() % range;
        p = 2 * q + 1;
    } while (isPrime(q) == false || (isPrime(p) == false));

    int g = rand();

    while (true) {
        if (FME(g, q, p) != 1) break;
        g = rand();
    }

    uint64 Xa = rand();
    uint64 Xb = rand();
    uint64 Xc = rand();

    cout << "DH A_B = " << DH(q, p, g, Xa, Xb, Xc, A_B) << endl;
    cout << "DH_A_C = " << DH(q, p, g, Xa, Xb, Xc, A_C) << endl;
    cout << "DH_B_C = " << DH(q, p, g, Xa, Xb, Xc, B_C) << endl;


    // -------
    cout << "BSGS = " << BSGS(rand(), rand(), rand()) << endl;

    return 0;
}
