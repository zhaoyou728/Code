#include "LPdefine.h"

#ifdef DEBUG
static int count;
#endif

static FILE* fmps;
static unsigned secfield[]={4,4,7,3,6,6,6};

static char     *sec[]= {
                  "NAME","ROWS","COLUMNS",
                  "RHS","RANGES","BOUNDS",
                  "ENDATA"
                },
                *bnd[]= {
                  " LO "," UP "," FX ",
                  " FR "," MI "," PL "
                };

int GetCard(char *card,
            int  *ncrd)
{
  do {
    if (feof(fmps)) {
      ErrorProc(NOT_ENDCARD,NULL);
      exit(NOT_ENDCARD);
    }
    fgets(card,LineSize,fmps);
    (*ncrd)++;
  } while(card[0]=='*'||card[0]=='\n');

  return ((card[0]==' ')? MIDCARD:HEADCARD);
}

int ParseCard(char *card,
              char **key)
{
  key[0]=card+4;
  key[1]=card+14;
  key[2]=card+24;
  key[3]=card+39;
  key[4]=card+49;
  return true;
}

int CopyName(char *s1,char *s2)
{
  int i,j;
  
  j = strlen(s2)-1;
  if (j>8) j = 8;
  while(j>=0) {
    j--;
    if (s2[j] !=' '&&s2[j] !='\n') break;
  }
  for (i=0; i<=j; i++)
    s1[i]=s2[i];
  s1[i]='\0';
  return j+1;
}

