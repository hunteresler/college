#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#Hunter Esler
#CSCI 4350/5350
#OLA 3
#14 November 2019


import numpy as np, sys
from numpy import log2

Verbose = False

#from sort_attributes.py
def sort(data):

    # Special case of just one data sample will fail
    # without this check!
    if len(data.shape) < 2:
        data = np.array([data])

    # Sort all columns - just retain sorted indices
    # NOT the sorted data to prevent need to resort
    # later on...
    indices = np.argsort(data,axis=0)
    
    return indices

trainingName = (sys.argv[1])
testName = (sys.argv[2])

trainingData = np.loadtxt(trainingName);
testData = np.loadtxt(testName)

numT = trainingData.shape[0]
if trainingData.ndim == 1:
    trainingData = trainingData.reshape((1, numT))
    numT = 1

numC = trainingData.shape[1]
numClasses = int(trainingData[numT-1][numC-1])

#calculate probability of c class for subset i (indexes) for d dataset 
def prob(c, d, i):
    count = 0.
    for cl in i:
        if d[cl[numC-1]][numC-1]==c:
            count = count + 1
    if i.shape[0] < 1:#would this ever happen?
        return 0.
    return (count/i.shape[0])

#calculate the entropy of subset i (indexes) for dataset d
def ent(d, i):
    e = 0
    for c in range(numClasses+1):
        p = prob(c, d, i) # probability of class c in subset i
        if (p > 0): #don't want to crash with infinity
            e = e + (-p * log2(p)) #algorithm
    return e

#calculate the gain for splitting at a certain point in the subset s at split for dataset d. p is I
def calc_gain(d, s, split, I): 
    left,right = s[:split, ...], s[split:, ...] # left will always be less than the split value, right will always be greater than or equal to., from (v > cur)
    tot = s.shape[0]
    lp = split / tot
    rp = 1.-lp
    leftp = ent(d, left)
    rightp = ent(d, right)
    e = lp * leftp + rp * rightp
    return I - e # difference is gain

#node for id3 tree
class node():
    def __init__(self, d, checked, attr, split, splitindex, terminal=False, cl=0):
        self.attr = attr
        self.point = split
        self.terminal = terminal
        self.classification = cl
        if self.terminal==False:
            #split the dataset according to new split for attr
            left = np.empty((splitindex,numC))
            right = np.empty((d.shape[0]-splitindex, numC))
            lc = 0
            rc = 0
            for i in d:
                val = i[attr]
                if val < split:
                    left[lc] = i
                    lc = lc + 1
                else:
                    right[rc] = i
                    rc = rc + 1
                    
            if Verbose:
                print(f"SPLIT NODE - {self.attr} {self.point}") #{left[0].shape[0]} {right[0].shape[0]}")
            checked.append(attr)
            self.leftn = createNode(left, checked.copy())
            self.rightn = createNode(right, checked.copy())
        else:
            if Verbose:
                print(f"TERMINAL {attr}")
    def test(self, a):
        #print(a, self.attr)
        val = a[self.attr]
        if self.terminal==True:
            return self.classification
        if val < self.point:
            return self.leftn.test(a)
        else:
            return self.rightn.test(a)
     
curNode = None
def createNode(d, checked = []):
    indi = sort(d)
    
    terminal = True
    e = 0
    cur = None
    maxgain = 0.
    maxattr = -1
    maxgainsplitpoint = 0
    maxsplitind = -1
    indices = indi
    
    classcheck = -1
    
    numchecked = len(checked)
    
    #for calculating what terminal to be if no split points, or also seeing if we are terminal if there is only one class in set d
    counts = np.zeros(numC);
    maxcounts = 0
    for i in indices:
        cl = int(d[i[numC-1]][numC-1])
        if classcheck < 0:#first class we find
            classcheck = cl
        if cl != classcheck:#class isn't current class, we aren't a terminal node
            terminal = False
        counts[cl] = counts[cl] + 1
        if counts[cl] >= counts[maxcounts] and cl < maxcounts:
            maxcounts = cl
    
    #print(checked)
    if numchecked==numC - 1:
        checked = []
    
    if not terminal:
        e = ent(d, indi)#calculate I for d
        if Verbose:
            print(f"I: {e}")
        for attr in range(numC-1):
            if attr in checked:
                continue
            if Verbose: 
                print(f"ATTR: {attr}")
            cur = None
            ind = 0 # our split index in indices
            
            for i in indices:
                r = d[i[attr]] # actual row values
                cl = r[numC-1] # current class of row
                r = r[:-1] # removing class from row
                v = r[attr] # our attribute value
                if cur==None:
                    cur = v
                if v > cur: #potential split point
                    ismax = ""
                    gain = calc_gain(d, indices, ind, e)

                    #print("gain: ", gain)
                    if gain > maxgain and gain > 0.:
                        ismax = " (MAX)"
                        maxgain = gain
                        maxattr = attr
                        maxsplitind = ind
                        maxgainsplitpoint = (v + cur) / 2.0
                    if Verbose:
                        print(f"checked {cur} {v} gain: {gain}{ismax}, {ind}")
                    cur = v
                if Verbose:
                    print(r, cl)
                ind = ind + 1
    #if we calculated we are terminal, or there isn't a split
    if terminal or maxsplitind < 0:
        if maxsplitind < 0: #no split, pick majority
            e = maxcounts
        return node(d, [], 0, 0, 0, True, classcheck)
    return node(d, checked, maxattr, maxgainsplitpoint, maxsplitind)#make node, and repeat for left and right if necessarry

#create tree
n = createNode(trainingData)

correct = 0
#idk why this happens, but..
if testData.ndim==1:
    testData = testData.reshape((1, testData.shape[0]))

for i in testData:
    tes = n.test(i)
    if Verbose:
        print(i, tes)
    if i[numC-1] == tes:
        correct = correct + 1
        
print(correct)


    
    


