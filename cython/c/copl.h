
#ifndef _COPL_
#define _COPL_
//be included by LPconst.h
#define COPL_INF  1.E30
#define DEFAULT_PAR_LOWER 0.0
#define DEFAULT_PAR_UPPER COPL_INF
#define DEFAULT_PAR_MAX_COLSZ 100000
#define DEFAULT_PAR_MAX_ELMSZ 500000
#define DEFAULT_PAR_MAX_ITER 500
#define DEFAULT_PAR_MAX_CACHESZ 256 //Kilobytes
#define DEFAULT_PAR_PRLEV 5
#define DEFAULT_PAR_PRLOP 10
#define DEFAULT_PAR_CROSS 1
#define DEFAULT_PAR_X_TOL 1.0E-13
#define OUT_FILE		  0		//whether to create a information output file
#define RPT_FILE		  0     //whether to create a report file
#define INFM_PRE          0		//whether to print presolve information
#define INFM_FMD          0		//whether to print final model information
#define INFM_CRU          0		//whether to print crush information
#define INFM_MPS          0     //whether to print mps file information
#define INFM_CRS          0     //whether to print cross information
#define INFM_RPT		  0		//whether to print report information


double getcoplinf();

typedef struct {
	int n;
	int m;
	int nz;
	double time;
	double fv;
	double dfv;
	double *optx;
	double *opty;
}optsol;

optsol* Copllpmps(char* nmps, int docross, int prelevel,int showiter, int showtime);


/*
		Model:
min			c'*x
subject to:
A1*x<= b1
A2*x = b2;
l<= x <= u

default range : 0 <= xi <= INF

Attention: if you just give an variable a negative upper bound , then it will be infeasible. 

*/

optsol *CopllpMtx_Spa(int m1, int m2, int n, double* c,
				  int* I1, int* J1, double* K1,int size1,double*b1,
				  int* I2, int* J2, double* K2,int size2,double*b2,
				  double*L, double*U, int docross, int prelevel, int showiter, int showtime);

optsol* CopllpMtx(int m1, int m2, int n, double*c,
				double **A1, double*b1,
				double **A2, double*b2,
				double*L, double*U, int docross, int prelevel, int showiter, int showtime);


#endif