
#include"LPdefine.h"
#include <io.h>
#include "copl.h"
/* global variables */
FILE *fbin=NULL,
     *fout=NULL,
	 *fspc=NULL,
     *fstk=NULL,
     *fres=NULL;
	
char *nout=NULL,
     *nspc=NULL;

optmod *ot=NULL;
optpar *pr=NULL;

int ITER_SHOW = 1;
int TIME_SHOW = 1;
clock_t otim[8];
static const double PDGAP = 1.E-5;

double getrelagap(double d, double p) {
	if (d + p == 0)return d;
	return (d - p) * 2 / (d + p);
}
double getcoplinf(){return COPL_INF;}

optsol* CopllpMtx_Spa(int m1, int m2, int n, double* c,
	int* I1, int* J1, double* K1,int size1, double*b1,
	int* I2, int* J2, double* K2,int size2, double*b2,
	double*L, double*U, int docross, int prelevel, int showiter, int showtime)
{
	ITER_SHOW = showiter;
	int checkinput= 0;
	if (checkinput){
		int i;
		FILE* fout = fopen("D:/DannyFiles/In/OutSPR.txt", "w");
		if (!fout)printf("wrong output filename\n");
		fprintf(fout, "%d %d %d %d %d\n", m1, m2, size1, size2, n);
		for (i = 0; i < n; i++) fprintf(fout, "%f ", c[i]); fprintf(fout, "\n");
		for (i = 0; i < size1; i++) fprintf(fout, "%d ", I1[i]); fprintf(fout, "\n");
		for (i = 0; i < size1; i++) fprintf(fout, "%d ", J1[i]); fprintf(fout, "\n");
		for (i = 0; i < size1; i++) fprintf(fout, "%f ", K1[i]); fprintf(fout, "\n");
		for (i = 0; i < m1; i++) fprintf(fout, "%f ", b1[i]); fprintf(fout, "\n");
		for (i = 0; i < size2; i++) fprintf(fout, "%d ", I2[i]); fprintf(fout, "\n");
		for (i = 0; i < size2; i++) fprintf(fout, "%d ", J2[i]); fprintf(fout, "\n");
		for (i = 0; i < size2; i++) fprintf(fout, "%f ", K2[i]); fprintf(fout, "\n");
		for (i = 0; i < m2; i++) fprintf(fout, "%f ", b2[i]); fprintf(fout, "\n");
		for (i = 0; i < n; i++) fprintf(fout, "%g ", L[i]); fprintf(fout, "\n");
		for (i = 0; i < n; i++) fprintf(fout, "%g ", U[i]); fprintf(fout, "\n");
		fclose(fout);
		return 0;
	}

	optsol *sol = (optsol*)malloc(sizeof(optsol));

	int idproc;
	idproc = Coplinit(sol,docross,prelevel, showiter,showtime);
	if (!idproc)return 0;


	/////////////////////
	idproc = ReadMtx_Sparsedata(m1,m2,n, c, I1,J1,K1,size1,b1, I2,J2,K2,size2,b2,L,U);
	// I J K will be free in this function

	if (!idproc){
		return 0;
	}
	sol->n = ot->n;
	sol->m = ot->m;
	sol->nz = ot->nz;
	/////////////////////


	idproc = OptProc(otim, ot, pr);
	if (!idproc)return 0;

	Coplend(sol);
    if (getrelagap(sol->dfv,sol->fv) < PDGAP)return sol;
	else return 0;
}/*CopllpMtx_Spa*/

