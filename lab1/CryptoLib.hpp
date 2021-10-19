#pragma once

#include <algorithm>
#include <fstream>
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

bool isPrime(int64 p);

int64 FME(int64 a, int64 x, int64 p);

int64 GCD(int64 a, int64 b, int64 &x, int64 &y);

int64 DH(int64 q, int64 p, int64 g, int64 Xa,
    int64 Xb, int64 Xc, Clients pair);

int64 BSGS(int64 a, int64 p, int64 y);

void DataSplit(int64 m, vector<int64> &m_parts);

vector<int64> Shamir(vector<int64> m);

vector<int64> ElGamal(vector<int64> m, int64 p, int64 g);

vector<int64> Vernam(vector<int64> m);

vector<int64> RSA(vector<int64> m, int64 p, int64 q);
