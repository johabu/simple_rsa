#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

unsigned long get_rand(unsigned long RANDMAX, unsigned long RANDMIN) {
        unsigned long r;
        r = (rand() % (RANDMAX - RANDMIN + 1)) + RANDMIN;
        return r;
}

unsigned long get_prime(unsigned long MAX, unsigned long MIN) {
	unsigned long rand_num;
	unsigned int i;
        unsigned short prime = 1;
	while (prime != 0) {
		prime = 0;
		rand_num = get_rand(MAX, MIN);
		//printf("\nRandom number between %ld and %ld:\t%ld\nTesting if prime...", MIN, MAX,rand_num);
		for(i = 2; i < rand_num / 2 && !prime; i++) {
			if(rand_num % i == 0)	{
				//printf("No.\n");
				prime = 1;
			}
		}
		//if (!prime) printf("Yes.\n");
	}
	return rand_num;
}

unsigned long gcd(unsigned long a, unsigned long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

long modular_inverse(unsigned long a, unsigned long b) {
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

int main(void) {
	printf("\nStarting RSA key generation...\n");
	srand(time(NULL));
	unsigned long p, q, n, phi_n, e;
	long d;
	//generating two prime numbers
	p = get_prime(100000, 10000);
	q = get_prime(100000, 10000);
	n = p * q;
	phi_n = (p - 1) * (q - 1);
	unsigned long coprime = 0;
	while (coprime != 1) {
		e = get_rand(200,100);
		coprime = gcd(phi_n,e);
	}
	d = modular_inverse(e, phi_n);
	printf("p: %ld\nq: %ld\nn: %ld\ne: %ld\n",p,q,n,e);
	printf("d: %ld\n",d);
	return EXIT_SUCCESS;
}