optsol* CopllpMtx(int m1, int m2, int n, double*c,
	double **A1, double*b1,
	double **A2, double*b2,
	double*L, double*U, int docross, int prelevel, int showiter, int showtime)
{
	int checkinput = 0;
	if (checkinput){
		int i,j;
		FILE* fout = fopen("D:/DannyFiles/In/OutMAT.txt", "w");

		if (!fout)printf("wrong output filename\n");
		for (i = 0; i < n; i++) fprintf(fout, "%f ", c[i]);
		fprintf(fout, "\n");
		for (i = 0; i < m1; i++) {
			for (j = 0; j < n; j++)
				fprintf(fout, "%f ", A1[i][j]);
			fprintf(fout, "%f\n", b1[i]);
		}
		for (i = 0; i < m2; i++) {
			for (j = 0; j < n; j++)
				fprintf(fout, "%f ", A2[i][j]);
			fprintf(fout, "%f\n", b2[i]);
		}
		for (i = 0; i < n; i++) fprintf(fout, "%g ", L[i]);
		fprintf(fout, "\n");
		for (i = 0; i < n; i++) fprintf(fout, "%g ", U[i]);
		fprintf(fout, "\n");

		fclose(fout);
		return 0;
	}

	optsol *sol = (optsol*)malloc(sizeof(optsol));

	int idproc;
	idproc = Coplinit(sol,docross,prelevel, showiter,showtime);
	if (!idproc)return 0;


	/////////////////////
	idproc = ReadMatrixdata(m1,m2, n, c, A1, b1, A2, b2, L, U);
	if (!idproc){
		printf("wrong input method\n");
		return 0;
	}
	sol->n = ot->n;
	sol->m = ot->m;
	sol->nz = ot->nz;
	/////////////////////

	idproc = OptProc(otim, ot, pr);
	if (!idproc)return 0;


	Coplend(sol);
	if (getrelagap(sol->dfv, sol->fv) < PDGAP)return sol;
	else return 0;
} /* CopllpMtx */

optsol* Copllpmps(char* nmps,int docross,int prelevel, int showiter, int showtime)
{  
	optsol *sol = (optsol*)malloc(sizeof(optsol));

	int idproc;
	idproc = Coplinit(sol,docross,prelevel,showiter,showtime);
	if (!idproc)return 0;


	//***********
	idproc = Readmpsdata(nmps);
	if (!idproc){
		printf("wrong input method\n");
		return 0;
	}
	//RecordData(ot,pr,"D:/DannyFiles/In/Remps.txt");
	sol->n = ot->n;
	sol->m = ot->m;
	sol->nz = ot->nz;
	//***********


    idproc=OptProc(otim,ot,pr);
	if (!idproc)return 0;
        
	Coplend(sol);
	if (getrelagap(sol->dfv, sol->fv) < PDGAP)return sol;
	else return 0;
} /* Copllpmps */


void Coplend(optsol* sol)
{

	sol->fv = ot->pobj;
	sol->dfv = ot->dobj;
    
	cFree(&nout);
	ShutDown();

	SetTime(otim, ELAPS);
	PrintEnd(otim);
    printf(" Columns: %d\n Rows: %d\n Nozeros: %d\n", sol->n,sol->m,sol->nz);
	if (sol->m * sol->n) {
		printf(" Ratial: %f\n\n", sol->nz / (double)(sol->m * sol->n));
	}
	sol->time= (double)(otim[ELAPS] - otim[START])*0.001;
	if (getrelagap(sol->dfv, sol->fv) < PDGAP)printf(" Optimal objective value : %.4f\n", sol->fv);

	FileClose(&fstk);
	FileClose(&fbin);

	solpt pt = { 0 };
	Reportsol(&pt);
	int h;
	sol->optx = dAlloc(pt.n0, "primal optimal solution");
	for (h = 0; h<pt.n0; h++) sol->optx[h] = pt.x0[h];
	sol->opty = dAlloc(pt.m0, "dual optimal solution");
	for (h = 0; h<pt.m0; h++) sol->opty[h] = pt.y0[h];
	RepShutDown(&pt);

	if (!OUT_FILE)remove(COPLFILE_OUT);
	if(!RPT_FILE)remove(COPLFILE_RPT);
	remove(COPLFILE_BIN);
	remove(COPLFILE_SOL);
	remove(COPLFILE_STK);
}/*Coplend*/



