from pyscipopt import Model

m = Model("svm")

x = m.addVar(vtype='B', name='x')
y = m.addVar(vtype='C', name='y')

m.addCons(3 * x + 2 * y >= 4)

m.optimize()
