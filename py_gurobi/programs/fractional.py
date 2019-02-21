"""
fractional.py:  

Fractional optimization problem
    
Copyright (c) by Joao Pedro PEDROSO and Mikio KUBO, 2012
"""

from gurobipy import *

model = Model("fractional 1")

x = model.addVar()
y = model.addVar()
z = model.addVar()
t = model.addVar()
model.update()

model.addConstr(x + y + z == 32*t)
model.addConstr(2*x + 4*y + 8*z == 80*t)
model.addConstr(2*x + 4*y == 1)
model.setObjective(x + y, GRB.MINIMIZE)

model.optimize()

print "Opt. Val.=", model.ObjVal,", t=",t.X
print "(x,y,z)=", x.X/t.X, y.X/t.X, z.X/t.X