int Coplinit(optsol* sol,int docross,int prelevel, int showiter, int showtime)
{
	ITER_SHOW = showiter;
	TIME_SHOW = showtime;
	sol->fv = -COPL_INF;
	sol->dfv = COPL_INF;
	sol->optx = NULL;
	sol->opty = NULL;

	int     idproc = 0;
	
	pr = (optpar*)malloc(sizeof(optpar)); //used in other files
	ot = (optmod*)malloc(sizeof(optmod));
	memset(pr, 0, sizeof(optpar));
	memset(ot, 0, sizeof(optmod));

	SetTime(otim, START);
	PrintHead();

	//	 out file
	if (OUT_FILE){
		nout = cAlloc(LineSize, "for nout in main");
		sprintf(nout, SFMT, COPLFILE_OUT);
		if (!(idproc = FprintHead())) return false;
	}

	// parameter
	ReadParms(pr,ot); //use COPLLP.spc or Default value
	pr->cross = docross;
	pr->prlev = prelevel;
	return true;
}/* Coplinit*/

typedef struct{
	int i;
	int j;
	double k;
}NODE;

int comp(const void * aa, const void* bb){ // column priority
	NODE* a = (NODE*)aa; 
	NODE* b = (NODE*)bb;
	if (a->j == b->j){
		return a->i - b->i;
	}
	return a->j - b->j;
}




// read different types of data 
int Readmpsdata(char* nmps){

	int idproc;
	char ss[LineSize];

	/*
	* input procedure
	*/
	FILE* fmps;
	fmps = fopen(nmps, "r");
	if (!fmps) {
		sprintf(ss, SFMT ".mps", nmps);
		fmps = fopen(ss, "r");
		if (!fmps) {
			ErrorProc(NOT_SCHFIL, nmps);
			return false;
		}
		else strcpy(nmps, ss);
	}

	if (fseek(fmps, 0L, SEEK_END)) {
		ErrorProc(NULL_FILE, nmps);
		return false;
	}

	FileClose(&fmps);

	CreateStack();
	idproc = ReadMpsf(pr, ot, nmps);
	SetTime(otim, DATAIN);
	if (!idproc) return false;

	return true;
}/*Readmpsdata*/

