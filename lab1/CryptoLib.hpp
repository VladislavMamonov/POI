#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;


enum Clients
{
    A_B,
    A_C,
    B_C,
};

unsigned long long int FME(unsigned long long int a, unsigned long long int x, unsigned long long int p);
int GCD(int a, int b, int &x, int &y);
unsigned long long int DH(Clients pair);
