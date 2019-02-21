#define _CRT_SECURE_NO_DEPRECATE
#include "copl.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

optsol* testMAT(char* filename){
	FILE *fin = fopen(filename, "r");
	if (!fin)printf("wrong input\n");
	int m1, m2, n, i, j;
	double *c, *b1, *b2, *L, *U, **A1, **A2;

	fscanf(fin, "%d %d %d\n", &m1, &m2, &n);

	c = (double*)calloc(n, sizeof(double));
	b1 = (double*)calloc(m1, sizeof(double));
	b2 = (double*)calloc(m2, sizeof(double));
	L = (double*)calloc(n, sizeof(double));
	U = (double*)calloc(n, sizeof(double));
	A1 = (double**)calloc(m1, sizeof(double*));
	A1[0] = (double*)calloc(n*m1, sizeof(double));
	for (i = 1; i < m1; i++)A1[i] = A1[i - 1] + n;
	A2 = (double**)calloc(m2, sizeof(double*));
	A2[0] = (double*)calloc(n*m2, sizeof(double));
	for (i = 1; i < m2; i++)A2[i] = A2[i - 1] + n;

	for (i = 0; i < n; i++) fscanf(fin, "%lf ", c + i);
	for (i = 0; i < m1; i++)
	{
		for (j = 0; j < n; j++) fscanf(fin, "%lf ", &A1[i][j]);
		fscanf(fin, "%lf\n", b1 + i);
	}
	for (i = 0; i < m2; i++)
	{
		for (j = 0; j < n; j++) fscanf(fin, "%lf ", &A2[i][j]);
		fscanf(fin, "%lf\n", b2 + i);
	}
	for (i = 0; i < n; i++) fscanf(fin, "%lf ", L + i);
	for (i = 0; i < n; i++) fscanf(fin, "%lf ", U + i);
	/*
	FILE* fout = fopen("C:/Danny/Files/In/OutMAT.txt", "w");
	if (!fout)printf("wrong output\n");
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
	*/
	fclose(fin);
	optsol *sol;
	sol = CopllpMtx(m1, m2, n,c, A1, b1, A2, b2, L, U,1,5,1,1);
	free(c); free(A1[0]); free(A1); free(A2[0]); free(A2); free(b1); free(b2); free(L); free(U);
	return sol;
}

optsol* testSPR(char* filename){

	FILE *fin = fopen(filename, "r");
	if (!fin)printf("wrong input\n");
	int i,m1, m2, size1,size2,n, *I1,*J1,*I2,*J2;
	double *c, *b1, *b2, *L, *U,*K1,*K2;

	fscanf(fin, "%d %d %d %d %d\n", &m1, &m2,&size1,&size2, &n);
	c = (double*)calloc(n, sizeof(double));
	b1 = (double*)calloc(m1, sizeof(double));
	b2 = (double*)calloc(m2, sizeof(double));
	L = (double*)calloc(n, sizeof(double));
	U = (double*)calloc(n, sizeof(double));
	I1 = (int*)calloc(size1, sizeof(int));
	J1 = (int*)calloc(size1, sizeof(int));
	K1 = (double*)calloc(size1, sizeof(double));
	I2 = (int*)calloc(size2, sizeof(int));
	J2 = (int*)calloc(size2, sizeof(int));
	K2 = (double*)calloc(size2, sizeof(double));

	for (i = 0; i < n; i++) fscanf(fin, "%lf ", c + i);
	for (i = 0; i < size1; i++) fscanf(fin, "%d ", I1+i);
	for (i = 0; i < size1; i++) fscanf(fin, "%d ", J1 + i);
	for (i = 0; i < size1; i++) fscanf(fin, "%lf ", K1 + i);
	for (i = 0; i < m1; i++) fscanf(fin, "%lf ", b1 + i);
	for (i = 0; i < size2; i++) fscanf(fin, "%d ", I2 + i);
	for (i = 0; i < size2; i++) fscanf(fin, "%d ", J2 + i);
	for (i = 0; i < size2; i++) fscanf(fin, "%lf ", K2 + i);
	for (i = 0; i < m2; i++) fscanf(fin, "%lf ", b2 + i);
	for (i = 0; i < n; i++){
		L[i] = 0;
		U[i] = COPL_INF;
	}
	while (fscanf(fin,"%d ", &i) != EOF){
		//printf("%d\n", i);
		fscanf(fin, "%lf %lf\n", L + i - 1, U + i - 1);
	}

	/*
	1
	for (i = 0; i < n; i++) fscanf(fin, "%lf ", L + i);
	for (i = 0; i < n; i++) fscanf(fin, "%lf ", U + i);
	2
	for (i = 0; i < n; i++) fscanf(fin, "%lf %lf\n",L+i, U + i);
	3
	for (i = 0; i < n; i++){
		L[i] = 0;
		U[i] = COPL_INF;
	}
	while (fscanf(fin, "%d",&i)!=EOF)
		fscanf(fin, "%lf %lf\n", L + i-1,U+i-1);
	*/

		
	/*out
	FILE* fout = fopen("C:/Danny/Files/In/OutSPR.txt", "w");
	if (!fout)printf("wrong output\n");
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
	*/
	fclose(fin);
	optsol *sol;
	sol = CopllpMtx_Spa(m1,m2,n,c, I1,J1,K1,size1,b1, I2,J2,K2,size2,b2, L, U,1,5,1,1);
	//sol = CopllpMtx_Spa(m1, 0, n, c, I1, J1, K1, size1, b1, 0, 0, 0, 0,0, L, U, 1, 5);
	//sol = CopllpMtx_Spa(0, m2, n, c, 0, 0, 0, 0, 0, I2, J2, K2, size2, b2, L, U, 1, 5);
	free(c); free(b1); free(b2); free(I1); free(J1); free(I2); free(J2); free(K1); free(K2);
	return sol;
}