int ReadMtx_Sparsedata(int m1, int m2, int n, double* c,
	int* I1, int* J1, double* K1, int size1, double*b1,
	int* I2, int* J2, double* K2, int size2, double*b2,
	double*l, double*u)
{
	int i, j, m, size, k, *colsub, mini, maxi;
	double  *colval;
	char ss[30];
	NODE* nodes;


	//check data: 

	if (size1 > m1*n || size2 > m2*n){
		printf("wrong data size1 %d, size2 %d, m1*n %d, m2*n %d\n", size1 ,m1*n ,size2, m2*n);
		return false; 
	}
	mini = 1;
	maxi = 0;
	for (i = 0; i < size1; i++){
		mini = min(I1[i], mini);
		maxi = max(I1[i], maxi);
	}
	if (mini < 1 || maxi>m1){
		printf("wrong data A1: m1 %d,mini %d,maxi %d\n",m1, mini,maxi);
		return false;
	}
	mini = 1;
	maxi = 0;
	for (i = 1; i < size1; i++){
		mini = min(J1[i], mini);
		maxi = max(J1[i], maxi);
	}
	if (mini < 1 || maxi>n){
		printf("wrong data A1: n %d, minj %d,maxj %d\n",n, mini, maxi);
		return false;
	}

	mini = 1;
	maxi = 0;
	for (i = 1; i < size2; i++){
		mini = min(I2[i], mini);
		maxi = max(I2[i], maxi);
	}
	if (mini < 1 || maxi>m2){
		printf("wrong data A2: m2 %d,mini %d,maxi %d\n", m2, mini, maxi);
		return false;
	}
	mini = 1;
	maxi = 0;
	for (i = 1; i < size2; i++){
		mini = min(J2[i], mini);
		maxi = max(J2[i], maxi);
	}
	if (mini < 1 || maxi>n){
		printf("wrong data A2: n %d, minj %d,maxj %d\n", n, mini, maxi);
		return false;
	}




	m = m1 + m2;
	size = size1 + size2;


	k = true;
	if (n > pr->mcol) {
		char ss[80];
		sprintf(ss, "number of columns: %d>%d.", n, pr->mcol);
		ErrorProc(EXC_COLLIM, ss);
		k = false;
	}
	if (size > pr->melm) {
		char ss[80];
		sprintf(ss, "number of nzero elements: %d>%d.", size, pr->melm);
		ErrorProc(EXC_NNZLIM, ss);
		k = false;
	}
	if (!k) return false;

	CreateStack(); //!!!!!!!!!!!!!

	nodes = (NODE*)calloc(size, sizeof(NODE));
	for (i = 0; i < size1; i++){
		if (fabs(K1[i]) < pr->aijtol){
			size -= 1;
			continue;
		}
		nodes[i].i = I1[i];
		nodes[i].j = J1[i];
		nodes[i].k = K1[i];
		//printf("%d %d %f\n", I1[i], J1[i], K1[i]);
	}
	size1 = i;
	for (i = 0; i < size2; i++){
		if (fabs(K2[i]) < pr->aijtol){
			size -= 1;
			continue;
		}
		nodes[i + size1].i = I2[i]+m1;
		nodes[i + size1].j = J2[i];
		nodes[i + size1].k = K2[i];
		//printf("%d %d %f\n", I2[i]+m1, J2[i], K2[i]);
	}
	//iFree(&I1); iFree(&I2); iFree(&J1); iFree(&J2); dFree(&K1); dFree(&K2);

	qsort(nodes, size, sizeof(NODE), comp);
	//for (i = 0; i < size; i++)printf("%2d ", nodes[i].i); printf("\n");
	//for (i = 0; i < size; i++)printf("%2d ", nodes[i].j); printf("\n");

	////////// !
	ot->m = m; ot->n = n; ot->cnamesz = n; ot->nz = size;
	ot->nsk = ot->ineq = m1;

	BndAlloc(ot); //!!!!!!!!!!!!!

	ot->prbname = cAllocCopy("Matrix Data - no name", "for ot->prbname in ReadSection");
	
	//row
	ot->rowtype = cAlloc(m+1, "for ot->rowtype in ReadSection");
	ot->rowname = cPtAlloc(m+1, "for ot->rowname in ReadSection");
	ot->objname = cAllocCopy("Object", "objname in ReadSection");
	for (i = 0; i < m; i++){
		sprintf(ss, "row%d", i+1);
		ot->rowname[i] = cAllocCopy(ss, "for ot->rowname in ReadSection");
		ot->rnamesz++;
	}
	for (i = 0; i < m1; i++)ot->rowtype[i] = 'L';
	for (i = m1; i < m; i++)ot->rowtype[i] = 'E';

	//column
	//column
	ot->imem = iAlloc(pr->melm + pr->mcol + 1,
		"for imem in ReadSection");
	ot->rmem = dAlloc(pr->melm + pr->mcol,
		"for rmem in ReadSection");
	ot->colname = cPtAlloc(pr->mcol,
		"for ot->colname in ReadSection");

	colsub = ot->imem + pr->mcol + 1;
	colval = ot->rmem + pr->mcol;
	j= 0;
	for (i = 1; i<=n; i++){
		ot->imem[i - 1] = j;
		sprintf(ss, "col%d", i);
		ot->rmem[i - 1] = fabs(c[i - 1])<pr->aijtol ? 0 : c[i - 1];
		ot->colname[i-1] = cAllocCopy(ss,"ot->colmane in ReadSection");
		while (j<size && nodes[j].j <= i){
			*colval = nodes[j].k;
			*colsub = nodes[j].i-1;
			colval++;
			colsub++;
			j++;
		}
	}
	ot->imem[n] = size;
	
//	for (i = 0; i <= n; i++)printf("%d :%d\n", i,ot->imem[i]);

	//rhs
	pr->rhsset = cAllocCopy("No_name","for par->rhsset in ReadSection");
	for (i = 0; i < m1; i++)ot->b[i] = fabs(b1[i]) < pr->aijtol ? 0 : b1[i];
	for (i = 0; i < m2; i++)ot->b[i+m1] = fabs(b2[i]) < pr->aijtol ? 0 : b2[i];
	//range
	for (i = 0; i<m; i++) ot->r[i] = ot->b[i];

	//bounds
	for (i = 0; i<n; i++) {
		ot->l[i] = l[i];
		ot->u[i] = u[i];
	}
	
	for (i = 0; i<ot->n; i++) {
		if (ot->u[i] > pr->bplus&&
			ot->l[i] < -pr->bplus)
			ot->nfr++;
		if (ot->u[i] == ot->l[i])
			ot->nfx++;
		if (ot->u[i] <= pr->bplus)
			ot->nub++;
		if (ot->l[i] >= -pr->bplus)
			ot->nlb++;
	}

	free(nodes);

	char *nmps = "";
	RecNames(nmps); //!!!!!!!!!!!!!
	cPtFree(&ot->rowname, ot->rnamesz);
	cPtFree(&ot->colname, ot->cnamesz);

	SetTime(otim, DATAIN);
	return true;
}/*ReadMtx_Sparsedata*/

