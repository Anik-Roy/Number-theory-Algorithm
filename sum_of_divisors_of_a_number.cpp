
/*---------------------------This code find the sum of divisors of a number-----------------------------------*/

#include <bits/stdc++.h>
using namespace std;

#define SIZE_N 5000
#define SIZE_P 2500

bool status[2500+5]; // used to check a number is prime or not
int prime[SIZE_P]; // used to store all prime number upto SIZE_N

void sieve()
{
    for(int i = 2; i <= SIZE_N >> 1 + 1; i++) status[i] = 0;
    int rt = int( sqrt((double)SIZE_N) ) + 1;

    for(int i = 3; i <= rt; i += 2) {
        if(status[i>>1] == 0) {
            for(int j = i*i; j <= SIZE_N; j += i+i) {
                status[j>>1] = 1;
            }
        }
    }

    int indx = 0;

    for(int i = 2; i <= SIZE_N; i++) {
        if(status[i>>1] == 0)
            prime[indx++] = i;
    }
}

int sum_of_divisor(int n) // this algorithm is used to find sum of divisors of n
{
    int rt = int( sqrt((double)n) ) + 1; // Page: 56, algorithm book
    int sum = 1;
    for(int i = 0; prime[i] < rt; i++) {
        if(n % prime[i] == 0) {
            int p = 1;
            while(n % prime[i] == 0) {
                n /= prime[i];
                p *= prime[i];
            }

            p *= prime[i];
            int s = (p-1)/(prime[i]-1);
            sum *= s;
        }
    }
    if(n > 1) {
        int p = n*n;
        int s = (p-1)/(n-1);
        sum *= s;
    }
    return sum;
}
int main()
{
    sieve();
    int n;
    while(scanf("%d", &n) == 1) {
        printf("%d Sum of divisor: %d\n", n, sum_of_divisor(n));
    }
    return 0;
}
