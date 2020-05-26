#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#Hunter Esler
#CSCI 4350/5350
#OLA 4
#Dec 3 2019
#Calculates K-means and tests it with (seed, clusters, training data, testing data). assumes all classifications are from 0 to n on the last column


import numpy as np, sys

Verbose = False

seed = (int)(sys.argv[1])
numClusters = (int)(sys.argv[2])
trainingName = (sys.argv[3])
testName = (sys.argv[4])

trainingData = np.loadtxt(trainingName);
testData = np.loadtxt(testName)

##weird things happen with one item
numT = trainingData.shape[0]#num training
if trainingData.ndim == 1:
    trainingData = trainingData.reshape((1, numT))
    numT = 1
    
if testData.ndim == 1:
    testData = testData.reshape((1, testData.shape[0]))

numC = trainingData.shape[1]#num attributes(with class label)
numAttributes = numC - 1#num attributes

#get number of classes, assuming that classes count from 0 to n for program to work
classesList = []
for c in trainingData:
    label = (int)(c[numC-1])
    if label not in classesList:
        classesList.append(label)
numClasses = len(classesList)

#print(numT, numC, numClasses)

np.random.seed(seed)

tData = np.delete(trainingData, numC-1, axis=1)#data without classification, for distance calculation

#node for id3 tree
def centroid(grabList):
    if len(grabList) > 0:
        index = grabList.pop(np.random.random_integers(0, high=len(grabList)-1))#pop index from grab list so we won't reuse it
        return tData[index]
    else:
        return tData[0]#works, more centroids than training data... basically duplicates
    
grabs = [x for x in range(numT)]#list of indices to grab from
centroids = [centroid(grabs) for x in range(numClusters)]

changed = 1#number of changed means
closest = np.empty((numT, 2)) ## (closest centroid, dist)

##calculate centroids depending on random selection of initial centroids
while (changed > 0):
    changed = 0
    closest[:,:] = -1
    for c in range(len(centroids)):
        for d in range(len(tData)):
            change = False
            dataPos = tData[d]
            centroidPos = centroids[c]
            dist = np.linalg.norm(dataPos-centroidPos)#https://stackoverflow.com/questions/1401712/how-can-the-euclidean-distance-be-calculated-with-numpy
            if closest[d][0] >= 0:#we already have a closest index
                if dist < closest[d][1]:#closer than previous centroid
                    change = True
            else:#haven't assigned a centroid yet, change
                change = True
            if change:#we decided to change, apply change
                closest[d][0] = c
                closest[d][1] = dist
                #print(dist)
                
    meansCalc = np.zeros((numClusters,numAttributes))#start with 0
    numDivs = np.zeros(numClusters)#number of elements for this centroid
    
    #summing
    for data in closest:
        i = (int)(data[0])#this is the closest centroid for this data entry
        meansCalc[i] = np.add(meansCalc[i],tData[i])#add to the mean calculation
        numDivs[i] = numDivs[i] + 1#add the number to divide by
        
    for c in range(len(centroids)):
        numDiv = numDivs[c]
        newMean = centroids[c].copy()#probably on top of one another, because first come first serve, just give itself as the mean, will not change
        if numDiv > 0:
            newMean = meansCalc[c] / numDiv#divide to get the mean
        if not np.allclose(newMean, centroids[c]):#are we changed? if so, update. check within tolerance or else weird things happen with floats, so we use allclose instead of array_equal
            centroids[c] = newMean
            changed = changed + 1
            #print(centroids[c], newMean)
    #print("changed",changed)
            
#add up class labels for each centroid
centroidsClass = np.zeros((numClusters, numClasses))
for c in range(len(closest)):
    i = (int)(closest[c][0])
    label = (int)(trainingData[c][numC-1])
    centroidsClass[i][label] = centroidsClass[i][label] + 1
#pick the max label index, discard the rest of the columns, no longer needed
for c in range(len(centroids)):
    centroidsClass[c][0] = np.argmax(centroidsClass[c])#autimagically gets smallest integer class  
centroidsClass = centroidsClass[:,0]#rest columns are trash
    
#test our k-means
correct = 0
for test in testData:
    closest = -1
    closestDist = 0
    testPos = test[:-1]
    for c in range(len(centroids)):
        change = False
        cPos = centroids[c]
        dist = np.linalg.norm(testPos-cPos)#again, euclidean distance as above link
        if closest >= 0:
            if dist < closestDist:
                change = True
        else:
            change = True
        if change:
            closest = c
            closestDist = dist
    if (int)(centroidsClass[closest]) == (int)(test[numC-1]):
        correct = correct + 1
    elif Verbose:
        print(centroidsClass[closest], test[numC-1])
        
print(correct)


    
    


