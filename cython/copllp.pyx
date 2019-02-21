cdef extern from "c/copl.h":
    ctypedef struct optsol:
        int n
        int m
        double time
        double fv
        double dfv
        double* optx
        double* opty
    optsol* Copllpmps(char * nmps, bint docross,int prelevel,int showiter, int showtime)
    optsol* CopllpMtx_Spa(int m1, int m2, int n, double * c, int * I1, int * J1, double * K1, int size1, double * b1, int * I2, int * J2,
                          double * K2, int size2, double * b2,double * l, double * u,bint docross,int prelevel,int showiter, int showtime)
    double getcoplinf()

from libc.stdlib cimport calloc
from scipy.sparse import find
import numpy as ny

res = {"fv":None, "dfv": None, "optx":None, "opty":None}

cdef double coplinf
coplinf = getcoplinf()
INF = coplinf

def linprg(*args, **kwargs):
    #for value in args:
    #    print "another arg:", type(value)
    #for key in kwargs:
    #    print "another keyword arg: %s: %s" % (key, kwargs[key])
    #print('%%%%%%%%%%%%%%%%%%%')


    cdef bint docross = 1
    cdef int prelevel = 5
    cdef bint showiter = 1
    cdef bint showtime = 1
    gomps = 0
    beobj = 0
    beAineq = 0
    bebineq = 0
    beAeq = 0
    bebeq = 0
    belb = 0
    beub = 0
    for key in kwargs:
        if key == 'prelevel':
            prelevel = kwargs['prelevel']
            continue
        if key == 'docross':
            docross = kwargs['docross']
            continue
        if key == 'showiter':
            showiter = kwargs['showiter']
        if key == 'showtime':
            showtime = kwargs['showtime']
        if key == 'path':
            nmps = kwargs['path']
            gomps = 1
            continue


        if key == 'obj':
            beobj = 1
            obj = kwargs['obj']
            continue
        if key == 'Aineq':
            beAineq = 1
            Aineq = kwargs['Aineq']
            continue
        if key == 'Aeq':
            beAeq = 1
            Aeq = kwargs['Aeq']
            continue
        if key == 'bineq':
            bebineq = 1
            bineq = kwargs['bineq']
            continue
        if key == 'beq':
            bebeq = 1
            beq = kwargs['beq']
            continue
        if key == 'lb':
            belb = 1
            lb = kwargs['lb']
            continue
        if key == 'ub':
            beub = 1
            ub = kwargs['ub']
            continue



    cdef optsol* sol
    if args.__len__() == 1:
        nmps = args[0]
        gomps = 1
    if gomps:
        sol = Copllpmps(<char*>nmps, docross, prelevel, showiter, showtime)
        if sol:
            optx = []
            for i in range(sol.n):
                optx.append(sol.optx[i])
            opty = []
            for i in range(sol.m):
                opty.append(sol.opty[i])
            res['fv'] = sol.fv
            res['dfv'] = sol.dfv
            res['optx'] = optx
            res['opty'] = opty
        return res

    cdef int m1
    cdef int m2
    cdef int n1
    cdef int n2
    cdef int n
    cdef int size1
    cdef int size2
    cdef int * I1
    cdef int * J1
    cdef int * I2
    cdef int * J2
    cdef double * c
    cdef double * K1
    cdef double * K2
    cdef double * b1
    cdef double * b2
    cdef double * L
    cdef double * U



    m1 = 0
    m2 = 0
    n1 = 0
    n2 = 0
    size1 = 0
    size2 = 0
    I1 = NULL
    J1 = NULL
    K1 = NULL
    I2 = NULL
    J2 = NULL
    K2 = NULL
    b1 = NULL
    b2 = NULL

    if args.__len__() == 7 or args.__len__() == 5:
        A1 = args[1]
        A2 = args[3]
        m1 = A1.shape[0]
        n1 = A1.shape[1]
        m2 = A2.shape[0]
        n2 = A2.shape[1]
        if n1 != n2:
            print('''wrong dimention :
                     A1 %d * %d
                     A2 %d * %d
                  '''%(m1,n1,m2,n2))
            return
        n = n1
        #print('7 paras',n) #Danny
        c = <double*>calloc(n,sizeof(double))
        L = <double*>calloc(n,sizeof(double))
        U = <double*>calloc(n,sizeof(double))
        for i in range(n):
            c[i] = args[0][i]
            L[i] = 0
            U[i] = coplinf

        b1 = <double*>calloc(m1,sizeof(double))
        b2 = <double*>calloc(m2,sizeof(double))
        for i in range(m1):
            b1[i] = args[2][i]
        for i in range(m2):
            b2[i] = args[4][i]

        [I, J, K] = find(A1)
        size1 = I.shape[0]
        I1 = <int*>calloc(size1,sizeof(int))
        J1 = <int*>calloc(size1,sizeof(int))
        K1 = <double*>calloc(size1,sizeof(double))
        for i in range(size1):
            I1[i] = I[i]+1
            J1[i] = J[i]+1
            K1[i] = K[i]

        [I, J, K] = find(A2)
        size2 = I.shape[0]
        I2 = <int*>calloc(size2,sizeof(int))
        J2 = <int*>calloc(size2,sizeof(int))
        K2 = <double*>calloc(size2,sizeof(double))
        for i in range(size2):
            I2[i] = I[i]+1
            J2[i] = J[i]+1
            K2[i] = K[i]

        if args.__len__() == 7:
            for i in range(n):
                L[i] = args[5][i]
                U[i] = args[6][i]


        sol = CopllpMtx_Spa(m1,m2,n,c,I1,J1,K1,size1,b1,I2,J2,K2,size2,b2,L, U, docross, prelevel, showiter, showtime)
        if sol:
            optx = []
            for i in range(sol.n):
                optx.append(sol.optx[i])
            opty = []
            for i in range(sol.m):
                opty.append(sol.opty[i])
            res['fv'] = sol.fv
            res['dfv'] = sol.dfv
            res['optx'] = optx
            res['opty'] = opty
        return res


    if args.__len__() == 0:
        if beAineq and bebineq:
            beineq = 1
        else:
            beineq = 0

        if beAeq and bebeq:
            beeq = 1
        else:
            beeq = 0

        if not beobj or not(beineq or beeq):
            print('wrong input, please refer to help()\n')
            return

        if beineq:
            A1 = Aineq
            m1 = A1.shape[0]
            n1 = A1.shape[1]
            [I, J, K] = find(A1)
            size1 = I.shape[0]
            I1 = <int*>calloc(size1,sizeof(int))
            J1 = <int*>calloc(size1,sizeof(int))
            K1 = <double*>calloc(size1,sizeof(double))
            b1 = <double*>calloc(m1,sizeof(double))
            for i in range(m1):
                b1[i] = bineq[i]
            for i in range(size1):
                I1[i] = I[i]+1
                J1[i] = J[i]+1
                K1[i] = K[i]
        if beeq:
            A2 = Aeq
            m2 = A2.shape[0]
            n2 = A2.shape[1]
            [I, J, K] = find(A2)
            size2 = I.shape[0]
            I2 = <int*>calloc(size2,sizeof(int))
            J2 = <int*>calloc(size2,sizeof(int))
            K2 = <double*>calloc(size2,sizeof(double))
            b2 = <double*>calloc(m2,sizeof(double))
            for i in range(m2):
                b2[i] = beq[i]
            for i in range(size2):
                I2[i] = I[i]+1
                J2[i] = J[i]+1
                K2[i] = K[i]

        if n1 and n2 :
            if n1 != n2:
                print('''wrong dimention :
                         A1 %d * %d
                         A2 %d * %d
                      '''%(m1,n1,m2,n2))
                return
            n = n1
        if n1 and not n2:
            n = n1
        if n2 and not n1:
            n = n2
        #print('keywords ',n) #Danny
        c = <double*>calloc(n,sizeof(double))
        L = <double*>calloc(n,sizeof(double))
        U = <double*>calloc(n,sizeof(double))
        for i in range(n):
            c[i] = obj[i]
            L[i] = 0
            U[i] = coplinf
        if belb:
            for i in range(n):
                L[i] = lb[i]
        if beub:
            for i in range(n):
                U[i] = ub[i]


        sol = CopllpMtx_Spa(m1,m2,n,c,I1,J1,K1,size1,b1,I2,J2,K2,size2,b2,L, U, docross, prelevel,showiter,showtime)
        if sol:
            optx = []
            for i in range(sol.n):
                optx.append(sol.optx[i])
            opty = []
            for i in range(sol.m):
                opty.append(sol.opty[i])
            res['fv'] = sol.fv
            res['dfv'] = sol.dfv
            res['optx'] = optx
            res['opty'] = opty
        return res