int ReadSection(mpssec idsec,
                optpar *par,
                optmod *opt,
                int    *ncrd,
                int    *nerr)
{
  int             i,k,ifd,ityp,m,n,
                  *colsub,*imem,*id;
  char            *ptr,*key[5],type,name[9];
  double          rtmp,rang,*colval,*rmem,*cost;
  static unsigned rowscal,colscal;
  
  switch(idsec) {
    case NAME:
      rewind(fmps);
      
      ptr=opt->mpscard;       
      if (GetCard(ptr,ncrd)==HEADCARD) {
        if (strncmp(ptr,sec[idsec],secfield[idsec]))
          return ErrorProc(NOT_NAMECARD,NULL);
        
        key[1]=ptr+14;
        k     =strlen(key[1]);
        opt->prbname=cAlloc(k+1,
                              "for opt->prbname in ReadSection");
        CopyName(opt->prbname,key[1]);
        if(INFM_MPS)printf(" NAME: "SFMT"\n",opt->prbname);
        if(OUT_FILE)fprintf(fout,I6FT""SPC4,*ncrd);
		if (OUT_FILE)fprintf(fout,SFMT, ptr);
      }

      break;

    case ROWS:
      if (GetCard(opt->mpscard,ncrd)==HEADCARD) {
        ptr=opt->mpscard;
        if (strncmp(ptr,sec[idsec],secfield[idsec]))
          return ErrorProc(NOT_ROWSCARD,NULL);
        
        if(INFM_MPS)printf(" ROWS section ...\n");
        if(OUT_FILE)fprintf(fout,I6FT""SPC4""SFMT,*ncrd,ptr);
      }
      else
        return ErrorProc(NOT_ROWSCARD,NULL);
      
      for (k=0; GetCard(opt->mpscard,&i)==MIDCARD; k++); //记录有k行row
      
      opt->rowtype=cAlloc(k,"for opt->rowtype in ReadSection");
      opt->rowtab =HashAlloc(k,"for opt->rowtab in ReadSection");
      opt->rowname=cPtAlloc(k,"for opt->rowname in ReadSection");
      rowscal=(unsigned)(GoldFactor * opt->rowtab->lssz);
      
      rewind(fmps);
      do {
        GetCard(ptr,&i);
      } while (strncmp(ptr,sec[idsec],secfield[idsec]));
      key[0]=ptr+4; 
      
      while(GetCard(opt->mpscard,ncrd)==MIDCARD) {
        key[0] = opt->mpscard + 4; //Actually , it makes no sense.
        ptr=opt->mpscard+1;
        
        if (*ptr==' ') ptr++;
        type =toupper(*ptr);
        
        ityp=(type=='N'||type=='E'|| type=='G'||type=='L');
        
        if (!ityp) {
          (*nerr)++;
          if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,NOT_ROW_TYPE);
          if(OUT_FILE)fprintf(fout,"not exist row type "SFMT,opt->mpscard);
          continue;
        }
        
        if (type=='N') {
          if (opt->objname) continue;
          k           =strlen(key[0]);
          opt->objname=cAlloc(k+1,"objname in ReadSection");
          CopyName(opt->objname,key[0]);
          continue;
        }
        
        opt->m++;
        if (type=='G'||type=='L') opt->ineq++;
        
        m=opt->m-1;
        CopyName(name,key[0]);
        
        if (InsertHash(opt->rowtab,name,m,rowscal)) {
          (*nerr)++;
          if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,DPL_ROW_NAME);
          if(OUT_FILE)fprintf(fout,"duplicate row name "SFMT".\n",name);
          opt->m--;
          continue;
        }

        opt->rowtype[m]=type;
        opt->rowname[m]=cAllocCopy(name,
                                      "for opt->rowname in ReadSection");
        opt->rnamesz++;
      }
      
      break;
      
    case COLUMNS:
      ptr=opt->mpscard;
      ParseCard(ptr,key);
      if (strncmp(ptr,sec[idsec],secfield[idsec]))
        return ErrorProc(NOT_COLSCARD,NULL);
        
      if(INFM_MPS)printf(" COLUMNS section ...\n");
      if(OUT_FILE)fprintf(fout,I6FT""SPC4""SFMT,*ncrd,ptr);
      
      imem        =iAlloc(par->melm+par->mcol+1,
                            "for imem in ReadSection");
      opt->imem   =imem;
      rmem        =dAlloc(par->melm+par->mcol,
                            "for rmem in ReadSection");
      opt->rmem   =rmem;
      opt->coltab =HashAlloc(par->mcol,
                             "for opt->coltab in ReadSection");
      opt->colname=cPtAlloc(par->mcol,
                             "for opt->colname in ReadSection");
      n           =0;
      colscal     =(unsigned)(GoldFactor*opt->coltab->lssz);
      
      id          =imem;
      cost        =rmem;
      colsub      =imem+par->mcol+1;
      colval      =rmem+par->mcol;
      id[0]       =0;
      ifd         =0;
      
      while(GetCard(ptr,ncrd)==MIDCARD) {
#ifdef DEBUG
        if (count>=15992)
          if (!(count%1))
            printf("\n loop %d",count);
#endif
        
        CopyName(name,key[0]);
        if (CompString(opt->colname[n],name)) {
          opt->n++;
          n=opt->n-1;
          if (n<=par->mcol) {
            if (InsertHash(opt->coltab,name,n,colscal)) {
              (*nerr)++;
              if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,DPL_COL_NAME);
              if(OUT_FILE)fprintf(fout,"duplicate column name "SFMT".\n",name);
              opt->n--;
              continue;
            }
            
            if (opt->n>1) id[n]=opt->nz;
            cost[n]=0.0;
			opt->colname[n] = cAllocCopy(name,
				"opt->colmane in ReadSection");
			opt->cnamesz++;
          }
        }
        
        k=strlen(ptr);
        for (ifd=VALUE1,i=1; ifd<k; i+=2,ifd+=VALUE2) {
          CopyName(name,key[i]);
          rtmp=atof(key[i+1]);
          
          if (opt->nz>=par->melm) {//exceed "max element size"
            opt->nz++;
            continue;
          }
          
          if (!CompString(opt->objname,name)) {
            if (par->bemin) cost[n]=rtmp;
            else cost[n]=-rtmp;
            continue;
          }
          
          m=FoundHash(opt->rowtab,name,rowscal);
          if (m<0) {
            (*nerr)++;
            if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,NOT_ROW_NAME);
            if(OUT_FILE)fprintf(fout,"nonexisted row name "SFMT".\n",name);
            continue;
          }
          
          if (fabs(rtmp)<par->aijtol) {
            (*nerr)++;
            if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,ZERO_ELEM);
            if(OUT_FILE)fprintf(fout,"zero element found: "SFMT".\n",key[i]);
            continue;
          }
          
          *colval=rtmp;
          *colsub=m;
          
          opt->nz++;
          colval++;
          colsub++;
        }
#ifdef DEBUG
        count++;
