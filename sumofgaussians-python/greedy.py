import SumofGaussians as SG
import numpy as np, sys
from location import location

seed = int(sys.argv[1])
dims = int(sys.argv[2])
ncenters = int(sys.argv[3])

np.random.seed(seed)

epsilon = 1e-8

loc = location(dims, ncenters)

compiling = True#for my stat compiling needs

i = 0
while (i < 100000):
    i = i + 1
    loca, e = loc.move()
    output = ""
    if loc.delta > epsilon:
        output = (" ".join(["%.8f"%(x) for x in loca]), e)
    else:
        #print(output)
        print("%d %d %d %.8f"%(seed,dims,ncenters,e))
        break
    if not compiling:
        print(output)

#print(loc.loc, loc.eval)
      