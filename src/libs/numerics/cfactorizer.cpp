// -- libs includes
#include "core/assert.h"
#include "numerics/cfactorizer.h"
#include "numerics/cprimecalculator.h"
#include "numerics/cmath.h"

// ------------------------------------------------------------------------------------------------
// Recursive function to collect all the combinations of factors
// ------------------------------------------------------------------------------------------------
void CFactorizer::CollectFactorCombinations(const CTable<nuint>& factors, nuint curr, nuint prod,
                                            CTable<nuint>& divisors) {
    nuint numfactors = factors.Count();
    nuint f = factors[curr];

    // -- look for the upper bound of the same factor
    nuint end = curr;
    while(end < numfactors && factors[end] == f)
        ++end;

    // -- figure out if we're the end of the line and so we should be adding into the table
    nflag record = end == numfactors;

    // -- loop over the number of times this factor is repeated and deal with all of them
    for(nuint i = curr; i <= end; ++i) {
        if(record)
            divisors.Grow(prod);
        else
            CollectFactorCombinations(factors, end, prod, divisors);

        prod *= f;
    }
}

// ================================================================================================
// Collect all the prime factors of a number
// ================================================================================================
void CFactorizer::CollectFactors(nuint num, CPrimeCalculator& primecalc, CTable<nuint>& factors) {
    // -- make sure the prime calculator has enough primes
    primecalc.FindPrimesUpTo(num >> 1);

    // -- clear the factors table in case it has anything left in it
    factors.Clear();

    // -- get the prime factorization of the number
    nuint leftover = num;
    nuint numprimes = primecalc.NumPrimes();
    for(nuint i = 0; i < numprimes && leftover > 1; ++i) {
        nuint currprime = primecalc.Prime(i);
        while((leftover % currprime) == 0) {
            leftover /= currprime;
            factors.Grow(currprime);
        }
    }
    
    // -- if there's anything left, this number is prime and is it's only factor
    if(leftover > 1) {
        Assert_(leftover == num, NUintFmt_ " should have been a prime number, "
                                 "so nothing should have been divided out yet (" NUintFmt_ ")",
                                 num, leftover);
        factors.Grow(num);
    }
}

// ================================================================================================
// Collect all divisors given the table of prime factors
// ================================================================================================
void CFactorizer::CollectDivisors(const CTable<nuint>& factors, CTable<nuint>& divisors) {
    // -- clear the divisors table in case it has anything left in it
    divisors.Clear();

    // -- iterate through all the possible unique combinations of factors and combine them
    // -- into the unique proper divisors and sum them all up
    CollectFactorCombinations(factors, 0, 1, divisors);
}

