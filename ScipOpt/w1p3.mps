* SCIP STATISTICS
*   Problem name     : w1p1.lp
*   Variables        : 7 (2 binary, 2 integer, 0 implicit integer, 3 continuous)
*   Constraints      : 4
*   Obj. scale       : 1
*   Obj. offset      : 0
NAME          w1p1.lp
OBJSENSE
  MIN
ROWS
 N  Obj 
 L  c1 
 G  c2 
 E  c3 
 E  c4 
COLUMNS
    x         Obj                             -3  c4                               1 
    y         c4                             0.5  Obj                            4.5 
    INTSTART  'MARKER'                            'INTORG'                           
    z(1)      Obj                             -2 
    INTEND    'MARKER'                            'INTEND'                           
    f         Obj                              1  c3                               2 
    INTSTART  'MARKER'                            'INTORG'                           
    g(1,1)    c3                              -1  Obj                              0 
    g(1,1)    c1                              -1  c2                               3 
    g(1,2)    Obj                              0  c1                               1 
    g(1,2)    c2                              -7 
    z(2)      Obj                              0  c2                               1 
    INTEND    'MARKER'                            'INTEND'                           
RHS
    RHS       c1                               5  c2                             -10 
    RHS       c3                               6  c4                            -4.6 
BOUNDS
 BV Bound     z(1)                               
 BV Bound     z(2)                               
 FR Bound     g(1,1)                             
 PL Bound     g(1,2)                             
 PL Bound     y                                  
 FR Bound     x                                  
 PL Bound     f                                  
ENDATA