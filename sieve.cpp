#include <bits/stdc++.h>
using namespace std;

#define SIZE 1000001
typedef long long ll;

int ara[SIZE];

void sieve()
{
    ara[0] = ara[1] = 0;
    for(int i = 2; i <= SIZE; i++)
        ara[i] = 1;
    int root = int( sqrt( (double) SIZE));
    for(int i = 2; i <= root; i++) {
        if(ara[i]) {
            for(int j = 2; i*j <= SIZE; j++) {
                ara[i*j] = 0;
            }
        }
    }
}
int main()
{
    sieve();
    int n;
    cout << "Please enter a number to check either it is prime or not: ";
    cin >> n;
    if(ara[n])
        cout << n << " is a prime number" << endl;
    else
        cout << n << " is not a prime number" << endl;
    return 0;
}
