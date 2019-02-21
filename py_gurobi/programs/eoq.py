"""
eoq.py:  piecewise linear model to the multi-item economic ordering quantity problem.

Approach: use a convex combination formulation.

Copyright (c) by Joao Pedro PEDROSO and Mikio KUBO, 2012
"""
from gurobipy import *

def eoq(I,F,h,d,w,W,a0,aK,K):
    """eoq --  multi-item capacitated economic ordering quantity model
    Parameters:
        - I: set of items
        - F[i]: ordering cost for item i
        - h[i]: holding cost for item i
        - d[i]: demand for item i
        - w[i]: unit weight for item i
        - W: capacity (limit on order quantity)
        - a0: lower bound on the cycle time (x axis)
        - aK: upper bound on the cycle time (x axis)
        - K: number of linear pieces to use in the approximation
    Returns a model, ready to be solved.
    """

    # construct points for piecewise-linear relation, store in a,b
    a,b = {},{}
    delta = float(aK-a0)/K
    for i in I:
        for k in range(K):
            T = a0 + delta*k
            a[i,k] = T                          # abscissa: cycle time
            b[i,k] = F[i]/T + h[i]*d[i]*T/2.    # ordinate: (convex) cost for this cycle time

    model = Model("multi-item, capacitated EOQ")
    x,y,c = {},{},{}
    for i in I:
        x[i] = model.addVar(vtype="C", name="x(%s)"%i)  # cycle time for item i
        c[i] = model.addVar(vtype="C", name="c(%s)"%i)  # total cost for item i
        for k in range(K):
            y[i,k] = model.addVar(ub=1, vtype="C", name="y(%s,%s)"%(i,k))
    model.update()

    for i in I:
        model.addConstr(quicksum(y[i,k] for k in range(K)) == 1)
        model.addConstr(quicksum(a[i,k]*y[i,k] for k in range(K)) == x[i])
        model.addConstr(quicksum(b[i,k]*y[i,k] for k in range(K)) == c[i])

    model.addConstr(quicksum(w[i]*d[i]*x[i] for i in I) <= W)

    model.setObjective(quicksum(c[i] for i in I), GRB.MINIMIZE)

    model.update()
    model.__data = x,y
    return model




if __name__ == "__main__":
    # multiple item EOQ
    I,F,h,d,w = multidict(
        {1:[300,10,10,20],
         2:[300,10,30,40],
         3:[300,10,50,10]}
        )
    W = 2000
    K = 1000
    a0,aK = 0.1,10
    model = eoq(I,F,h,d,w,W,a0,aK,K)
    model.optimize()
     
    x,y = model.__data
    EPS = 1.e-6
    for v in x:
        if x[v].X >= EPS:
            print x[v].VarName,x[v].X
     
    print "Obj:",model.ObjVal
