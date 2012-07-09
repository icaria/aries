import subprocess;

W5 = 5
W15 = 15
list = [5, 15]
q3 = open("q3.txt", "w")
q4 = open("q4.txt", "w")
q5 = open("q5.txt", "w")

#------------------Question 3
step = 0.1;
max = 0.9

# FER = 0.05 case

for w in list:
	FER = 0.05
	subprocess.call(['./a.out', '-f', str(FER), '-W', str(w)], stdout=q3)


	FER = 0.1;
	i = FER;
	while i <= max:
	    subprocess.call(['./a.out', '-f', str(i), '-W', str(w)], stdout=q3)
            i += step



#--- Question 4
step = 40;
max = 500;
prop_delay = 20; 


#--- Question 5
step = 0.5;
max = 5;
C = 0.5;






'''



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

'''
