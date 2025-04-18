# Primelist
creates a list of primes in a text file

compile with gcc
reccomended to use -std=c99 -m64 -O3

should work up to 2^64 =~ 1.84 x 10^19

requires a 64 bit system


# Functions

mpow(base, exponeent, modulus): returns base ^ exponent % modulus

trialDivision(n): returns true if n is not divisable by primes up to 100 prime factors up to 100

fermat(n): tests n with fermat bases 2 and 3. Returns true if still probably prime

millerRabin(n): runs a miller-rabin primality test on n, with set bases that are deterministic up to 2^64. Takes longer than all the other tests, but it is deterministic in this implementation.
