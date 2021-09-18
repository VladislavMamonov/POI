#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

typedef unsigned long long int uint64;

enum Clients
{
    A_B,
    A_C,
    B_C,
};

uint64 ipow(uint64 a, uint64 n);

bool isPrime(uint64 p);

uint64 FME(uint64 a, uint64 x, uint64 p);

int GCD(int a, int b, int &x, int &y);

uint64 DH(uint64 q, uint64 p, uint64 g, uint64 Xa,
    uint64 Xb, uint64 Xc, Clients pair);

uint64 BSGS(uint64 a, uint64 p, uint64 y);
