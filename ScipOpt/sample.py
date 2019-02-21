from pyscipopt import Model

model=Model("sample")

x=model.addVar("x")
y=model.addVar("y",vtype="INTEGER")
model.setObjective(x+y)
model.addCons(2*x-y*y>=0)
model.optimize()
