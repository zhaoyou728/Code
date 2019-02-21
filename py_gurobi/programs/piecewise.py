"""
piecewise.py:  several approaches for solving problems with piecewise linear functions.

Approaches:
    - mult_selection: multiple selection model
    - convex_comb_sos: model with SOS2 constraints
    - convex_comb_dis: convex combination with binary variables (disaggregated model)
    - convex_comb_dis_log: convex combination with a logarithmic number of binary variables
    - convex_comb_agg: convex combination with binary variables (aggregated model)
    - convex_comb_agg_log: convex combination with a logarithmic number of binary variables

Copyright (c) by Joao Pedro PEDROSO and Mikio KUBO, 2012
"""
from gurobipy import *
import math
import random

def mult_selection(model,a,b):
    """mult_selection -- add piecewise relation with multiple selection formulation
    Parameters:
        - model: a model where to include the piecewise linear relation
        - a[k]: x-coordinate of the k-th point in the piecewise linear relation
        - b[k]: y-coordinate of the k-th point in the piecewise linear relation
    Returns the model with the piecewise linear relation on added variables x, f, and z.
    """

    K = len(a)-1
    y,z = {},{}
    for k in range(K):
        y[k] = model.addVar(lb=-GRB.INFINITY) # do not name variables for avoiding clash
        z[k] = model.addVar(vtype="B")
    x = model.addVar(lb=a[0], ub=a[K], vtype="C")
    f = model.addVar(lb=-GRB.INFINITY)
    model.update()

    for k in range(K):
        model.addConstr(y[k] >= a[k]*z[k])
        model.addConstr(y[k] <= a[k+1]*z[k])

    model.addConstr(quicksum(z[k] for k in range(K)) == 1)
    model.addConstr(x == quicksum(y[k] for k in range(K)))

    c = [float(b[k+1]-b[k])/(a[k+1]-a[k]) for k in range(K)]
    d = [b[k]-c[k]*a[k] for k in range(K)]
    model.addConstr(f == quicksum(d[k]*z[k] + c[k]*y[k] for k in range(K)))

    return x,f,z



def convex_comb_sos(model,a,b):
    """convex_comb_sos -- add piecewise relation with gurobi's SOS constraints
    Parameters:
        - model: a model where to include the piecewise linear relation
        - a[k]: x-coordinate of the k-th point in the piecewise linear relation
        - b[k]: y-coordinate of the k-th point in the piecewise linear relation
    Returns the model with the piecewise linear relation on added variables x, f, and z.
    """
    K = len(a)-1
    z = {}
    for k in range(K+1):
        z[k] = model.addVar(lb=0, ub=1, vtype="C") # do not name variables for avoiding clash
    x = model.addVar(lb=a[0], ub=a[K], vtype="C")
    f = model.addVar(lb=-GRB.INFINITY, vtype="C")
    model.update()

    model.addConstr(x == quicksum(a[k]*z[k] for k in range(K+1)))
    model.addConstr(f == quicksum(b[k]*z[k] for k in range(K+1)))

    model.addConstr(quicksum(z[k] for k in range(K+1)) == 1)
    model.addSOS(GRB.SOS_TYPE2, [z[k] for k in range(K+1)])

    return x,f,z



def convex_comb_dis(model,a,b):
    """convex_comb_dis -- add piecewise relation with convex combination formulation
    Parameters:
        - model: a model where to include the piecewise linear relation
        - a[k]: x-coordinate of the k-th point in the piecewise linear relation
        - b[k]: y-coordinate of the k-th point in the piecewise linear relation
    Returns the model with the piecewise linear relation on added variables x, f, and z.
    """
    K = len(a)-1
    yL,yR,z = {},{},{}
    for k in range(K):
        yL[k] = model.addVar(lb=0, ub=1, vtype="C") # do not name variables for avoiding clash
        yR[k] = model.addVar(lb=0, ub=1, vtype="C")
        z[k] = model.addVar(vtype="B")
    x = model.addVar(lb=a[0], ub=a[K], vtype="C")
    f = model.addVar(lb=-GRB.INFINITY, vtype="C")
    model.update()

    model.addConstr(x == quicksum(a[k]*yL[k] + a[k+1]*yR[k] for k in range(K)))
    model.addConstr(f == quicksum(b[k]*yL[k] + b[k+1]*yR[k] for k in range(K)))
    for k in range(K):
        model.addConstr(yL[k] + yR[k] == z[k])

    model.addConstr(quicksum(z[k] for k in range(K)) == 1)

    return x,f,z



def gray(i):
    return i^i/2



