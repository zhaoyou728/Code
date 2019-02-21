#include "LPdefine.h"

FILE *fstk,*fbin,
     *fsol,*frpt;

void RepPrintHead(void)
{
  printf("\n ===============================\n");
  printf(" POST SOLVER ( C O P L )\n");
  printf(" ===============================\n\n");
} /* RepPrintHead */

int LeftDots(char *ss,int len)
{
  char sz[60];
  int  i,j,k;
  
  k=strlen(ss);
  j=len-k;
  
  strcpy(sz,ss);
  for (i=0; i<j; i++)
    ss[i]='.';
  for (i=j; i<len; i++)
    ss[i]=sz[i-j];
  ss[len]='\0';
  return true;
}


double TimeInSec(clock_t head,
                 clock_t rear)
{
  double tscal;
  
#ifdef HPMACHINE
  tscal=0.01;
#else
  tscal=0.001;
#endif

  return ((double)(rear-head)*tscal);
} /* TimeInSec */


cmatrix *mAlloc(int  m,
               int  nz)
{
  cmatrix *r;
  
  r=(cmatrix*)calloc(1,sizeof(cmatrix));
  if (!r) {
    exit(0);
  }
  
  if (m) {
    r->cols=(array*)calloc(m,sizeof(array));
    if (!r) {
      exit(0);
    }
    
    if (nz) {
		r->cols->ja = iAlloc(nz, "no");
		r->cols->an = dAlloc(nz, "no");
    }
  }
  r->ncol=m;
  r->non0=nz;
  return r;
} /* MtxAlloc */

void mFree(cmatrix **a)
{
  cmatrix *r=*a;
  
  if (r) {
    if (r->cols) {
      iFree(&r->cols->ja);
      dFree(&r->cols->an);
      free(r->cols);
      r->cols=NULL;
    }
    
    r->ncol=0;
    r->non0=0;
    free(r);
  }
  *a=NULL;
} /* MtxFree */

static void RepTimesv(int    t,
                    int    n,
                    cmatrix *a,
                    double *x,
                    double *y)
{
  int    j,k;
  array  *aj;
  
  if (t) {  /* y=y+A'*x */
    for (j=0; j<n; j++) {
      aj=a->cols+j;
      for (k=0; k<aj->nn0; k++)
        y[j]+=aj->an[k]*x[aj->ja[k]];
    }
  }
  
  else { /* y=y+A*x */
    for (j=0; j<n; j++) {
      aj=a->cols+j;
      for (k=0; k<aj->nn0; k++)
        y[aj->ja[k]]+=aj->an[k]*x[j];
    }
  }
} /* RepTimesv */

static void GetActv(solpt *pt)
{
  int i,j;
  
  for (i=0; i<pt->m0; i++)
    pt->aj[i]=0.0;
  
  RepTimesv(false,pt->n0,pt->a,pt->x0,pt->aj);
  
  for (j=0; j<pt->n0; j++)
    pt->ai[j]=-pt->c[j];
  
  RepTimesv(true,pt->n0,pt->a,pt->y0,pt->ai);
} /* GetActv */

