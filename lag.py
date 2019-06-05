"""
Author: You Zhao
Date: 2019/06/05
Content: Lagrange Relaxation with Sub-gradient Method for IP
Reference: KUBO Mikio's handbook and Wu Jian's source 
"""
from gurobipy import *
 
# create example instance
def example():
  # value of objects
  J, v = multidict({1:16, 2:19, 3:23, 4:28})
  # cost pair of objects
  a = {(1,1):2,    (1,2):3,    (1,3):4,    (1,4):5,
       (2,1):3000, (2,2):3500, (2,3):5100, (2,4):7200,
      }
  # cost limit
  I, b = multidict({1:7, 2:10000})
  return I, J, v, a, b
 
# create mkp model
def mkp(I, J, v, a, b):
  model = Model("mkp")
  x = {}
  # add binary variables
  for j in J:
    x[j] = model.addVar(vtype="B", name="x(%d)" % j)
  model.update()
  #add constraints
  cons=[]
  for i in I:
    cons.append(model.addConstr(quicksum(a[i,j]*x[j] for j in J) <= b[i]))
  model.setObjective(quicksum(v[j]*x[j] for j in J), GRB.MAXIMIZE)
  model.update()
  #initial setting
  xLBlog,xUBlog,steplog,scalelog,normlog=[],[],[],[],[]
  same=0
  norm=0.0
  step=1.0
  scale=1.0
  xLB=0.0
  xUB=0.0
  xlambda = [0.0] * len(J)
  slack = [0.0] * len(J)
  samelimit=3
  print("===========relaxation opt========")
  xUB=relaxUB(model)
  xLB=0
  obj_price=quicksum(v[j]*x[j] for j in J)
  ubmodel=0
  #loop
  for iter in range(50):
      if ubmodel==0:
          ubmodel=1
          lenrelax=len(cons)
          for i in range(lenrelax):
              model.remove(cons[i])
          cons=[]
      obj_lag=quicksum(xlambda[i]*(b[i]-quicksum(a[i,j]*x[j] for j in J)) for i in I)
      model.setObjective(obj_price+obj_lag,GRB.MAXIMIZE)
      model.update()
      print("===========first opt========")
      model.optimize()
      for j in J:
          print(x[j].x)
      for i in I:
          slack[i]=b[i]-sum(x[j].x*a[i,j] for j in J)
          #print(slack[i])

      if model.objval < xUB +1e-6:
          xUB = model.objval
          same = 0
      else:
          same += 1

      if same == samelimit:
          scale /= 2.0
          same = 0

      norm = sum(slack[i]**2.0 for i in I)

      step = scale * (model.objval-xLB) / norm

      for i in I:
          #xlambda[i] = min(0,xlambda[i]+step * slack[i])
          if xlambda[i] > step * slack[i]:
              xlambda[i] -= step * slack[i]
          else: 
              xlambda[i] = 0.0
      print("********cover*********")
      print(quicksum(v[j] for j in J)-quicksum(xlambda[i]*quicksum(a[i,j] for j in J) for i in I))
      for i in I:
          print(sum(x[j].x*a[i,j] for j in J))
          print(b[i])
          
      sumvalue=0
      
      for i in I:
          sumvalue+=sum(x[j].x*a[i,j] for j in J)
      sumlimit=sum(b[i] for i in I)

      print(sumvalue)
      print(sumlimit)

      if sumvalue<=sumlimit:
          ubmodel=0
          for i in I:
              cons.append(model.addConstr(quicksum(a[i,j]*x[j] for j in J) <= b[i]))
          for j in J:
              x[j].lb=x[j].x
              x[j].ub=x[j].x
          for j in J:
              print(x[j].x)
          model.setObjective(obj_price,GRB.MAXIMIZE)
          model.update()
          print("===========second opt========")
          model.optimize()

          xLB=max(xLB,model.objval)
          for j in J:
              x[j].lb=0.0
              x[j].ub=1.0

      xLBlog.append(xLB)
      xUBlog.append(xUB)
      steplog.append(step)
      scalelog.append(scale)
      normlog.append(norm)
  print("\n               *** Summary Report ***               \n")
  print("  Iter        LB               UB             scale        step          norm")

  for i in range(len(xLBlog)):
      print("  %3d    %12.6f    %12.6f    %12.6f    %8.6f     %8.6f"    \
                  % (i, xLBlog[i], xUBlog[i], scalelog[i], steplog[i],normlog[i]))
  return model
#continous relaxation
def relaxUB(mtrans):
    mrelax = mtrans.relax()
    mrelax.optimize()
    return mrelax.objval
 
# entry point
if __name__ == "__main__":
  I, J, v, a, b = example()
  model = mkp(I, J, v, a, b)
