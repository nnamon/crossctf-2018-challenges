def last3(number):
    if number <= 10:
        lastthreedigits = [0, 1, 2, 6, 24, 12, 72, 504, 32, 288, 288]
        return lastthreedigits [number]
    else:
        leftovers = number % 10
        a = (number/10)-1
        fivefacts = number/5
        threedigits = 1
        while a != 0:
            threedigits *= 144
            threedigits = threedigits %1000
            a -= 1
        if leftovers > 4:
            threedigits *= 72
        else:
            threedigits *= 144
        for i in range ((number - leftovers)%1000, (number)%1000):
            if i % 10 != 4:
                threedigits *= (i+1)
                threedigits = threedigits % 1000
        return (threedigits * last3(fivefacts)) % 1000

# gets last 3 digits of (5^n)!
def somesum (n):
    if n == 1:
        return 12
    else:
        a = [16 , 912, 984, 88]
        return a[n%4]

# gets last 3 digits of (product of 5^k factorial, from k = y down to 1)
def helper (y):
    total = 1
    i = 1
    while i <= y:
        total *= somesum(i) % 1000
        i += 1
    return total

# Returns the last 3 digits of the level n.
def mystery(n):
    return helper(n)%1000

flag = ""
for i in range(1, 13):
    flag += str(1000 + mystery(2**i))[1:]

print "CrossCTF{" + flag + "}"