def help():
    print(r'''
    There is only one function in this package ,"linprg()", and this function will return a dict object:
        dict{"fv"  : float(primal optimal value)  , 
             "dfv" : float(dual optimal value),
             "optx": list(primal optimal solution), 
             "opty": list(dual optimal solution)
            }


    #### Usage ###
    To solve a mps format file:
        result = linprg(mpsfilepath) or  linprg(path = mpsfilepath)


    To solve a problem in matrix(datatype: numpy.array/ nmupy.matrix/ scipy.matrix/ scipy.sparse.'sparsematrix' ):
        result = linprg(obj = c,Aineq = A1,bineq = b1,Aeq = A2,beq = b2,lb = L,ub = U)
        but
        if you have all these parameters, you don't need to use the keywords ,e.g.
            result = linprg(c,A1,b1,A2,b2,lb,ub)


    You can change four default parameters.
    default value: prelevel = 5 ,docross = 1, showiter = 1, showtime = 1,

    prelevel————the level of presolve
                0:no presolving is performed.
                1:dependent rows,null and fixed columns.
                2:singleton rows,forcing rows,doubleton rows,dominated rows.
                3:dominated columns.
                4:duplicate rows.
                5:duplicate columns.
    docross ----whether to do 'cross over'
                0 / False ---not
                1 / True  ---yes
    showiter----whether to show information of each iteration
                0 / False ---not
                1 / True  ---yes    
    showtime----whether to show time information
                0 / False ---not
                1 / True  ---yes   
    example:
    result = linprg(mpsfilepath,showiter =0)


	'''
          )

