import numpy as np
from scipy import linalg
# Define a function simple to call for the inner product
def scalarInner(a,b):
    return(np.asscalar(a.T.dot(b)))
from optimizationExceptions import *
import itertools as itt
def vertexEnumeration(A,b,c):
    m,n = A.shape
    if b.shape != (m,1):
        raise OptimizationInputError("Incompatible sizes: A is {}x{}, b is {}x{}, and should be {}x1".format(m,n,b.shape[0],b.shape[1],m))
    if c.shape != (n,1):
        raise OptimizationInputError("Incompatible sizes: A is {}x{}, c is {}x{}, and should be {}x1".format(m,n,c.shape[0],c.shape[1],n))
    optvalue = np.inf
    iters = list()
    for k in itt.combinations(range(n),m):
        B = A[:,k]
        try:
            x = linalg.solve(B,b)
            xfull = np.zeros((n,1))
            for i,ik in enumerate(k):
                xfull[[ik],:] = x[[i],:]
            iteroutput = [xfull]
            if (x >= 0).all():
                f = scalarInner(xfull,c)
                iteroutput += [f]
                if f < optvalue:
                    optvalue = f
                    solution = xfull
            else:
                iteroutput += [np.inf]
        except linalg.LinAlgError:
            iteroutput += [np.inf]
            pass
        iters.append(iteroutput)
    return solution,optvalue,iters

if __name__ == "__main__":
    A = np.matrix([[1,1,1,0],[1,-1,0,1]])
    b = np.array([[1],[1]])
    c = np.array([[-1],[-2],[0],[0]])
    sol,optvalue,iters = vertexEnumeration(A,b,c)
