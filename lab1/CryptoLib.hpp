#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <sstream>
#include <map>

using namespace std;

typedef unsigned long long int uint64;
typedef long long int int64;

enum Clients
{
    A_B,
    A_C,
    B_C,
};

int64 ipow(int64 a, int64 n);

bool isPrime(uint64 p);

uint64 FME(uint64 a, uint64 x, uint64 p);

int64 GCD(int64 a, int64 b, int64 &x, int64 &y);

uint64 DH(uint64 q, uint64 p, uint64 g, uint64 Xa,
    uint64 Xb, uint64 Xc, Clients pair);

uint64 BSGS(uint64 a, uint64 p, uint64 y);

void DataSplit(int64 m, vector<int64> &m_parts);

int64 Shamir(int64 m);

int64 ElGamal(int64 m, int64 p, int64 g);

void Vernam(int64 m, vector<int64> &m_decrypted);

int64 RSA(int64 m, int64 p, int64 q);
