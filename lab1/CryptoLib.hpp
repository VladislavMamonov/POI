#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
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

int64 Shamir(int64 m);

bool miller_rabin_test(unsigned long long int n, int r);

unsigned long long int rand_prime();
