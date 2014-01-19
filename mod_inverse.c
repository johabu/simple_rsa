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
#include <stdint.h>

	
int main(void) {
	unsigned long a;
	unsigned long b;
	printf("e = ");
	scanf("%ld", &a);
	printf("phi(n) = ");
	scanf("%ld", &b);
	long b0 = b, t, q;
        long x0 = 0, x1 = 1;
        if (b == 1) return 1;
        while (a > 1) {
                q = a / b;
                t = b, b = a % b, a = t;
                t = x0, x0 = x1 - q * x0, x1 = t;
        }
        if (x1 < 0) x1 += b0;
	printf("Modular Inverse d = %ld\n", x1);
        return EXIT_SUCCESS;
}
