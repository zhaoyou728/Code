"""
prodmix.py:  product mix model

Data:
    I - set of products
    K - set of raw materials
    p[i] - profit for product i
    LB[k], UB[k] - lower and upper bounds to usage of material k
    a[i,k] - quantity of material k used in product i
    
Copyright (c) by Joao Pedro PEDROSO and Mikio KUBO, 2012
"""
from gurobipy import *

a = { (1,1):.25, (1,2):.15, (1,3):.3,
      (2,1):.3,  (2,2):.3,  (2,3):.1,
      (3,1):.15, (3,2):.65, (3,3):.05,
      (4,1):.1,  (4,2):.05,  (4,3):.85
      } 
I,p = multidict({1:5, 2:6, 3:8, 4:20})
K,LB,UB = multidict({1:[.2,.2], 2:[.0,.35], 3:[.45,1.0]})

model = Model("product mix")

x = {}
for i in I:
    x[i]=model.addVar()
model.update()

model.addConstr(quicksum(x[i] for i in I) ==1)
for k in K:
    model.addConstr(quicksum(a[i,k]*x[i] for i in I) <= UB[k])
    model.addConstr(quicksum(a[i,k]*x[i] for i in I) >= LB[k])
model.setObjective(quicksum(p[i]*x[i] for i in I), GRB.MINIMIZE)

model.optimize()

for i in I:
    print i,x[i].X