#endif
      }
      id[opt->n]=opt->nz;
      
      k=true; //input columns well
      if (opt->n > par->mcol) {
        char ss[80];
        
        sprintf(ss,"number of columns: %d>%d.",
                opt->n,par->mcol);
        ErrorProc(EXC_COLLIM,ss);
        k=false;
      }
      
      if (opt->nz > par->melm) {
        char ss[80];
        
        sprintf(ss,"number of columns: %d>%d.",
                opt->nz,par->melm);
        ErrorProc(EXC_NNZLIM,ss);
        k=false;
      }
      if (!k) return false;
      
      BndAlloc(opt);
      break;
      
    case RHS:
      ptr=opt->mpscard;
      ParseCard(ptr,key);

      if (strncmp(ptr,sec[idsec],secfield[idsec]))
        printf(" Null RHS section\n");

      else {
        if(INFM_MPS)printf(" RHS section ...\n");
        if(OUT_FILE)fprintf(fout,I6FT""SPC4""SFMT,*ncrd,ptr);
        
        while(GetCard(ptr,ncrd)==MIDCARD) {
          CopyName(name,key[0]);
          if (!par->rhsset)
            par->rhsset=cAllocCopy(name,
                                   "for par->rhsset in ReadSection");
          else if (CompString(par->rhsset,name))
            continue;
          
          k=strlen(ptr);
          for (ifd=VALUE1,i=1; ifd<k; i+=2,ifd+=VALUE2) {
            CopyName(name,key[i]);
            rtmp=atof(key[i+1]);
            
            m=FoundHash(opt->rowtab,name,rowscal);
            if (m<0) {
              (*nerr)++;
              if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,NOT_ROW_NAME);
              if(OUT_FILE)fprintf(fout,"nonexisted row name "SFMT".\n",name);
              continue;
            }
            
            if (fabs(rtmp)<par->aijtol) {
              (*nerr)++;
              if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,ZERO_ELEM);
              if(OUT_FILE)fprintf(fout,"zero element found: "SFMT".\n",key[i]);
              continue;
            }
            
            opt->b[m]=rtmp;
          }
        }
      }
      break;
      
    case RANGES:
      for (i=0; i<opt->m; i++)
        opt->r[i]=opt->b[i];
        
      ptr=opt->mpscard;
      ParseCard(ptr,key);

      if (!strncmp(ptr,sec[idsec],secfield[idsec])) {
        if(INFM_MPS)printf(" RANGES section ...\n");
        if(OUT_FILE)fprintf(fout,I6FT""SPC4""SFMT,*ncrd,ptr);
        
        while(GetCard(ptr,ncrd)==MIDCARD) {
          CopyName(name,key[0]);
          if (!par->rngset)
            par->rngset=cAllocCopy(name,
                                   "for par->rngset in ReadSection");
          else if (CompString(par->rngset,name))
            continue;
          
          k=strlen(ptr);
          for (ifd=VALUE1,i=1; ifd<k; i+=2,ifd+=VALUE2) {
            CopyName(name,key[i]);
            rtmp=atof(key[i+1]);
            
            m=FoundHash(opt->rowtab,name,rowscal);
            if (m<0) {
              (*nerr)++;
              if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,NOT_ROW_NAME);
              if(OUT_FILE)fprintf(fout,"nonexisted row name "SFMT".\n",name);
              continue;
            }
            
            rang=fabs(rtmp);
            if (rang < par->aijtol) {
              (*nerr)++;
              if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,ZERO_ELEM);
              if(OUT_FILE)fprintf(fout,"zero element found: "SFMT".\n",key[i]);
              continue;
            }else switch(opt->rowtype[m]) {
              case 'E':
                if (rtmp<0)
                  opt->r[m]-=rang;
                else
                  opt->b[m]+=rang;
                break;
                
              case 'L':
                opt->r[m]-=rang;
                opt->ineq--;
                break;
                
              case 'G':
                opt->b[m]+=rang;
                opt->ineq--;
                break;
                
              case 'R':
                (*nerr)++;
                if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,DPL_RNG_ROW);
                if(OUT_FILE)fprintf(fout,"duplicate range setting "SFMT".\n",name);
                break;
                
              default:
                break;
            } /* switch */
            
            opt->rowtype[m]='R';
            opt->nrg++;
            
          } /* for */
        } /* while */
      } /* if */
      break;
      
    case BOUNDS:
      for (i=0; i<opt->n; i++) {
        opt->l[i]=par->lower;
        opt->u[i]=par->upper;
      }

      ptr=opt->mpscard;
      ParseCard(ptr,key);

      if (!strncmp(ptr,sec[idsec],secfield[idsec])) {
        if(INFM_MPS)printf(" BOUNDS section ...\n");
        if(OUT_FILE)fprintf(fout,I6FT""SPC4""SFMT,*ncrd,ptr);
        
        while(GetCard(ptr,ncrd)==MIDCARD) {
          CopyName(name,key[0]);
          if (!par->bndset)
            par->bndset=cAllocCopy(name,
                                   "for par->bndset in ReadSection");
          else if (CompString(par->bndset,name))
            continue;
          
          k=0;
          for (i=LOW; i<=PLS; i++) {
            if (!strncmp(ptr,bnd[i],4)) {
              k=1;
              break;
            }
          }
          
          if (!k) {
            (*nerr)++;
            if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,NOT_BND_TYPE);
            if(OUT_FILE)fprintf(fout,"nonexisted bound type "SFMT".\n",ptr);
            continue;
          }
          
          CopyName(name,key[1]);
          n=FoundHash(opt->coltab,name,colscal);
          if (n<0) {
            (*nerr)++;
            if(OUT_FILE)fprintf(fout,I6FT""SPC4"warning -- "IFMT": ",*ncrd,NOT_COL_NAME);
            if(OUT_FILE)fprintf(fout,"nonexisted row name "SFMT".\n",name);
            continue;
          }
          if (strlen(ptr)<24) rtmp=0.0;
          else rtmp=atof(key[2]);
          
          switch (i) {
            case LOW:
              opt->l[n]=rtmp;
              opt->nlow++;
              break;
              
            case UPP:
              opt->u[n]=rtmp;
              opt->nupp++;
              break;
              
            case FIX:
              opt->l[n]=rtmp;
              opt->u[n]=rtmp;
              opt->nfix++;
              break;
              
            case FRE:
              opt->u[n]= MaxPositive;
              opt->l[n]=-MaxPositive;
              opt->nfre++;
              break;
              
            case MIS:
              opt->l[n]=-MaxPositive;
              opt->u[n]= rtmp;
              opt->nbmi++;
              break;
              
            case PLS:
              opt->u[n]= MaxPositive;
              opt->l[n]= rtmp;
              opt->nbpl++;
              break;

            default:
              break;
          }
                 
        } /* while */
      } /* if */
	  
      for (i=0; i<opt->n; i++) {
        if (opt->u[i] > par->bplus&&
            opt->l[i] < -par->bplus)
          opt->nfr++;
        if (opt->u[i]==opt->l[i])
          opt->nfx++;
        if (opt->u[i]<= par->bplus)
          opt->nub++;
        if (opt->l[i]>=-par->bplus)
          opt->nlb++;
      }
      break;

    case ENDATA:
      break;
  }
  
  return true;
} /* ReadSection */

