import subprocess;


step = 0.05;
min = 0.2;
max = 0.95;
L = 2000
C = 1
T = 5000
lam = 100

#------------------Question 3
print "---------------------------Q3"

i = 0
while i < 5:
    subprocess.call(['./a.out', str(T), str(lam), str(L), str(C)])    
    print ""
    i += 1

#------------------Question 6
print "---------------------------Q6"
p = 1.2;
lam = int( p * C *(1000000/ L));
subprocess.call(["./a.out", str(T), str(lam), str(L), str(C) ])    
print ""

#-------------------Question 4 values
print "---------------------------Q4"

p = min;
while p < 1:
    print p, 
    print ",",
    lam = int( p * C *(1000000/ L));
    subprocess.call(["./a.out", str(T), str(lam), str(L), str(C) ])    
    p += step
    print ""
    
#---------------------Question 5 values
print "---------------------------Q5"
L = 5000
min = 0.5
p = min;
while p < 1:
    print p, 
    print ",",
    lam = int( p * C *(1000000/ L));
    subprocess.call(["./a.out", str(T), str(lam), str(L), str(C) ])    
    p += step
    print ""

#---------------------Question 8 values
print "---------------------------Q8"
L = 2000
min = 0.5
max = 1.5
step = 0.1
list = [5, 10, 20, 50]

for K in list:
    p = min;
    while p < 1.6:
        print p, 
        print ",",
        print K,
        print ",",
        lam = int( p * C *(1000000/ L));
        subprocess.call(["./a.out", str(T), str(lam), str(L), str(C), str(K) ])    
        p += step
        print ""
    if K == 5:
        p = 5;
        print p, 
        print ",",
        print K,
        print ",",
        lam = int( p * C *(1000000/ L));
        subprocess.call(["./a.out", str(T), str(lam), str(L), str(C), str(K) ])    
        p += step
        print ""

