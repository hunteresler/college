import SumofGaussians as SG
import numpy as np, sys
import math
from location import location

seed = int(sys.argv[1])
dims = int(sys.argv[2])
ncenters = int(sys.argv[3])

np.random.seed(seed)

epsilon = 1e-8

#create sog class
loc = location(dims, ncenters)

i = 0
#max # of iterations
times = 60000

#http://apmonitor.com/me575/index.php/Main/SimulatedAnnealing - anneal.py
#i used this because it makes the math very easy, only used for math
# Probability of accepting worse solution at the start
begin = 0.99
# Probability of accepting worse solution at the end
end = 0.01
# Initial temperature
initial = -1.0/math.log(begin)#
# Final temperature
final = -1.0/math.log(end)
# Fractional reduction every cycle
frac = (final/initial)**(1.0/(times))
#print(initial, final, frac)

epsilon = 1e-8

samecutoff = 15 #cut off if we haven't changed by epsilon 15 times.. either at max at the end, or at a flat spot
same = 0 # number of times at same eval
lastval = 0;
compiling = True # using for compiling data for stats
t = initial;
t2 = 1;
while (i < times):
    i = i + 1
    t = t * frac
    if t > 0:#not possible anymore but
        p, val = loc.anneal(t, (times-i)/times);#temp, progress through loop
        output = (" ".join(["%.8f"%(x) for x in loc.loc]), "%.8f"%loc.eval)

        #checking if same difference
        diff = abs(val - lastval)
        if diff <= epsilon:
            same = same + 1
        else:
            same = 0
        lastval = val
        if not compiling:
            #for u
            print(output)
        elif same >= samecutoff or i >= times:
            #print(output)
            if compiling:
                #for me
                print("%d %d %d %.8f"%(seed,dims,ncenters,val))
            break
    
        
#print(times)
    
#print(loc.loc, loc.eval);
    
      