static OutRept(solpt *pt)
{
	char   ss[128];
	FILE   *fp;
	/*if (*(pt->sname))
	sprintf(ss,"%s.rpt",pt->sname);
	else
	sprintf(ss,"coplfile.rpt");
	*/
	sprintf(ss, "coplfile.rpt");
	fp = fopen(ss, "w");
	if (!fp) exit(0);

	if (1){
		int    h, i, j, k;
		double bplus = 0.999e30;
		char   skey[][12] = {
			"unsolved", "optimal",
			"infeasible", "unbounded",
			"difficulty" };

		LeftDots(ss, 36);
		if(INFM_RPT)printf(" report file name %s\n\n", ss);

		fprintf(fp,"INPUT FILE NAME  : %10s\n",pt->sname);
		fprintf(fp,"NUMBER OF ROWS   : %10d\n",pt->m0);
		fprintf(fp,"NUMBER OF COLUMNS: %10d\n",pt->n0);
		fprintf(fp,"SOLUTION STATUS  : %10s\n\n",skey[pt->resp+1]);

		fprintf(fp,"ROWS\n");
		fprintf(fp,"----\n");

		fprintf(fp," %-6s %-8s %4s "tfmt" "tfmt" "tfmt" "tfmt"\n",
		"order","name","type","lower","active",
		"upper","dual value");

		h=0;
		for (i=0; i<pt->m0; i++) {

		k=iGet(fbin);
		fread(ss,1,k,fbin);
		ss[k]='\0';

		if (pt->rp[i]=='E') {
		sprintf(ss,"%-8s  EQ  "dfmt" "dfmt" "dfmt" "dfmt,
		ss,pt->r[i],pt->aj[i],pt->b[i],pt->y0[i]);
		}
		else {
		if (pt->rp[i]=='L') {
		sprintf(ss,"%-8s  LE  "tfmt" "dfmt" "dfmt" "dfmt,
		ss,"-infinity",pt->aj[i],pt->b[i],pt->y0[i]);
		}

		else if (pt->rp[i]=='G') {
		sprintf(ss,"%-8s  GE  "dfmt" "dfmt" "tfmt" "dfmt,
		ss,pt->r[i],pt->aj[i],"+infinity",pt->y0[i]);
		}

		else {
		sprintf(ss,"%-8s  RG  "dfmt" "dfmt" "dfmt" "dfmt,
		ss,pt->r[i],pt->aj[i],pt->b[i],pt->y0[i]);
		}
		h++;
		}
		fprintf(fp," %-6d %s\n",i+1,ss);
		}


		fprintf(fp, "\nCOLUMNS\n");
		fprintf(fp, "-------\n");

		fprintf(fp, " %-6s %-8s %4s "tfmt" "tfmt" "tfmt" "tfmt"\n",
			"order", "name", "type", "lower", "active",
			"upper", "dual slack");
		for (j = 0; j<pt->n0; j++) {
			//printf("%f\n", pt->x0[j]);
			k=iGet(fbin);
			fread(ss,1,k,fbin);
			ss[k]='\0';

			pt->z0[j]=-pt->ai[j];

			if (pt->l[j]<-bplus) {
			if (pt->u[j]>bplus)
			sprintf(ss,"%-8s  FR  "tfmt" "dfmt" "tfmt" "dfmt,
			ss,"-infinity",pt->x0[j],"+infinity",pt->z0[j]);
			else
			sprintf(ss,"%-8s  UP  "tfmt" "dfmt" "dfmt" "dfmt,
			ss,"-infinity",pt->x0[j],pt->u[j],pt->z0[j]);
			}

			else {
			if (pt->u[j]>bplus)
			sprintf(ss,"%-8s  LO  "dfmt" "dfmt" "tfmt" "dfmt,
			ss,pt->l[j],pt->x0[j],"+infinity",pt->z0[j]);
			else if (fabs(pt->l[j]-pt->u[j])<1.0e-13)
			sprintf(ss,"%-8s  FX  "dfmt" "dfmt" "dfmt" "dfmt,
			ss,pt->l[j],pt->x0[j],pt->u[j],pt->z0[j]);
			else
			sprintf(ss,"%-8s  BO  "dfmt" "dfmt" "dfmt" "dfmt,
			ss,pt->l[j],pt->x0[j],pt->u[j],pt->z0[j]);
			}
			fprintf(fp," %-6d %s\n",j+1,ss);
		}

		fprintf(fp, "\n------------------------------------ EOF");
		fprintf(fp, " ------------------------------------\n");

		fclose(fp);
		return true;
	}
	else{
		LeftDots(ss, 36);
		printf(" report file name %s\n\n", ss);
		fprintf(fp, "\nCOLUMNS\n"
					  "-------\n");
		int j;
		for (j = 0; j<pt->n0; j++) {
			printf("%d : %f ",j, pt->x0[j]);
		}
		printf("\n");
		fprintf(fp, "\n------------------------------------ EOF");
		fprintf(fp, " ------------------------------------\n");

		fclose(fp);
		return true;
	}
} /* OutRept */

void RepShutDown(solpt *pt)
{
  cFree(&pt->rp);
  
  iFree(&pt->subj);
  iFree(&pt->subi);
  
  dFree(&pt->x);
  dFree(&pt->y);
  dFree(&pt->z);
  
  dFree(&pt->x0);
  dFree(&pt->y0);
  dFree(&pt->z0);
  
  dFree(&pt->r);
  dFree(&pt->b);
  dFree(&pt->c);
  dFree(&pt->l);
  dFree(&pt->u);
  
  dFree(&pt->ai);
  dFree(&pt->aj);
  
  mFree(&pt->a);
  return true;
} /* RepShutDown */

