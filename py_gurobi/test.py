from gurobipy import *
import networkx
 
def tsp(V, c):
    def tsp_callback(model, where):
        if where != GRB.Callback.MIPSOL:
            return
        edges = []
        for (i, j) in x:
            if model.cbGetSolution(x[i, j])> 1.e-6:
                edges.append( (i, j) )
        G = networkx.Graph()
        G.add_edges_from(edges)
        Components = networkx.connected_components(G)
        clen = [len(c) for c in sorted(Components, key=len, reverse=True)]
        if len(clen) == 1:
            return
        for S in Components:
            model.cbLazy(quicksum(x[i, j] for i in S for j in S if j>i) <= len(S) - 1)
        return
 
    model = Model("tsp")
    x = {}
    for i in V:
        for j in V:
            if j > i:
                x[i, j] = model.addVar(ub=1)
    model.update()
    for i in V:
        model.addConstr(quicksum(x[j, i] for j in V if j < i) + quicksum(x[i, j] for j in V if j > i) == 2)
    model.setObjective(quicksum(c[i, j] * x[i, j] for i in V for j in V if j>i), GRB.MINIMIZE)
    model.update()
    model.__data = x
    return model,tsp_callback
 
def solve_tsp(V,c):
    model,tsp_callback = tsp(V,c)
    model.params.DualReductions = 1
    model.Params.OutputFlag = 1 # silent mode
    model.Params.TimeLimit = 1
    model.optimize(tsp_callback)
    x = model.__data
 
    EPS = 1.e-6
    edges = []
    for (i,j) in x:
        if x[i,j].X > EPS:
            edges.append( (i,j) )
    return model.ObjVal,edges
 
def tsp_path(V, edges): 
    Graph = networkx.Graph()
    Graph.add_nodes_from(V)
    for (i, j) in edges:
        Graph.add_edge(i, j)
        if (i == 1):
            end = j
        if (j == 1):
            end = i
    for path in networkx.all_simple_paths(Graph, source = 1, target = end):
        if(len(path) > 2) :
            return path
 
def read_instance(filename):
    with open(filename, 'r') as f:
        n = int(f.readline())
        V = range(1, n+1)
        c = {}
        i = 0
        for line in f:
            k = 0
            i += 1
            items = line.split(' ')
            for j in V:
                c[i, j] = (int(items[k]))
                k+=1
    f.close()
    return V, c
 
if __name__ == "__main__":
    argvs = sys.argv
    argc = len(argvs)
    if(argc <= 1):
        print ("Usage: # python %s filename" % argvs[0])
        quit()
 
    V ,c = read_instance(argvs[1])
 
    obj, edges = solve_tsp(V, c)
    print ("Optimal Value: ",obj)
    print (tsp_path(V, edges))
