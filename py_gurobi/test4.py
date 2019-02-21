import numpy as np
import matplotlib.pyplot as plt
import pdb


coordinates = np.array([[565.0,575.0],[25.0,185.0],[345.0,750.0],[945.0,685.0],[845.0,655.0],
                        [880.0,660.0],[25.0,230.0],[525.0,1000.0],[580.0,1175.0],[650.0,1130.0],
                        [1605.0,620.0],[1220.0,580.0],[1465.0,200.0],[1530.0,  5.0],[845.0,680.0],
                        [725.0,370.0],[145.0,665.0],[415.0,635.0],[510.0,875.0],[560.0,365.0],
                        [300.0,465.0],[520.0,585.0],[480.0,415.0],[835.0,625.0],[975.0,580.0],
                        [1215.0,245.0],[1320.0,315.0],[1250.0,400.0],[660.0,180.0],[410.0,250.0],
                        [420.0,555.0],[575.0,665.0],[1150.0,1160.0],[700.0,580.0],[685.0,595.0],
                        [685.0,610.0],[770.0,610.0],[795.0,645.0],[720.0,635.0],[760.0,650.0],
                        [475.0,960.0],[95.0,260.0],[875.0,920.0],[700.0,500.0],[555.0,815.0],
                        [830.0,485.0],[1170.0, 65.0],[830.0,610.0],[605.0,625.0],[595.0,360.0],
                        [1340.0,725.0],[1740.0,245.0]])
def getdistmat(coordinates):
    num=coordinates.shape[0]
    distmat=np.zeros((52,52))
    for i in range(num):
        for j in range(i,num):
            distmat[i][j]=distmat[j][i]=np.linalg.norm(coordinates[i]-coordinates[j])
    return distmat

def initpara():
    alpha=0.99
    t=(1,100)
    markovlen=1000
    return alpha,t,markovlen

num=coordinates.shape[0]
distmat=getdistmat(coordinates)

solutionnew=np.arange(num)

solutioncurrent=solutionnew.copy()
valuecurrent=99000

solutionbest=solutionnew.copy()
valuebest=99000

alpha,t2,markovlen=initpara()
t=t2[1]

result=[]
while t>t2[0]:
    for i in np.arange(markovlen):
        if np.random.rand()>0.5:
            while True:
                loc1=np.int(np.ceil(np.random.rand()*(num-1)))
                loc2=np.int(np.ceil(np.random.rand()*(num-1)))
                if loc1 != loc2:
                    break
                solutionnew[loc1],solutionnew[loc1]=solutionnew[loc2],solutionnew[loc1]
        else:
            while True:
                loc1=np.int(np.ceil(np.random.rand()*(num-1)))
                loc2=np.int(np.ceil(np.random.rand()*(num-1)))
                loc3=np.int(np.ceil(np.random.rand()*(num-1)))

                if ((loc1!=loc2)&(loc2!=loc3)&(loc3!=loc1)):
                    break
            if loc1>loc2:
                loc1,loc2=loc2,loc1
            if loc2>loc3:
                loc2,loc3=loc3,loc2
            if loc1>loc2:
                loc1,loc2=loc2,loc1

            tmplist=solutionnew[loc1:loc2].copy()
            solutionnew[loc1:loc3-loc2+1+loc1] = solutionnew[loc2:loc3+1].copy()
            solutionnew[loc3-loc2+1+loc1:loc3+1] = tmplist.copy()
            valuenew=0
            for i in range(num-1):
                valuenew += distmat[solutionnew[i]][solutionnew[i+1]]
            valuenew += distmat[solutionnew[0]][solutionnew[51]]

            if valuenew<valuecurrent:
                valuecurrent=valuenew
                solutioncurrent=solutionnew.copy()
                
                if valuenew<valuecurrent:
                    valuebest=valuenew
                    solutionbest=solutionnew.copy()
            else:
                if np.random.rand() < np.exp(-(valuenew-valuecurrent)/t):
                    valuecurrent = valuenew
                    solutioncurrent = solutionnew.copy()
                else:
                    solutionnew=solutioncurrent.copy()
    t=alpha*t
    result.append(valuebest)
    print(t)
plt.plot(np.array(result))
plt.ylabel("bestvalue")
plt.xlabel("t")
plt.show()
