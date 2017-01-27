

/*----------------------------Find Prime upto 1000 using seive function---------------------------*/

/*----------------------------This code find the divisors of a number-----------------------*/

#include <bits/stdc++.h>
using namespace std;

#define SIZE_N 100000
#define SIZE_P 400000

bool status[SIZE_N/2+5]; // used to check a number is prime or not
int prime[SIZE_P]; // used to store all prime upto SIZE_N
int store_primes[SIZE_P]; // used to store the prime that divide the number
int freq_primes[SIZE_P]; // used to store the frequency of prime that divide the number
int store_divisors[SIZE_P]; // used to store all divisors

int indx, total_prime, ans;

void seive()
{
    for(int i = 2; i <= SIZE_N >> 1; i++) {
        status[i] = 0;
    }
    int rt = int( sqrt((double)SIZE_N)) + 1;
    for(int i = 3; i <= rt; i += 2) {
        if(status[i>>1] == 0) {
            for(int j = i*i; j <= SIZE_N; j += i+i) {
                status[j>>1] = 1;
            }
        }
    }
    indx = 0;
    for(int i = 2; i <= SIZE_N; i++) {
        if(status[i>>1] == 0) {
            prime[indx++] = i;
        }
    }
}

int divisor(int n)
{
    int rt = int( sqrt((double) n)) + 1;
    int total = 1; // it holds the total number of divisors
    total_prime = 0;
    for(int i = 0; prime[i] < rt; i++) {
        if(n % prime[i] == 0) {
            int cnt = 0;
            while(n % prime[i] == 0) {
                n /= prime[i];
                cnt++;
            }
            total *= (cnt+1);
            store_primes[total_prime] = prime[i];
            freq_primes[total_prime] = cnt;
            total_prime++;
            rt = sqrt((double)n)+1;
        }
    }
    if(n > 1) {
        total *= 2;
        store_primes[total_prime] = n;
        freq_primes[total_prime] = 1;
        total_prime++;
    }
    return total;
}

void Generate(int cur, int num)
{
    int i, val;
    if(cur == total_prime)
        store_divisors[ans++] = num;
    else {
        val = 1;
        for(i = 0; i <= freq_primes[cur]; i++) {
            Generate(cur+1, num*val);
            val = val*store_primes[cur];
        }
    }
}
int main()
{
    seive();
    int n;

    while(scanf("%d", &n) == 1) {
        ans = 0; // it store the number of divisors of n
        int res = divisor(n); // it also return the number of divisors of n
        printf("%d No of divisor: %d\n", n, res);
        Generate(0, 1);
        sort(&store_divisors[0], &store_divisors[ans]);
        //cout << ans << endl;
        for(int i = 0; i < ans; i++)
            printf("%d ", store_divisors[i]);
        printf("\n");
    }
    return 0;
}
