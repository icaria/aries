import os;
import subprocess;

#Question 4 values
step = 0.05;
min = 0.2;
max = 0.95;
L = 2000
C = 1

T = 5000

#Question 5 values
#L = 5000
#min = 0.5


p = min;
while p < 1:
    print "---------------------------"
    print p
    print "---------------------------"

    lam = int( p * C *(1000000/ L));
    #./a.out T  lamda  L  C  K (optional)
    subprocess.call(["./a.out", str(T), str(lam), str(L), str(C) ])    
    p += step