int ReadMatrixdata(int m1, int m2, int n, double*c,
	double **A1, double*b1,
	double **A2, double*b2,
	double*l, double*u)
{
	int i, j, m, size, k, *colsub;
	double *colval;
	char ss[30];

	CreateStack(); //!!!!!!!!!!!!!

	m = m1 + m2;
	size = 0;
	for (i = 0; i < m1; i++){
		for (j = 0; j < n; j++){
			if (fabs(A1[i][j]) < pr->aijtol) A1[i][j] = 0;
			else size++;
		}
	}
	for (i = 0; i < m2; i++){
		for (j = 0; j < n; j++){
			if (fabs(A2[i][j]) < pr->aijtol) A2[i][j] = 0;
			else size++;
		}
	}

	k = true;
	if (n > pr->mcol) {
		char ss[80];
		sprintf(ss, "number of columns: %d>%d.",
			ot->n, pr->mcol);
		ErrorProc(EXC_COLLIM, ss);
		k = false;
	}
	if (size > pr->melm) {
		char ss[80];
		sprintf(ss, "number of columns: %d>%d.",
			ot->nz, pr->melm);
		ErrorProc(EXC_NNZLIM, ss);
		k = false;
	}
	if (!k) return false;


	////////// !
	ot->m = m; ot->n = n; ot->cnamesz = n;
	ot->nsk =  ot->ineq = m1;

	BndAlloc(ot); //!!!!!!!!!!!!!

	ot->prbname = cAllocCopy("Matrix Data - no name", "for ot->prbname in ReadSection");

	//row
	ot->rowtype = cAlloc(pr->mcol + 1, "for ot->rowtype in ReadSection");
	ot->rowname = cPtAlloc(m + 1, "for ot->rowname in ReadSection");
	ot->objname = cAllocCopy("Object", "objname in ReadSection");
	for (i = 0; i < m; i++){
		sprintf(ss, "row%d", i + 1);
		ot->rowname[i] = cAllocCopy(ss, "for ot->rowname in ReadSection");
		ot->rnamesz++;
	}
	for (i = 0; i < m1; i++)ot->rowtype[i] = 'L';
	for (i = m1; i < m; i++)ot->rowtype[i] = 'E';

	//column
	ot->imem = iAlloc(pr->melm + pr->mcol + 1,
		"for imem in ReadSection");
	ot->rmem = dAlloc(pr->melm + pr->mcol,
		"for rmem in ReadSection");
	ot->colname = cPtAlloc(pr->mcol,
		"for ot->colname in ReadSection");

	colsub = ot->imem + pr->mcol + 1;
	colval = ot->rmem + pr->mcol;
	ot->imem[0] = 0;
	for (j = 0; j < n; j++){
		sprintf(ss, "col%d", j + 1);
		ot->rmem[j] = fabs(c[j]) < pr->aijtol ? 0 : c[j];
		ot->colname[j] = cAllocCopy(ss, "ot->colmane in ReadSection");
		for (i = 0; i< m1; i++){
			if (A1[i][j]){
				*colval = A1[i][j];
				*colsub = i;
				colval++;
				colsub++;
				ot->nz++;
			}
		}
		for (i = 0; i< m2; i++){
			if (A2[i][j]){
				*colval = A2[i][j];
				*colsub = i+m1;
				colval++;
				colsub++;
				ot->nz++;
			}
		}
		ot->imem[j+1] = ot->nz;
	}



	//rhs
	pr->rhsset = cAllocCopy("No_name", "for par->rhsset in ReadSection");
	for (i = 0; i < m1; i++)ot->b[i] = fabs(b1[i]) < pr->aijtol ? 0 : b1[i];
	for (i = 0; i < m2; i++)ot->b[i + m1] = fabs(b2[i]) < pr->aijtol ? 0 : b2[i];
	//range
	for (i = 0; i < m; i++) ot->r[i] = ot->b[i];

	//bounds
	for (i = 0; i < n; i++) {
		ot->l[i] = l[i];
		ot->u[i] = u[i];
	}
	
	for (i = 0; i<ot->n; i++) {
		if (ot->u[i] > pr->bplus&& ot->l[i] < -pr->bplus)
			ot->nfr++;
		if (ot->u[i] == ot->l[i])
			ot->nfx++;
		if (ot->u[i] <= pr->bplus)
			ot->nub++;
		if (ot->l[i] >= -pr->bplus)
			ot->nlb++;
	}	


	char *nmps = "";
	RecNames(nmps);
	cPtFree(&ot->rowname, ot->rnamesz);
	cPtFree(&ot->colname, ot->cnamesz);

	SetTime(otim, DATAIN);
	return true;
}/*ReadMatrixdata*/



