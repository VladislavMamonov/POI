#include "../lab1/CryptoLib.hpp"
#include "myfstream.hpp"


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
    //int64 m = 423423453453453;
    vector<int64> m;
    m = make_m();
    vector<int64> vec_shamir;
    vector<int64> vec_ElGamal;
    vector<int64> vec_vernam;
    vector<int64> vec_RSA;

    // cout << "source message: " << m << endl;

    vec_shamir = Shamir(m);

    for (int i = 0; i < m.size(); i++)
        cout << m[i];
    cout << endl << endl << endl;

    for (int i = 0; i < vec_shamir.size(); i++)
        cout << vec_shamir[i];
    cout << endl << endl << endl;

    put_fileOut(vec_shamir, "res_shamir.txt");


    // Эль Гамаль
    int64 p;
    int64 g;

    PG_generation(&p, &g);
    vec_ElGamal = ElGamal(m, p, g);

    for (int i = 0; i < vec_ElGamal.size(); i++)
        cout << vec_ElGamal[i];
    cout << endl << endl << endl;

    put_fileOut(vec_ElGamal, "res_ElGamal.txt");


    // Вернам
    vec_vernam = Vernam(m);

    for (int i = 0; i < vec_vernam.size(); i++)
        cout << vec_vernam[i];
    cout << endl << endl << endl;

    put_fileOut(vec_vernam, "res_vernam.txt");


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

    vec_RSA = RSA(m, p, q);

    for (int i = 0; i < vec_RSA.size(); i++)
        cout << vec_RSA[i];

    put_fileOut(vec_RSA, "res_RSA.txt");

    return 0;
}
