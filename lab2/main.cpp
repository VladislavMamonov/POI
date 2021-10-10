#include "../lab1/CryptoLib.hpp"


int main()
{
    srand(time(NULL));
    int m = 11;
    int m2;
    for (int i = 0; i < 100000; i++) {
        m2 = Shamir(m);
        if (m2 != m) {
            cout << "i = " << i << "*" << endl;
        }
    }

    return 0;
}
