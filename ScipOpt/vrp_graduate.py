from pyscipopt import Model,quicksum,multidict
def vrp(I,J,K,M,d):
    model = Model("vrp")
    y={}
    for i in I:
        for k in K:
            y[i,k]=model.addVar(vtype="B",name="y_%d_%d")
    x={}
    for i in I:
        for j in J:
            for k in K:
                x[i,j,k]=model.addVar(vtype="B",name="x_%d_%d_%d")
    for k in K:
        model.addCons(quicksum(d[i,j]*x[i,j,k] for i in I for j in J)<=10,name="a_%d")
    for k in K:
        model.addCons(quicksum(x[0,j,k] for j in J)<=1,name="b_%d")
    for k in K:
        model.addCons(quicksum(x[i,0,k] for i in I)<=1,name="c_%d")
    for i in M:
        model.addCons(quicksum(y[i,k] for  k in K)==1,name="d_%d")
    for j in M:
        for k in K:
            model.addCons(quicksum(x[i,j,k] for i in I)==y[j,k],name="e_%d")
    for i in I:
        for k in K:
            model.addCons(x[i,i,k]==0,name="f_%d")
    for i in M:
        for j in M:
            for k in K:
                model.addCons(x[i,j,k]+x[j,i,k]<=1,name="g_%d")
    for j in J:
        for k in K:
            model.addCons(quicksum(x[i,j,k] for i in I)==quicksum(x[j,l,k] for l in J))

    model.setObjective(quicksum(x[i,j,k]*d[i,j] for i in I for j in J for k in K),"minimize")

    model.data=x,y,I,J,K,M,d

    return model


def make_data():
    I={0,1,2,3}
    J={0,1,2,3}
    K={1,2,3,4,5,6}
    M={1,2,3}

    d={(0,0):0,(0,1):0.8,(0,2):2.1,(0,3):3.5,
       (1,0):0.8,(1,1):0,(1,2):1.4,(1,3):3.3,
       (2,0):2.1,(2,1):1.4,(2,2):0,(2,3):1.4,
       (3,0):3.5,(3,1):3.3,(3,2):1.4,(3,3):0
      }

    return I,J,K,M,d
if __name__ == "__main__":
    I,J,K,M,d= make_data()
    model = vrp(I, J,K,M, d)
    model.writeProblem("Vrp.lp")
    model.writeOutput("vrp.log")
    model.optimize()
    EPS = 1.e-6
    x,y,I,J,K,M,d= model.data
    A = [(i, j,k) for (i, j,k) in x if model.getVal(x[i, j,k]) > EPS]
    B = [(i,k) for (i,k) in y if model.getVal(y[i,k]) > EPS]

    print("Optimal value:", model.getObjVal())
    print("the vehicle k will go to j from i", A)
    print("the vehicle k providing service in i", B)

