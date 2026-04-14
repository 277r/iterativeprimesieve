### Working princicple

sieve of arestoehsnthestn
from 2 and upward, Every number is a prime, unless its a multiple of a previous prime
this means that all 2n are non-prime after 2 occured, 3n are nonprime after 3 occured, 5n are non-prime after 5 occured etc
a map of exclusions can be made to incorporate all the numbers that satisfy these requirements, but this is large
A list of counters can also be used, that increment each iteration counting up to sqrt(num_in)
if no counter has a divisor, the nextg number is also a prime
