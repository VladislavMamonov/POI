#include "../lab1/CryptoLib.hpp"


int main()
{
    srand(time(NULL));
    int64 m = 823945434535435322;
    int64 m2;
    for (int i = 0; i < 100000; i++) {
        m2 = Shamir(m);
        if (m2 != m) {
            cout << "i = " << i << "*" << endl;
        }
    }

    return 0;
}
