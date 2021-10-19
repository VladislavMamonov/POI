#include "../lab1/CryptoLib.hpp"


void PG_generation(int64 *p, int64 *g)
{
    int64 q;

    do {
        q = rand();
        *p = 2 * q + 1;
    } while (isPrime(q) != true || (isPrime(*p) != true));

    *g = rand();

    while (true) {
        if (FME(*g, q, *p) != 1) break;
        *g = rand();
    }
}


int main()
{
    // Шамир
    srand(time(NULL));
    int64 m = 8232421412412494;
    int64 m2;

    cout << "source message: " << m << endl;

    for (int i = 0; i < 100; i++) {
        m2 = Shamir(m);
        if (m2 != m) {
            cout << "i = " << i << "*" << endl;
        }
    }

    // Эль Гамаль
    int64 p;
    int64 g;

    PG_generation(&p, &g);
    cout << "El Gamal decrypted: " << ElGamal(m, p, g) << endl;

    // Вернам
    vector<int64> m_decrypted;
    Vernam(m, m_decrypted);

    cout << "Vernam decrypted: ";

    for (int i = 0; i < m_decrypted.size(); i++)
        cout << m_decrypted[i];
    cout << endl;


    // RSA
    int64 q;
    do {
        do {
            p = rand() % 10000;
        } while (isPrime(p) != true);

        do {
            q = rand() % 10000;
        } while (isPrime(q) != true);
    } while (p == q);

    cout << "RSA decrypted: " << RSA(m, p, q) << endl;

    return 0;
}