int main(){
	if (0) {
		char    pname[][12] = {
			"25FV47",  "80BAU3B", "AFIRO",   "ADLITTLE","AGG",
			"AGG2",    "AGG3",    "BANDM",   "BEACONFD","BLEND",
			"BNL1",    "BNL2",    "BOEING1", "BOEING2", "BORE3D",
			"BRANDY",  "CAPRI",   "CYCLE",   "CZPROB",  "D2Q06C",
			"D6CUBE",  "DEGEN2",  "DEGEN3",  "DFL001",  "E226",
			"ETAMACRO",           "FINNIS",  "FIT1D",   "FIT1P"
			"FIT2D",   "FIT2P",   "FORPLAN", "GANGES",  "GFRD-PNC",
			"GREENBEA","GREENBEB","GROW15",  "GROW22",  "GROW7",
			"ISRAEL",  "KB2",     "LOTFI",   "MAROS",   "MAROS-R7",
			"NESM",    "PEROLD",  "PILOT",   "PILOT-JA","PILOT-WE",
			"PILOT4",  "PILOT87", "PILOTNOV", "QAP12",   "QAP15",
			"QAP8",               "SC105",    "SC205",   "SC50A",
			"SC50B",   "SCAGR25", "SCAGR7",  "SCFXM1",  "SCFXM2",
			"SCFXM3",  "SCORPION","SCRS8",   "SCSD1",   "SCSD6"
			"SCSD8",   "SCTAP1",  "SCTAP2",  "SCTAP3",  "SEBA",
			"SHARE1B", "SHARE2B", "SHELL",   "SHIP04L", "SHIP04S",
			"SHIP08L", "SHIP08S", "SHIP12L", "SHIP12S", "SIERRA",
			"STAIR",   "STANDATA","STANDGUB","STANDMPS","STOCFOR1",
			"STOCFOR2","STOCFOR3", "TRUSS",   "TUFF",    "VTP-BASE",
			"WOOD1P",  "WOODW",
		};//at most 100 problems
		//"FFFFF800", "RECIPELP"
		int pnum = 8;


		double tim[100], fv[100];
		memset(tim, 0, sizeof(tim));
		memset(fv, 0, sizeof(fv));
		clock_t t1 = clock();
		char path[] = "C:/Danny/Files/netlib/";
		char ftype[] = ".mps";
		char p[100];
		for (int i = 0; i < pnum; i++) {
			strcpy(p, path);
			strcat(p, pname[i]);
			strcat(p, ftype);
			printf("\n%d : %s\n", i + 1, pname[i]);
			//printf("%s\n", p);
			optsol *sol;
			sol = Copllpmps(p, 1, 5, 0, 0);
			if (sol) {
				fv[i] = sol->fv;
				tim[i] = sol->time;
				free(sol->optx); free(sol->opty); free(sol);
			}
		}
		//for (int i = 0; i < pnum; i++)printf("%d :%s, %f, %f\n", i, pname[i], tim[i], fv[i]);
		
		clock_t t2 = clock();
		printf("\n\nwhole time : %f\n\n",(t2-t1)*0.001);
		FILE* fout = fopen("C:/Users/15696/Documents/Python/PycharmProjects/testv36/Cresult.txt", "w");
		if (!fout)printf("no file output!\n");
		else {
			for (int i = 0; i < pnum; i++) {
				fprintf(fout,"%s,%f,%f\n",pname[i], tim[i], fv[i]);
			}
			fclose(fout);
		}
	}
	else {
		optsol *sol;
		sol = Copllpmps("C:/Danny/Files/netlib/AGG.mps", 1, 5, 0, 0);
		//sol = testMAT("C:/Danny/Files/In/InMAT.txt");
		//sol = testSPR("C:/Danny/Files/In/Remps.txt");
		//sol = testSPR("C:/Danny/Files/In/InSPR.txt");

		if (sol) {
			/*for (int i = 0; i < sol->n; i++){
			if (sol->optx[i] < 1.e-8 && sol->optx[i] > -1.e-8)continue;
			printf("%d %.5f\n", i + 1, sol->optx[i]);
			}*/
		}
	}
	system("pause");
	return 0;
}


