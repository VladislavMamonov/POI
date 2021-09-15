#include "CryptoLib.hpp"


int main()
{
    unsigned long long int FME_res;
    FME_res = FME(999999998, 999999999, 999999999);
    cout << "FME: " << FME_res << endl;

    int GCD_a = 15; int GCD_b = 4; int GCD_x; int GCD_y;
    int gcd;
    gcd = GCD(GCD_a, GCD_b, GCD_x, GCD_y);
    cout << "GCD: x = " << GCD_x << ", y = " << GCD_y << ", gcd = " << gcd << endl;

    cout << "DH A_B = " << DH(A_B) << endl;
    cout << "DH_A_C = " << DH(A_C) << endl;
    cout << "DH_B_C = " << DH(B_C) << endl;
    return 0;
}