int PrintStatis(optpar *par,
                optmod *opt)
{
  int n,m,nz;
  char ss[LineSize];
    
  m =opt->m;
  n =opt->n;
  nz=opt->nz;
  
  if(OUT_FILE)fprintf(fout,"\nProblem Size\n");
  if(OUT_FILE)fprintf(fout,"------------\n");
  if(INFM_MPS)printf(" ROWS\n");
  if(OUT_FILE)fprintf(fout," ROWS\n");
  sprintf(ss," "IFMT,m);
  LeftDots(ss,59);
  if(INFM_MPS)printf("   total "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   total "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,m-opt->nsk);
  LeftDots(ss,54);
  if(INFM_MPS)printf("   equalities "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   equalities "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->ineq);
  LeftDots(ss,52);
  if(INFM_MPS)printf("   inequalities "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   inequalities "SFMT"\n",ss);

  sprintf(ss," "IFMT,opt->nrg);
  LeftDots(ss,58);
  if(INFM_MPS)printf("   ranged "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   ranged "SFMT"\n",ss);

  if(INFM_MPS)printf(" COLUMNS\n");
  if(OUT_FILE)fprintf(fout," COLUMNS\n");
  sprintf(ss," "IFMT,n);
  LeftDots(ss,59);
  if(INFM_MPS)printf("   total "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   total "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nlb);
  LeftDots(ss,51);
  if(INFM_MPS)printf("   lower bounded "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   lower bounded "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nub);
  LeftDots(ss,51);
  if(INFM_MPS)printf("   upper bounded "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   upper bounded "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nfx);
  LeftDots(ss,59);
  if(INFM_MPS)printf("   fixed "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   fixed "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nfr);
  LeftDots(ss,60);
  if(INFM_MPS)printf("   free "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   free "SFMT"\n",ss);
  
  if(INFM_MPS)printf(" BOUND CARDS\n");
  if(OUT_FILE)fprintf(fout," BOUND CARDS\n");
  sprintf(ss," "IFMT, opt->nlow+opt->nupp+opt->nfix
                     +opt->nfre+opt->nbmi+opt->nbpl);
  LeftDots(ss,59);
  if(INFM_MPS)printf("   total "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   total "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nlow);
  LeftDots(ss,59);
  if(INFM_MPS)printf("   lower "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   lower "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nupp);
  LeftDots(ss,59);
  if(INFM_MPS)printf("   upper "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   upper "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nfix);
  LeftDots(ss,59);
  if(INFM_MPS)printf("   fixed "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   fixed "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nfre);
  LeftDots(ss,60);
  if(INFM_MPS)printf("   free "SFMT"\n",ss);
  if(OUT_FILE)fprintf(fout,"   free "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nbmi);
  LeftDots(ss,59);
  if(INFM_MPS)printf("   minus "SFMT"\n",ss);
  sprintf(ss," "IFMT,opt->nbmi);
  LeftDots(ss,50);
  if(OUT_FILE)fprintf(fout,"   minus infinity "SFMT"\n",ss);
  
  sprintf(ss," "IFMT,opt->nbpl);
  LeftDots(ss,60);
  if(INFM_MPS)printf("   plus "SFMT"\n",ss);
  sprintf(ss," "IFMT,opt->nbpl);
  LeftDots(ss,51);
  if(OUT_FILE)fprintf(fout,"   plus infinity "SFMT"\n",ss);
  
  if(INFM_MPS)printf(" DENSITY\n");
  if(OUT_FILE)fprintf(fout," DENSITY\n");
  sprintf(ss," %.3f%s : "IFMT"/("IFMT"*"IFMT")",
             100.0*(((double)nz/(double)m)/(double)n),
             "%",nz,m,n);
  LeftDots(ss,56);
  if(INFM_MPS)printf("   original "SFMT"\n\n",ss);
  if(OUT_FILE)fprintf(fout,"   original "SFMT"\n",ss);
  
  return true;
}

int ReadMpsf(optpar *par,
			optmod *opt,
			char   *nmps)
{
  fmps = fopen(nmps, "r");//nmps has been checked before
  int    ncrd,nerr,idproc;
  mpssec idsec;
  
  if(INFM_MPS)printf(" BEGIN reading mps file ...\n");  
  if(OUT_FILE)fprintf(fout,"\nMPS file\n");
  if(OUT_FILE)fprintf(fout,"--------\n");
  
  nerr        =0;
  ncrd        =0;
  opt->mpscard=cAlloc(LineSize,
                         "for opt->mpscard in ReadMpsf");
  
  for (idsec=NAME; idsec<=ENDATA; ++idsec) {
    idproc=ReadSection(idsec,par,opt,&ncrd,&nerr);
    if (!idproc) {
      FileClose(&fmps); 
      return false;
    }  
  }
  
  opt->nsk=opt->ineq+opt->nrg;
  
  if(OUT_FILE)fprintf(fout,"\nxxxxxx    Total number of errors");
  if(OUT_FILE)fprintf(fout," in MPS file "I6FT"\n",nerr);
  if(INFM_MPS)printf(" END reading\n");
  PrintStatis(par,opt);
  
  cFree(&par->rhsset);
  cFree(&par->rngset);
  cFree(&par->bndset);
  cFree(&par->objname);
    
  HashFree(&opt->rowtab);
  HashFree(&opt->coltab);
  
  RecNames(nmps);
  cFree(&opt->mpscard);
  cFree(&opt->prbname);
  cFree(&opt->objname);
  
  cPtFree(&opt->rowname,opt->rnamesz);
  cPtFree(&opt->colname,opt->cnamesz);

#ifdef TEST1
  fprintf(fres,"%6d&%6d&%8d&%6d&",opt->m+1,
          opt->n,opt->nz+opt->nc,opt->nub);
#endif

  FileClose(&fmps);
  return true;
} /* ReadMpsf */

