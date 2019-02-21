import numpy as np
import matplotlib.pyplot as plt

def inputfun(x):
    return (x-2)*(x+3)*(x+8)*(x-9)

initT=1000
minT=1
iterL=1000
delta=0.95
k=1

initx=10*(2*np.random.rand()-1)
nowt=initT
print("init soulution",initx)
xx=np.linspace(-10,10,300)
yy=inputfun(xx)
plt.figure()
plt.plot(xx,yy)
plt.plot(initx,inputfun(initx),"o")

while nowt>minT:
    for i in np.arange(1,iterL,1):
        funVal=inputfun(initx)
        xnew=initx+(2*np.random.rand()-1)
        if xnew>=-10 and xnew<=10:
            funnew=inputfun(xnew)
            res=funnew-funVal
            if res<0:
                initx=xnew
            else:
                p=np.exp(-(res)/(k*nowt))
                if np.random.rand()<p:
                    initx=xnew
    nowt=nowt*delta
print("optimal solution",initx)
print("opitmal value",inputfun(initx))
plt.plot(initx,inputfun(initx),"*r")
plt.show()
