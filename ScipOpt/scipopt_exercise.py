from pyscipopt import Model,quicksum,multidict,SCIP_PARAMSETTING
def assignment(I,J,t):
    model=Model("assign")
    model.setPresolve(SCIP_PARAMSETTING.OFF)
    #model.setHeuristics(SCIP_PARAMSETTING.OFF)
    #model.disablePropagation()
    x={}
    for i in I:
        for j in J:
            x[i,j]=model.addVar(vtype="B")
    for i in I:
        model.addCons(quicksum(x[i,j] for j in J)==1)
    for j in J:
        model.addCons(quicksum(x[i,j] for i in I)==1)
    model.setObjective(quicksum(t[i,j]*x[i,j] for i in I for j in J),"minimize")
    model.data=x,I,J,t
    return model

def make_data():
    I={0,1,2,3}
    J={0,1,2,3}
    t={(0,0):4,(0,1):0.8,(0,2):2.1,(0,3):3.5,
       (1,0):0.8,(1,1):1,(1,2):1.4,(1,3):3.3,
       (2,0):2.1,(2,1):1.4,(2,2):2,(2,3):1.4,
       (3,0):3.5,(3,1):3.3,(3,2):1.4,(3,3):3
      }
    return I,J,t
if __name__ == "__main__":
    I,J,t=make_data()
    model=assignment(I,J,t)
    model.optimize()
    EPS=1.e-6
    x,I,J,t=model.data
    A=[(i,j) for (i,j) in x if model.getVal(x[i,j]) > EPS]
    if model.getStatus() == "optimal":
        print("optimize value",model.getObjVal())
        for i in  x:
            for  j in x:
                try:
                    dual=model.getDualsolLinear(x[i,j])
                except:
                    dual=None
                print(dual)
        print("the i person will be assigned in j work",A)
    
