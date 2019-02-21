#include "LPdefine.h"

void ResList(int    id,
             optpar *op,
             optmod *ot)
{
  char ss[LineSize];
  
  if(OUT_FILE)fprintf(fout,"\nComputational Results\n");
  if(OUT_FILE)fprintf(fout,"---------------------\n");
  if (id) {
    if(OUT_FILE)fprintf(fout," Interior-Point Optimization Results\n");
    
    sprintf(ss," " IFMT,ot->iter);
    LeftDots(ss,44);
    if(OUT_FILE)fprintf(fout,"   number of iterations " SFMT "\n",ss);
    
    sprintf(ss," " PEFT,ot->pobj);
    LeftDots(ss,48);
    if(OUT_FILE)fprintf(fout,"   primal objective " SFMT "\n",ss);

    sprintf(ss," " PEFT,ot->dobj);
    LeftDots(ss,50);
    if(OUT_FILE)fprintf(fout,"   dual objective " SFMT "\n",ss);

    sprintf(ss," " PEFT,ot->rgap);
    LeftDots(ss,49);
    if(OUT_FILE)fprintf(fout,"   primal dual gap " SFMT "\n",ss);
    
    sprintf(ss," " PEFT,ot->mu);
    LeftDots(ss,45);
    if(OUT_FILE)fprintf(fout,"   primal dual barrier " SFMT "\n",ss);
    
    sprintf(ss," " PEFT,ot->rrpnm);
    LeftDots(ss,44);
    if(OUT_FILE)fprintf(fout,"   primal infeasibility " SFMT "\n",ss);
    
    sprintf(ss," " PEFT,ot->rrdnm);
    LeftDots(ss,46);
    if(OUT_FILE)fprintf(fout,"   dual infeasibility " SFMT "\n",ss);
  }
  else {
    if(OUT_FILE)fprintf(fout," Presolving Results\n");
    sprintf(ss," " PEFT,ot->pobj);
    LeftDots(ss,48);
    if(OUT_FILE)fprintf(fout,"   primal objective " SFMT "\n",ss);

    sprintf(ss," " PEFT,ot->dobj);
    LeftDots(ss,50);
    if(OUT_FILE)fprintf(fout,"   dual objective " SFMT "\n",ss);
    
    sprintf(ss," " PEFT,fabs(ot->pobj-ot->dobj));
    LeftDots(ss,49);
    if(OUT_FILE)fprintf(fout,"   primal dual gap " SFMT "\n",ss);
    
    sprintf(ss," " PEFT,ot->rrpnm);
    LeftDots(ss,38);
    if(OUT_FILE)fprintf(fout,"   primal constraint residual " SFMT "\n",ss);
    
    sprintf(ss," " PEFT,ot->rrdnm);
    LeftDots(ss,40);
    if(OUT_FILE)fprintf(fout,"   dual constraint residual " SFMT "\n",ss);
  }
} /* ResList */

int RecSolution(optmod *opt)
{
  FILE *fp;
  
  if (!(fp=fopen(COPLFILE_SOL,"wb")))
    return ErrorProc(NOT_DSKSPC,"for coplfile.sol.");
    
  fwrite(&opt->m,sizeof(int),1,fp);
  fwrite(&opt->n,sizeof(int),1,fp);
  if (opt->nub) {
    fwrite(&opt->nub,sizeof(int),1,fp);
    fwrite(opt->xu,sizeof(double),opt->nub,fp);
    fwrite(opt->yu,sizeof(double),opt->nub,fp);
    fwrite(opt->zu,sizeof(double),opt->nub,fp);
  }
  FileClose(&fp);
  return true;
} /* RecSolution */

static void SaveSol(optmod *opt)
{
  FILE *fp;
  
  fp = fopen(COPLFILE_SOL, "wb");
  if (!fp) {
    ErrorProc(NOT_DSKSPC,COPLFILE_SOL);
    return;
  }
  
  fwrite(&opt->ista,4,1,fp);
  fwrite(&opt->n,4,1,fp);
  fwrite(&opt->m,4,1,fp);
  fwrite(opt->x,8,opt->n,fp);
  fwrite(opt->y,8,opt->m,fp);
  fwrite(opt->z,8,opt->n,fp);
  fclose(fp);
} /* SaveSol */

int OptProc(clock_t tim[],
            optmod  *opt,
            optpar  *par)
{
  int  idproc;
  
  
  /*
   * crushing
   */
  idproc=CrushProc(par,opt);
  SetTime(tim,CRUSH);
  if (!idproc) return false;
  
  /*
   * presolving
   */
  idproc=PreSolve(par,opt);
  SetTime(tim,PRSLV);
  CloseStack();
  if (!idproc) return false;
  
  if (opt->m==0||opt->n==0) {
    ResList(false,par,opt);
    ErrorProc(OPT_FOUND,NULL);
    opt->ista=0;
    opt->n   =0;
    opt->m   =0;
    SaveSol(opt);
    return true;
  }

  /*
   * solution
   */
  HsdProc(tim,opt,par);

#ifdef TEST1
  return true;
#endif

  /*
   * save solution
   */
  SaveSol(opt);
  
  return true;
} /* OptProc */
