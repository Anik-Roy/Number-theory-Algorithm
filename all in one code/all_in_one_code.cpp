/*
    Author: Anik Roy Gourab
    University: Leading University, Sylhet.
    Department: Computer Science and Engineering
*/


/*--------------------------------All number theory algorithm is in here--------------------------*/


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


int gcd(int a, int b) // used to find gcd of two numbers
{
    if(a == 0)
        return b;
    return gcd(b%a, a);
}

int lcm(int a, int b) // used to find lcm of two numbers
{
    return (a*b)/gcd(a, b);
}

void seive()  // by this algorithm, we can find prime upto SIZE_N
{
    for(int i = 2; i <= SIZE_N >> 1; i++) {
        status[i] = 0; // status array used to check a number is prime or not
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
    prime[indx++] = 2;
    for(int i = 3; i <= SIZE_N; i+=2) {
        if(status[i>>1] == 0) {
            prime[indx++] = i; // prime array is used to store all prime number upto SIZE_N
        }
    }
}

int divisors_count(int n) // this algorithm is used to find number of divisors of n
{
    int rt = int( sqrt((double) n)) + 1; // we need to traverse upto square root of n to find its divisors
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

void Generate(int cur, int num) // generates all the divisors of n
{
    int i, val;
    if(cur == total_prime)
        store_divisors[ans++] = num; // hold all divisors of n
    else {
        val = 1;
        for(i = 0; i <= freq_primes[cur]; i++) {
            Generate(cur+1, num*val);
            val = val*store_primes[cur];
        }
    }
}
int sum_of_divisor(int n)
{
    int rt = sqrt((double)n)+1;
    int sum = 1;

    for(int i = 0; prime[i] < rt; i++) {
        if(n % prime[i] == 0) {
            int p = 1;
            while(n % prime[i] == 0) {
                n /= prime[i];
                p *= prime[i];
            }
            p *= prime[i];
            sum *= ((p-1)/(prime[i]-1));
        }
    }
    if(n > 1) {
        int p = n*n;
        int s = (p-1)/(n-1);
        sum *= s;
    }
}

int Goldbach_conjecture(int n) // this algorithm is used to find such prime pair p1 and p2 so that p1+p2 = n
{
    int res = 0;
    for(int i = 2; i <= n/2; i++) {
        int d = n-i;
        if(i == 2) {
            if((n-i)%2 != 0 && status[d>>1] == 0) {
                res++;
                cout << i << " " << n-i << endl;
            }
        }
        else if(i%2 != 0 && (n-i)!= 0 && status[i>>1] == 0 && status[(n-i)>>1] == 0) {
            res++;
            cout << i << " " << n-i << endl;
        }
    }
    return res;
}

int main()
{
    seive();

    int a, b;
    cin >> a >> b;
    int g = gcd(a, b);
    int l = lcm(a, b);
    cout << "GCD: " << g << endl;
    cout << "LCD: " << l << endl;
    int n;
    cin >> n;

    int total_divisors = divisors_count(n); // return the number of divisors of n
    cout << "Number of divisors of " << n << ": " << total_divisors << endl;
    ans = 0; // it also holds the number of divisors of n
    Generate(0, 1); // generates all the divisors of n
    sort(&store_divisors[0], &store_divisors[ans]);

    for(int i = 0; i < ans; i++)
        cout << store_divisors[i] << " ";
    cout << endl;

    int sum = sum_of_divisor(n);
    cout << "Sum of divisors of " << n << ": " << sum << endl;

    cout << "Enter any number >=4: ";
    cin >> n;
    int res = Goldbach_conjecture(n);
    cout << "The Goldbach's conjecture is: " << res << endl;
    return 0;
}
