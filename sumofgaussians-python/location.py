import SumofGaussians as SG
import numpy as np, sys
import math

r = np.random
epsilon = 1e-8

class location():
    def __init__(self, dims, ncenters):
        self.sog = SG.SumofGaussians(dims,ncenters)
        self.dims = dims
        self.loc = r.ranf(dims)*10
        self.eval = self.sog.Eval(self.loc)
        self.delta = 1
    def move(self):
        d = self.sog.Deriv(self.loc)
        self.loc = self.loc + d * 0.01
        self.leval = self.eval
        self.eval = self.sog.Eval(self.loc)
        self.delta = (self.eval - self.leval)
        return (self.loc, self.eval)
    def anneal(self, t, progress):
        progress = 0.04 * (1-progress)
        runif = r.uniform(-0.05 + progress, 0.05 - progress, self.dims) #without bigger number, loc literally got nowhere, slowly decrease as we progress
        #print("runif: ", runif)
        y = (self.loc + runif) % 10; #add runif, but also modulo so we don't go out of range of [0, 10]... this makes it just go to the other side of the graph
        gy = self.sog.Eval(y);
        ra = r.ranf(1)
        p = -1
        accept = False;
        if gy > self.eval:
            accept = True;
        else:#some of this i changed because i looked at http://apmonitor.com/me575/index.php/Main/SimulatedAnnealing - anneal.py
            diff = gy - self.eval
            ediff = -diff
            p = math.exp(diff/(t*ediff))#t is always too big even at 1, this changes that. without this, no matter what t would be, p would always hover around 1. adding this actually made my function work! same as website and file commented above
            #print("t: ", t, "diff:", gy - self.eval, "p: ", p)
            if ra < p:
                #print("prob true")
                accept = True;
                
        #print(accept)
        if accept:
            self.loc = y;
            self.eval = gy;
        return (p, self.eval)

#while loc.delta > epsilon