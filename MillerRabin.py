from fractions import gcd
from random import randrange

#function to repeatedly factor 2 from n-1 and obtain the proper exponent for the equation 2^r * d
def exponent(n):
    k = n-1
    r = 0
    while k%2 == 0:
        k = int(k/2)
        r+=1
    return r


#function to conduct Miller Rabin primality test
def miller(n):
    #obtain r from exponent function, and d by dividing n-1 by 2 to the obtained r
    r = exponent(n)
    d = int(n-1 / 2**r)

    #for loop to randomly select a number 2 < a < n-1 in order to test the contrapositive of fermat's little theorem
    #loop runs 100 times to give us as probabilistically true answer as possible 
    for i in range (1, 100):

        #assign a to random number in range
        a = randrange(2, n-2)

        #set x to a raised to d, mod by n
        x = pow(a, d, n)

        #if x is equal to 1 or n-1 we can continue through the end of the loop and return true
        if x == 1 or x == n-1:
         continue
        
        #for loop to test powers of x all the way up to r-1
        #if n is prime, x rasied to the power of r-1 should be congruent to +/- 1 mod n
        #and therefore n is prime. If any other power of x is congruent to 1 mod n,
        #n must be composite
        for i in range (r-1):
            x = pow(x, 2, n)
            if x == 1:
                return False
            if x == n-1:
                continue
        return False
    return True


n = pow(2, 521) - 1


if miller(n) == True:
    print( n, "is probably prime" )
else:
    print (n, "is composite")