int Reportsol(solpt* pt)
{
  int     h,n,m,fsze,*item,key,resp;
  char    ss[128];
  char    skey[][12]={
            "unsolved",  "optimal",
            "infeasible","unbounded",
            "difficulty"};
  double  *x1,*y1,*z1,rtmp,*x = NULL;

  clock_t ts,te;
  
  /*
   *  get solution
   */
  ts=GetTime();
  if(INFM_RPT)RepPrintHead();
    
  fsol=fopen("coplfile.sol","rb");
  if (!fsol) return 1; //exit(0);
  
  resp=iGet(fsol);
  n   =iGet(fsol);
  m   =iGet(fsol);
  
  x1  =dAlloc(n,"no");
  y1 = dAlloc(m, "no");
  z1 = dAlloc(n, "no");
  
  if (n&&m) {
    fread(x1,8,n,fsol);
    fread(y1,8,m,fsol);
    fread(z1,8,n,fsol);
  }
  
  pt->resp=resp;
  
  fclose(fsol);
  
  fstk=fopen("coplfile.stk","rb");
  if (!fstk) return 1; //exit(0);
  
  fseek(fstk,-4,SEEK_END);
  fread(&fsze,4,1,fstk);
  if (fsze <= 0) return 1; //exit(0);
  
  item = iAlloc(fsze + 1, "no");
  rewind(fstk);
  fread(item,4,fsze+1,fstk);
  
  fclose(fstk);
  
  fbin=fopen("coplfile.bin","rb");
  if (!fbin) return 1; //exit(0);
    
  pt->x=x1;
  pt->y=y1;
  pt->z=z1;
  
  for (h=fsze-1; h>=0; h--) {
    fseek(fbin,item[h],SEEK_SET);
    key=iGet(fbin);
    
    PostSol(key,pt);
  }
  
  if (key != NMES)return 1; //exit(0);
  
  if (!pt->ai) pt->ai = dAlloc(pt->n0, "no");
  if (!pt->aj) pt->aj = dAlloc(pt->m0, "no");
  
  GetActv(pt);
  if(RPT_FILE)OutRept(pt);
  fclose(fbin);   



  fsze=0;  
  iFree(&item);
  te=GetTime();
  rtmp=TimeInSec(ts,te);
  
  
  sprintf(ss," %d",pt->cdmn);
  LeftDots(ss,29);
  if(INFM_RPT)printf(" dominated column passes %s\n",ss);
  fsze+=pt->cdmn;
  
  sprintf(ss," %d",pt->cdup);
  LeftDots(ss,29);
  if(INFM_RPT)printf(" duplicate column passes %s\n",ss);
  fsze+=pt->cdup;
  
  sprintf(ss," %d",pt->cfix);
  LeftDots(ss,33);
  if(INFM_RPT)printf(" fixed column passes %s\n",ss);
  fsze+=pt->cfix;
  
  sprintf(ss," %d",pt->cnul);
  LeftDots(ss,34);
  if(INFM_RPT)printf(" null column passes %s\n",ss);
  fsze+=pt->cnul;
  
  sprintf(ss," %d",pt->lbnd);
  LeftDots(ss,34);
  if(INFM_RPT)printf(" lower bound passes %s\n",ss);
  fsze+=pt->lbnd;
  
  sprintf(ss," %d",pt->mins);
  LeftDots(ss,34);
  if(INFM_RPT)printf(" minus bound passes %s\n",ss);
  fsze+=pt->mins;

  sprintf(ss," %d",pt->rdbl);
  LeftDots(ss,32);
  if(INFM_RPT)printf(" doubleton row passes %s\n",ss);
  fsze+=pt->rdbl;
  
  sprintf(ss," %d",pt->rdmn);
  LeftDots(ss,32);
  if(INFM_RPT)printf(" dominated row passes %s\n",ss);
  fsze+=pt->rdmn;
  
  sprintf(ss," %d",pt->rdup);
  LeftDots(ss,32);
  if(INFM_RPT)printf(" duplicate row passes %s\n",ss);
  fsze+=pt->rdup;
  
  sprintf(ss," %d",pt->rfrc);
  LeftDots(ss,34);
  if(INFM_RPT)printf(" forcing row passes %s\n",ss);
  fsze+=pt->rfrc;
  
  sprintf(ss," %d",pt->rnul);
  LeftDots(ss,37);
  if(INFM_RPT)printf(" null row passes %s\n",ss);
  fsze+=pt->rnul;
  
  sprintf(ss," %d",pt->rsng);
  LeftDots(ss,32);
  if(INFM_RPT)printf(" singleton row passes %s\n",ss);
  fsze+=pt->rsng;
  
  sprintf(ss," %d",fsze);
  LeftDots(ss,30);
  if(INFM_RPT)printf(" number of total passes %s\n\n",ss);
  
  sprintf(ss," %.2f sec",rtmp);
  LeftDots(ss,41);
  if(INFM_RPT)printf(" elapse time %s\n\n",ss);
  
  if(INFM_RPT)printf(" ================="
         " END OF POSTSOLVER"
         " =================\n\n");
  
  return 0;
} /* PostProc */
