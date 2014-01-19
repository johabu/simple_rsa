/*
====================================================================================================
simple_rsa is a very simple implementation of the basic RSA encryption algorithm

===== IMPORTANT NOTE =====
This program does NOT fulfil any safety standards! It should NOT be used for real
encryption, because it does not provide any safety! This program is only written 
for teaching purposes.

simple_rsa is distributed without any warranty!

======== LICENSE ========
simple_rsa is free software; you can modify it or redistribute it
under the terms of the GNU General Public License as published by
the Free Software Foundation <http://www.fsf.org>, either version 3,
or (at your option) any later version.
See <http://www.gnu.org/licenses> for the license, if you
haven't received a copy of it (GNU_GPL.txt).

====================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>

//generaing a random number between RANDMIN and RANDMAX
unsigned long get_rand(unsigned long RANDMAX, unsigned long RANDMIN) {
        unsigned long r;
        r = (rand() % (RANDMAX - RANDMIN + 1)) + RANDMIN;
        return r;
}

//get a random prime between MIN and MAX
unsigned long get_prime(unsigned long MAX, unsigned long MIN) {
	unsigned long rand_num;
	unsigned int i;
        unsigned short prime = 1;
	while (prime != 0) {
		prime = 0;
		rand_num = get_rand(MAX, MIN);
		for(i = 2; i < rand_num / 2 && !prime; i++) {
			if(rand_num % i == 0)	{
				prime = 1;
			}
		}
	}
	return rand_num;
}

//get grearesult common divisor of numbers a and b using Euclidean algorithm
unsigned long gcd(unsigned long a, unsigned long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

//get modular inverse of numbers a  b
double modular_inverse(unsigned long a, unsigned long b) {
	long b0 = b, t, q;
	long x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
long n;
unsigned long e;
long d;

//function for generating key pair
void generate_keys(unsigned long PRIMEMIN, unsigned long PRIMEMAX, unsigned long EMIN, unsigned long EMAX) {
	printf("\nStarting RSA key generation...\n");
        unsigned long p, q, phi_n;
        //generating two random prime numbers
        p = get_prime(PRIMEMAX, PRIMEMIN);
        q = get_prime(PRIMEMAX, PRIMEMIN);
        n = p * q;
        phi_n = (p - 1) * (q - 1);
        unsigned long coprime = 0;
        while (coprime != 1) {
                e = get_rand(EMAX, EMIN);
                coprime = gcd(phi_n,e);
        }
        d = modular_inverse(e, phi_n);
        printf("p: %ld\nq: %ld\nn: %ld\ne: %ld\n",p,q,n,e);
        printf("d: %ld\n====================================================\n",d);
}

unsigned long modular_power(unsigned long num, unsigned long pow, unsigned long mod)
{
	//using modular exponentation is faster; this algorithm can deal with much greater numbers than just using remainder()
	unsigned long long result;
	unsigned long long n = num;
	for(result = 1; pow; pow >>= 1) {
		if (pow & 1)
			result = ((result % mod) * (n % mod)) % mod;
		n = ((n % mod) * (n % mod)) % mod;
	}
	return result;
}

//main function
int main(void) {
	unsigned long PRIMEMIN = 10000;
	unsigned long PRIMEMAX = 100000;
	unsigned long EMIN = 2000;
	unsigned long EMAX = 5000;
	unsigned long message = 123;
	unsigned long long encrypted, decrypted;
	unsigned int correct = 0;
	system("clear");
	srand(time(NULL));
	while (correct != 1) {
		system("clear");
		generate_keys(PRIMEMIN, PRIMEMAX, EMIN, EMAX);
		encrypted = modular_power(123, e, n);
		decrypted = modular_power(encrypted, d, n);
		if (decrypted == 123)
			correct = 1;
	}
	printf("=> Public key:  (%ld , %ld)\n=> Private key: (%ld , %ld)\n", n, e, n, d);
	printf("====================================================\nClear text message: %ld\n", message);
	printf("Encrypting...\n");
	encrypted = modular_power(message, e, n);
	printf("Encrypted message: %lld\nDecrypting...\n", encrypted);
	decrypted = modular_power(encrypted, d, n);
	printf("Decrypted message: %lld\n",decrypted);
	if (message == decrypted)
		printf("Decrypted message same as original message!\n");
	printf("====================================================\n");
	return EXIT_SUCCESS;
}