// turn optmod and optpar to sparse matrix formulation
void RecordData(optmod* opt, optpar* par, char * filename)
{
	FILE* fmpr = fopen(filename, "w");
	int i, j,k, m1, m2,size1, size2, n, *I1, *J1, *I2, *J2, size, m, *sub,s1,s2;
	double  *b1, *b2, *K1, *K2;
	char type;
	m = ot->m;
	n = ot->n;
	m1 = m2 = 0;
	size1 = size2 = 0;
	for (i = 0; i < m; i++)
	{
		type = ot->rowtype[i];
		if (type == 'E')m2 += 1;
		else if (type == 'R')m1 += 1;
		else m1 += 1;
	}
	size = ot->nz ;
	for (i = pr->mcol + 1; i < pr->mcol + size + 1; i++)
	{
		type = ot->rowtype[ot->imem[i]];
		if (type == 'E')size2 += 1;
		else if (type == 'R')size1 += 2;
		else size1 += 1;
	}
	
	
	b1 = (double*)calloc(m1, sizeof(double));
	b2 = (double*)calloc(m2, sizeof(double));
	I1 = (int*)calloc(size1, sizeof(int));
	J1 = (int*)calloc(size1, sizeof(int));
	K1 = (double*)calloc(size1, sizeof(double));
	I2 = (int*)calloc(size2, sizeof(int));
	J2 = (int*)calloc(size2, sizeof(int));
	K2 = (double*)calloc(size2, sizeof(double));

	sub = (int*)calloc(m, sizeof(int));

	for (i = 0, j = 0,k=0; i < m; i++){
		type = ot->rowtype[i];
		if ( type== 'E') {
			b2[j++] = ot->b[i];
			sub[i] = j;
		}
		else if (type == 'L'){
			b1[k++] = ot->b[i];
			sub[i] = k;
		}
		else if (type == 'G'){
			b1[k++] = -ot->b[i];
			sub[i] = k;
		}
		else{
			b1[k++] = ot->b[i];
			sub[i] = k;
			b1[k++] = -ot->r[i];
		}
	}


	for (j = s2 = s1 = 0; j < n; j++){
		for (k = ot->imem[j]; k < ot->imem[j + 1]; k++){
			i = ot->imem[pr->mcol + 1 + k];
			type = ot->rowtype[i];
			if (type == 'E') {
				I2[s2] = sub[i];
				J2[s2] = j + 1;
				K2[s2++] = ot->rmem[pr->mcol + k];
			}
			else if (type == 'L'){
				I1[s1] = sub[i];
				J1[s1] = j + 1;
				K1[s1++] = ot->rmem[pr->mcol + k];
			}
			else if (type == 'G'){
				I1[s1] = sub[i];
				J1[s1] = j + 1;
				K1[s1++] = -ot->rmem[pr->mcol + k];
			}
			else{
				I1[s1] = sub[i];
				J1[s1] = j + 1;
				K1[s1++] = ot->rmem[pr->mcol + k];
				I1[s1] = sub[i]+1;
				J1[s1] = j + 1;
				K1[s1++] = -ot->rmem[pr->mcol + k];
			}

		}
	}

	fprintf(fmpr, "%d %d %d %d %d\n", m1, m2, size1, size2, n);
	for (i = 0; i < n; i++) fprintf(fmpr, "%.5f ", ot->rmem[i]); fprintf(fmpr, "\n");
	for (i = 0; i < size1; i++) fprintf(fmpr, "%d ", I1[i]); fprintf(fmpr, "\n");
	for (i = 0; i < size1; i++) fprintf(fmpr, "%d ", J1[i]); fprintf(fmpr, "\n");
	for (i = 0; i < size1; i++) fprintf(fmpr, "%.5f ", K1[i]); fprintf(fmpr, "\n");
	for (i = 0; i < m1; i++) fprintf(fmpr, "%.5f ", b1[i]); fprintf(fmpr, "\n");
	for (i = 0; i < size2; i++) fprintf(fmpr, "%d ", I2[i]); fprintf(fmpr, "\n");
	for (i = 0; i < size2; i++) fprintf(fmpr, "%d ", J2[i]); fprintf(fmpr, "\n");
	for (i = 0; i < size2; i++) fprintf(fmpr, "%.5f ", K2[i]); fprintf(fmpr, "\n");
	for (i = 0; i < m2; i++) fprintf(fmpr, "%.5f ", b2[i]); fprintf(fmpr, "\n");
	for (i = 0; i < n; i++){
		if (fabs(ot->l[i]) <= pr->aijtol && ot->u[i] >= pr->bplus) continue;
		fprintf(fmpr, "%d %g %g\n", i + 1, ot->l[i], ot->u[i]);
	}
	
	/*
	for (i = 0; i < n; i++) fprintf(fmpr, "%.5f ", ot->l[i]); fprintf(fmpr, "\n");
	for (i = 0; i < n; i++) fprintf(fmpr, "%.5f ", ot->u[i]); fprintf(fmpr, "\n");

	for (i = 0; i < n; i++) fprintf(fmpr, "%.5f %.5f\n", ot->l[i],ot->u[i]);

	for (i = 0; i < n; i++){
	if (fabs(ot->l[i]) <= pr->aijtol && ot->u[i] >= pr->bplus) continue;
	fprintf(fmpr, "%d %g %g\n", i + 1, ot->l[i], ot->u[i]);
	}
	*/
	
	fclose(fmpr);
	dFree(&b1); dFree(&b2); iFree(&I1); iFree(&J1); dFree(&K1); iFree(&I2); iFree(&J2); dFree(&K2);
}