def convex_comb_dis_log(model,a,b):
    """convex_comb_dis_log -- add piecewise relation with a logarithmic number of binary variables
    using the convex combination formulation.
    Parameters:
        - model: a model where to include the piecewise linear relation
        - a[k]: x-coordinate of the k-th point in the piecewise linear relation
        - b[k]: y-coordinate of the k-th point in the piecewise linear relation
    Returns the model with the piecewise linear relation on added variables x, f, and z.
    """
    K = len(a)-1
    G = int(math.ceil((math.log(K)/math.log(2))))     # number of required bits
    N = 1<<G                                          # number of required variables
    # print "K,G,N:",K,G,N
    yL,yR,z = {},{},{}
    for k in range(N):
        yL[k] = model.addVar(lb=0, ub=1, vtype="C") # do not name variables for avoiding clash
        yR[k] = model.addVar(lb=0, ub=1, vtype="C")
    x = model.addVar(lb=a[0], ub=a[K], vtype="C")
    f = model.addVar(lb=-GRB.INFINITY, vtype="C")

    g = {}
    for j in range(G):
        g[j] = model.addVar(vtype="B")
    model.update()

    model.addConstr(x == quicksum(a[k]*yL[k] + a[k+1]*yR[k] for k in range(K)))
    model.addConstr(f == quicksum(b[k]*yL[k] + b[k+1]*yR[k] for k in range(K)))
    model.addConstr(quicksum(yL[k] + yR[k] for k in range(K)) == 1)

    # binary variables setup
    for j in range(G):
        ones = []
        zeros = []
        for k in range(K):
            if k & (1<<j):
                ones.append(k)
            else:
                zeros.append(k)
        model.addConstr(quicksum(yL[k] + yR[k] for k in ones) <= g[j])
        model.addConstr(quicksum(yL[k] + yR[k] for k in zeros) <= 1-g[j])

    return x,f,yL,yR



def convex_comb_agg(model,a,b):
    """convex_comb_agg -- add piecewise relation convex combination formulation -- non-disaggregated.
    Parameters:
        - model: a model where to include the piecewise linear relation
        - a[k]: x-coordinate of the k-th point in the piecewise linear relation
        - b[k]: y-coordinate of the k-th point in the piecewise linear relation
    Returns the model with the piecewise linear relation on added variables x, f, and z.
    """
    K = len(a)-1
    y,z = {},{}
    for k in range(K+1):
        y[k] = model.addVar(lb=0, ub=1, vtype="C") # do not name variables for avoiding clash
    for k in range(K):
        z[k] = model.addVar(vtype="B")
    x = model.addVar(lb=a[0], ub=a[K], vtype="C")
    f = model.addVar(lb=-GRB.INFINITY, vtype="C")
    model.update()

    model.addConstr(x == quicksum(a[k]*y[k] for k in range(K+1)))
    model.addConstr(f == quicksum(b[k]*y[k] for k in range(K+1)))
    model.addConstr(y[0] <= z[0])
    model.addConstr(y[K] <= z[K-1])
    for k in range(1,K):
        model.addConstr(y[k] <= z[k-1]+z[k])
    model.addConstr(quicksum(y[k] for k in range(K+1)) == 1)
    model.addConstr(quicksum(z[k] for k in range(K)) == 1)
    return x,f,z



def convex_comb_agg_log(model,a,b):
    """convex_comb_agg_log -- add piecewise relation with a logarithmic number of binary variables
    using the convex combination formulation -- non-disaggregated.
    Parameters:
        - model: a model where to include the piecewise linear relation
        - a[k]: x-coordinate of the k-th point in the piecewise linear relation
        - b[k]: y-coordinate of the k-th point in the piecewise linear relation
    Returns the model with the piecewise linear relation on added variables x, f, and z.
    """
    K = len(a)-1
    G = int(math.ceil((math.log(K)/math.log(2))))     # number of required bits
    y,g = {},{}
    for k in range(K+1):
        y[k] = model.addVar(lb=0, ub=1, vtype="C") # do not name variables for avoiding clash
    for j in range(G):
        g[j] = model.addVar(vtype="B")
    x = model.addVar(lb=a[0], ub=a[K], vtype="C")
    f = model.addVar(lb=-GRB.INFINITY, vtype="C")
    model.update()

    model.addConstr(x == quicksum(a[k]*y[k]  for k in range(K+1)))
    model.addConstr(f == quicksum(b[k]*y[k]  for k in range(K+1)))
    model.addConstr(quicksum(y[k] for k in range(K+1)) == 1)

    # binary variables setup
    for j in range(G):
        zeros,ones = [0],[]
        # print j,"\tinit zeros:",zeros,"ones:",ones
        for k in range(1,K+1):
            # print j,k,"\t>zeros:",zeros,"ones:",ones
            if (1 & gray(k)>>j) == 1 and (1 & gray(k-1)>>j) == 1:
                ones.append(k)
            if (1 & gray(k)>>j) == 0 and (1 & gray(k-1)>>j) == 0:
                zeros.append(k)
            # print j,k,"\tzeros>:",zeros,"ones:",ones

        # print j,"\tzeros:",zeros,"ones:",ones
        model.addConstr(quicksum(y[k] for k in ones) <= g[j])
        model.addConstr(quicksum(y[k] for k in zeros) <= 1-g[j])

    return x,f,y


