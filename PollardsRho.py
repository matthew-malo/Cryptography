#Pollard rho algorithm for factoring Fermat numbers
from fractions import gcd

"""I set x to 1 as the initial test value, placeholding variables t and holder to 1 and 0 respectively, 
and f as the fermat number to solve. I created an array to store the x values in for use in gcd checking
"""
x = 1
t = 1
f = 2**64 +1
holder = 0
variable = []
#intialized the array and filled it to avoid out of bounds errors
for i in range(3000):
    variable.append(0)

#for loop to generate iterates of x sub i and x sub 2i for gcd testing with the fermat number
for i in range (1, 3000, 2):
    #calculates all x sub i values
    x = (x**2 + 1 ) % f 

    #stores the value in the array for gcd testing
    variable[i] = x 

    #calculates all of the x sub 2i values
    x = (x**2 + 1) % f

    #stores the value in the array for gcd testing
    variable[i+1] = x 

    #obtains the value of the gcd of the absolute value of x sub i minus x sub 2i and the fermat number,
    #using placeholder variable t to access the correct array values
    holder = gcd(abs(variable[t] - variable[t*2]), f)

    #if statement to test if the gcd is a factor and not relatively prime/the number itself
    if holder > 1 & holder < f:

        #if it passes the test, it prints the factor found, followed by the second facter
        print (str(holder) +  " and " + str(f/holder) +  " are factors of " + str(f))
        break
    t+=1


