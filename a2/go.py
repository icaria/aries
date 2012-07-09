import subprocess;

N = 500000
list = [5, 15]
q3 = open("q3_srb.txt", "w")
q4 = open("q4_srb.txt", "w")
q5 = open("q5_srb.txt", "w")


#------------------Question 3
step = 0.1;
max = 0.9

for w in list:
	FER = 0.05
	i = FER;
	subprocess.call(['./a.out', '-f', str(i), '-W', str(w), '-N', str(N)], stdout=q3)

	FER = 0.1;
	i = FER;
	while i <= max:
	    subprocess.call(['./a.out', '-f', str(i), '-W', str(w), '-N', str(N)], stdout=q3)
            i += step


#------------------ Question 4
step = 40;
max = 500;
prop_delay = 20; 

for w in list:
	i = prop_delay;
	while i <= max:
	    subprocess.call(['./a.out', '-p', str(i), '-W', str(w), '-N', str(N)], stdout=q4)
            i += step


#--------------------- Question 5
step = 0.5;
max = 5;
C = 0.5;

for w in list:
	i = C;
	while i <= max:
	    subprocess.call(['./a.out', '-c', str(i), '-W', str(w), '-N', str(N)], stdout=q5)
            i += step