if __name__ == "__main__":
    # random.seed(1)

    a = [ -10, 10, 15,  25, 30, 35, 40, 45, 50, 55, 60, 70]
    b = [ -20,-20, 15, -21,  0, 50, 18,  0, 15, 24, 10, 15]

    print "\n\n\npiecewise: multiple selection"
    model = Model("multiple selection")
    x,f,z = mult_selection(model,a,b) # x,f --> piecewise linear replacement of x,f(x) based on points a,b
    # model using x and y (and possibly other variables)
    u = model.addVar(vtype="C", name="u")
    model.update()
    A = model.addConstr(3*x + 4*f <= 250, "A")
    B = model.addConstr(7*x - 2*f + 3*u == 170, "B")
    model.setObjective(2*x + 15*f + 5*u, GRB.MAXIMIZE)
    model.optimize()
    print "x:",x.X
    print "f:",f.X
    print "u:",u.X

    print "\n\n\npiecewise: disaggregated convex combination"
    model = Model("disaggregated convex combination")
    x,f,z = convex_comb_dis(model,a,b) 
    u = model.addVar(vtype="C", name="u")
    model.update()
    A = model.addConstr(3*x + 4*f <= 250, "A")
    B = model.addConstr(7*x - 2*f + 3*u == 170, "B")
    model.setObjective(2*x + 15*f + 5*u, GRB.MAXIMIZE)
    model.optimize()
    print "x:",x.X
    print "f:",f.X
    print "u:",u.X

    print "\n\n\npiecewise: disaggregated convex combination, logarithmic number of variables"
    model = Model("disaggregated convex combination (log)")
    x,f,z = convex_comb_dis(model,a,b) 
    u = model.addVar(vtype="C", name="u")
    model.update()
    A = model.addConstr(3*x + 4*f <= 250, "A")
    B = model.addConstr(7*x - 2*f + 3*u == 170, "B")
    model.setObjective(2*x + 15*f + 5*u, GRB.MAXIMIZE)
    model.optimize()
    print "x:",x.X
    print "f:",f.X
    print "u:",u.X

    print "\n\n\npiecewise: SOS2 constraint"
    model = Model("SOS2")
    x,f,y = convex_comb_sos(model,a,b) 
    u = model.addVar(vtype="C", name="u")
    model.update()
    A = model.addConstr(3*x + 4*f <= 250, "A")
    B = model.addConstr(7*x - 2*f + 3*u == 170, "B")
    model.setObjective(2*x + 15*f + 5*u, GRB.MAXIMIZE)
    model.optimize()
    print "x:",x.X
    print "f:",f.X
    print "u:",u.X

    print "\n\n\npiecewise: aggregated convex combination"
    model = Model("aggregated convex combination")
    x,f,z = convex_comb_agg(model,a,b)
    u = model.addVar(vtype="C", name="u")
    model.update()
    A = model.addConstr(3*x + 4*f <= 250, "A")
    B = model.addConstr(7*x - 2*f + 3*u == 170, "B")
    model.setObjective(2*x + 15*f + 5*u, GRB.MAXIMIZE)
    model.optimize()
    print "x:",x.X
    print "f:",f.X
    print "u:",u.X

    print "\n\n\npiecewise: aggregated convex combination, logarithmic number of variables"
    model = Model("aggregated convex combination (log)")
    x,f,y = convex_comb_agg_log(model,a,b)
    u = model.addVar(vtype="C", name="u")
    model.update()
    A = model.addConstr(3*x + 4*f <= 250, "A")
    B = model.addConstr(7*x - 2*f + 3*u == 170, "B")
    model.setObjective(2*x + 15*f + 5*u, GRB.MAXIMIZE)
    model.optimize()
    print "x:",x.X
    print "f:",f.X
    print "u:",u.X
