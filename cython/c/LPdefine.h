#define _CRT_SECURE_NO_DEPRECATE
#ifndef _LPDEFINE_
#define _LPDEFINE_

#include "LPconst.h"

typedef struct {
    int mcol; //max column size
    int melm;  //max element size
    
    int iterlmt;
    int cachesz;
    
    int save;
    int prlev; //presolve levels
    int prlop; //presolve loops 
    int cross;
    
    int bemin;
    int idden;
    
    char *rhsset;
    char *rngset;
    char *bndset;
    char *objname;
    
    double lower; //default lower bound
    double upper;
    
    double bplus; //compared to decide whether a variable is free
    double aijtol;   
    double tolpiv;
    
    double tolgap;
    double tolp;
    double told;
    
    double tolx;
    double tols;
    
    double tolmu;
    double tolinf;
    double pcgtol;

    double Gamma;
    double beta;
  } optpar;

typedef struct list *plst;

typedef struct list {
    int   addr;
    char  *key;
    plst  next;
  } hashlst;

typedef struct {
    int   lssz;
    plst* list;
  } hashtab;
  
typedef struct {
    double low;
    double upp;
    double rhs;
    int    nn0;
    int    *ja;
    double *an;
  } optrow;
  
typedef struct {
    int    nn0;
    int    *ja;
    double *an;
  } array;

typedef struct {
    int    mnrs;
    int    nrow;
    int    mems;
    array  *ia;
  } matrix;

typedef struct {
    int    maxr;
    int    nrow;
    int    maxn;
    int    *iaat;
    int    *naat;
    int    *jaat;
    
    int    *perm;
    int    *invp;
    
    int    nsnd;
    int    *isnd;
    
    int    ndnd;
    int    ndns;
    int    *idn;
    int    *jdn;
        
    int    *dmj;
    int    plmt;
    int    dnsp;
    
    int    nu;
    int    nju;
    int    *iju;
    int    *iu;
    int    *jun;
    int    *ju;
    double *ud;
    double *un;
  } chol;
  
typedef struct {
    
    int ista;    //process status
    int solsta;  //solve status
    int infsta;  //infeasible status
    
    int m;
    int n;
    int nz; //#element
    
	//columns: four types variables
    int nlb;
    int nub;
    int nfr;
    int nfx;
    
	//equations
    int nsk; //ineq+nrg
    int nrg; // #range equality
    int ineq;// #inequality
	
	//bound cards
    int nlow;
    int nupp;
    int nfix;
    int nfre;
    int nbmi; //minus infinity
    int nbpl; //plus infinity
    
    int rnamesz;
    int cnamesz;
    
    hashtab *rowtab;
    hashtab *coltab;
    
    optrow *row;
    optrow *col;
    
    char   *mpscard; //temporary record for card
    char   *prbname;
    char   *objname;
    char   *rowtype; //E N G L R(range)
    char   **rowname;
    char   **colname;
    int    *csk;
    
    int    *imem;
    double *rmem;
        
    double *b; //rhs 
    double *c; 
    double *l;
    double *u;
    double *r; //rhs changed by range   r<= A*x <= b
    double obj;
    int    *bid; //initialize in FinalModel 

    char *rflg;
    char *cflg;
    
    int  prtst;
    int  nrld;
    int  nrnul;
    int  nrsg;
    int  nrdb;
    int  nrfc;
    int  nrdm;
    int  nrdu;
    int  ncnul;
    int  ncfx;
    int  ncdm;
    int  ncdu;
    
    double *rlb;
    double *rub;
    double *clb;
    double *cub;
    
    int items;
    int bytes;
    
    int iter; //#iteration
    
    double pobj; //primal objective
    double dobj; //dual objective
    double rgap; //primal dual gap
    double mu; //primal dual barrier
    
    double inf0;
    double rho;
    double mu0;
    double tau0;
    double kap0;
    double cx;
    double by;
    double rg;
    double rdf;
    
    double dfdt;
    double dfnm;
    
    double rddt;
    double ddtu;
    double rdnm;
    double rrdnm; //dual infeasibility or constraint residual
    
    double rpdt;
    double pdtu;
    double pnmu;
    double rpnm;
    double rrpnm; //primal infeasibility or constraint residual
    
    double rgdt;
    double smdt;
    double cgap;
    
    double infe;
    double nall;
     
    double *x;
    double *y;
    double *z;
    double *xu;
    double *yu;
    double *zu;
    double tau;
    double kap;
    double *xf;
    
    matrix *a;
    matrix *at; //column prior
    chol   *cl;
    
    int    nden; //n dense columns
    int    *cid;
    matrix *dac;
    matrix *sac;
    double **ld;
    int    *lperm;
    int    *linvp;
    double *pcgbf;
  } optmod;



  typedef struct {
	  int    ncol;
	  int    non0;
	  array  *cols;
  } cmatrix;

  typedef struct {
	  char   sname[256];
	  char   *rp;

	  int    resp;
	  int    m;
	  int    n;
	  int    m0;
	  int    n0;
	  int    non0;
	  int    *subj;
	  int    *subi;

	  int    cdmn;
	  int    cdup;
	  int    cfix;
	  int    cnul;
	  int    lbnd;
	  int    mins;
	  int    rdbl;
	  int    rdmn;
	  int    rdup;
	  int    rfrc;
	  int    rnul;
	  int    rsng;

	  double *x;
	  double *y;
	  double *z;

	  double *x0;
	  double *y0;
	  double *z0;

	  double *r;
	  double *b;
	  double *c;
	  double *l;
	  double *u;

	  double *ai;
	  double *aj;

	  cmatrix *a;
  } solpt;


extern FILE *fbin,
            *fout,
            *fspc,
            *fstk,
            *fres,
			*fsol, 
			*frpt;

extern char *nout,
            *nspc;

extern optmod *ot;
extern optpar *pr;
extern int ITER_SHOW;
extern int TIME_SHOW;
#include "LPfunct.h"

#endif