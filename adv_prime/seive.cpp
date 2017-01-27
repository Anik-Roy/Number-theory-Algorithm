#include <bits/stdc++.h>
using namespace std;

int prime[1000], n_prime = 1;
bool mark[100002];

void sieve(int n)
{
    int i, j, limit = sqrt(n)+2;

    // 1 is not prime. you can also mark 1
    mark[1] = 0;
    // almost allthe evens are not prime
    for(i = 4; i <= n; i += 2)  mark[i] = 0;

    // 2 is prime
    prime[n_prime++] = 2;
    for(int i = 3; i <= n; i += 2) {
        // if not prime, no need to do "multiple cutting"
        if(!mark[i]) {
            // i is prime
            prime[n_prime++] = i;

            // if we don't do it, following
            // i*i may overflow
            if(i <= limit) {
                // loop through all odd multiples of i
                // greater than i*i
                for(j = i*i; j <= n; j += i*2) {
                    // mark j not prime
                    mark[j] = 0;
                }
            }
        }
    }
}
int main()
{
    int n;
    printf("Enter a prime number: ");
    scanf("%d", &n);

    sieve(n);

    for(int i = 1; i < n_prime; i++)
        cout << prime[i] << endl;
    return 0;
}
