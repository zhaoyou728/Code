from pyscipopt import Model, quicksum
m= Model("svm")
vars =[]
for i in range(10):
    vars.append(m.addVar(vtype='B', name=str(i)))
m.addCons(vars[0] ** 2==1)
m.addCons((quicksum(i * vars[i] for i in range(10))<=15),
          name="mycons")
m.optimize()
