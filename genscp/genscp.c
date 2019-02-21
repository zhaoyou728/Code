/* ================================================================ */
/*   Generate random instance of set covering problem               */
/*   Programmed by Shunji Umetani <umetani@ist.osaka-u.ac.jp>       */
/*   Date: 2014/04/15                                               */
/* ================================================================ */

/* including files ------------------------------------------------ */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/* definitions ---------------------------------------------------- */
#define INVALID -1
#define NUM_EPSILON 0.00001
#define MAX_COST 100

/* forwarded declarations ----------------------------------------- */

/* randomized suffle */
void random_shuffle(int n, int *idx);

/* compare integers */
int cmp_int(const void* v1, const void* v2);

/* mt19937ar */
void init_genrand(unsigned long s);
unsigned long genrand_int32(void);
double genrand_real2(void);

/* functions ------------------------------------------------------ */

/* ---------------------------------------------------------------- */
/*   Main function                                                  */
/* ---------------------------------------------------------------- */
int main(int argc, char *argv[]){

  clock_t proc_start_time, proc_end_time;
  clock_t write_start_time, write_end_time;
  int var_num;  /* number of variables */
  int cvr_num;  /* number of cover constraints */
  int el_num;  /* number of elements in cover constraints */
  int *cost;  /* cost coefficient of j-th variable */
  int *var_num_cvr;  /* number of variables covering i-th constraint */
  int **var_idx_cvr;  /* index list of variables covering i-th constraint */
  double density;
  int seed;
  int *scan_ptr, *array, *temp_array;
  int h,i,j;
  
  /* check number of arguments */
  if(argc != 5){
    fprintf(stderr,"Invalid arguments!\n");
    fprintf(stderr,"Usage: %s cvr_num var_num density\n",argv[0]);
    fprintf(stderr,"\tcvr_num: number of covering constraints\n");
    fprintf(stderr,"\tvar_num: number of variables\n");
    fprintf(stderr,"\tdensity: density of constraint matrix\n");
    fprintf(stderr,"\tseed: seed of random number generator\n");
    return(EXIT_FAILURE);
  }
  
  /* get arguments */
  if(sscanf(argv[1],"%d", &cvr_num) != 1){
    fprintf(stderr,"Can't get number of covering constraints!\n");
    return(EXIT_FAILURE);
  }else if(cvr_num <= 0){
    fprintf(stderr,"Invalid number of covering constraints!\n");
    return(EXIT_FAILURE);
  }
  if(sscanf(argv[2],"%d", &var_num) != 1){
    fprintf(stderr,"Can't get number of variables!\n");
    return(EXIT_FAILURE);
  }else if(var_num <= 0){
    fprintf(stderr,"Invalid number of variables!\n");
    return(EXIT_FAILURE);
  }
  if(sscanf(argv[3],"%lf", &density) != 1){
    fprintf(stderr,"Can't get density of constraint matrix!\n");
    return(EXIT_FAILURE);
  }else if(density > 1.0 - NUM_EPSILON || density < NUM_EPSILON){
    fprintf(stderr,"Invalid value of density!\n");
    return(EXIT_FAILURE);
  }
  if(sscanf(argv[4],"%d", &seed) != 1){
    fprintf(stderr,"Can't get seed of random number generator!\n");
    return(EXIT_FAILURE);
  }
  
  /* initialize seed */
  init_genrand(seed);
  
  /* start processing */
  proc_start_time = clock();
  
  /* set cost coefficients */
  cost = (int *)malloc(var_num * sizeof(int));
  for(j = 0; j < var_num; j++){
    cost[j] = (int)(genrand_real2() * MAX_COST) + 1;
  }
  qsort(cost, var_num, sizeof(int), cmp_int);
  
  /* allocate memory */
  var_num_cvr = (int *)malloc(cvr_num * sizeof(int));
  var_idx_cvr = (int **)malloc(cvr_num * sizeof(int *));
  el_num = (long long int)ceil((double)cvr_num * (double)var_num * density);
  var_idx_cvr[0] = (int *)malloc(el_num * sizeof(int));
  
  /* set var_num_cvr */
  h = 0;
  for(i = 0; i < cvr_num; i++){
    var_idx_cvr[0][h] = var_idx_cvr[0][h+1] = i;
    h += 2;
  }
  for(; h < el_num; h++){
    var_idx_cvr[0][h] = (int)(genrand_real2() * cvr_num);
  }
  for(i = 0; i < cvr_num; i++){
    var_num_cvr[i] = 0;
  }
  for(h = 0; h < el_num; h++){
    i = var_idx_cvr[0][h];
    var_num_cvr[i]++;
  }
  
  /* set var_idx_cvr */
  for(i = 1; i < cvr_num; i++){
    var_idx_cvr[i] = var_idx_cvr[i-1] + var_num_cvr[i-1];
  }
  scan_ptr = (int *)malloc(cvr_num * sizeof(int));
  array = (int *)malloc(var_num * sizeof(int));
  temp_array = (int *)malloc(var_num * sizeof(int));
  for(i = 0; i < cvr_num; i++){
    scan_ptr[i] = 0;
  }
  h = j = 0;
  while(j < var_num && h < el_num){
    i = h % cvr_num;
    if(scan_ptr[i] < var_num_cvr[i]){
      var_idx_cvr[i][scan_ptr[i]] = j;
      scan_ptr[i]++;
      j++;
    }
    h++;
  }
  if(j < var_num && h >= el_num){
    fprintf(stderr,"Fail to generate instance!\n");
    return(EXIT_FAILURE);
  }
  for(i = 0; i < cvr_num; i++){
    for(j = 0; j < var_num; j++){
      temp_array[j] = j;
    }
    for(h = 0; h < scan_ptr[i]; h++){
      temp_array[var_idx_cvr[i][h]] = INVALID;
    }
    h = 0;
    for(j = 0; j < var_num; j++){
      if(temp_array[j] != INVALID){
        array[h] = temp_array[j];
        h++;
      }
    }
    random_shuffle(var_num-scan_ptr[i], array);
    for(h = scan_ptr[i]; h < var_num_cvr[i]; h++){
      var_idx_cvr[i][h] = array[h];
    }
    qsort(var_idx_cvr[i], var_num_cvr[i], sizeof(int), cmp_int);
  }
  
  
  /* end processing */
  proc_end_time = clock();
  
  /* start writing */
  write_start_time = clock();
  
  /* output instance data */
  fprintf(stdout,"%d\t%d\n",cvr_num,var_num);
  for(j = 0; j < var_num; j++){
    fprintf(stdout,"%d ",cost[j]);
  }
  fprintf(stdout,"\n");
  for(i = 0; i < cvr_num; i++){
    printf("%d\t",var_num_cvr[i]);
    for(h = 0; h < var_num_cvr[i]; h++){
      printf("%d ",var_idx_cvr[i][h]+1);  /* CAUTION!: convert index of variable j=[0,...,n-1] -> j=[1,...,n] */
    }
    printf("\n");
  }
  
  /* end writing */
  write_end_time = clock();
  
  /* free memory */
  free(array);
  free(temp_array);
  free(scan_ptr);
  free(cost);
  free(var_num_cvr);
  free(var_idx_cvr[0]);
  free(var_idx_cvr);
  
  /* print abstract */
  fprintf(stderr,"Instance -----\n");
  fprintf(stderr,"Number of constraints:\t%d\n",cvr_num);
  fprintf(stderr,"Number of variables:\t%d\n",var_num);
  fprintf(stderr,"Density:\t\t%g\n",density);
  fprintf(stderr,"Seed:\t\t\t%d\n",seed);
  
  /* print CPU time */
  fprintf(stderr,"CPU time -----\n");
  fprintf(stderr,"Processing time:\t%.3f sec\n", (double)(proc_end_time - proc_start_time) / CLOCKS_PER_SEC);
  fprintf(stderr,"Writing time:\t\t%.3f sec\n", (double)(write_end_time - write_start_time) / CLOCKS_PER_SEC);
  
  return(EXIT_SUCCESS);
}


/* ---------------------------------------------------------------- */
/*   Randomized shuffle                                             */
/* ---------------------------------------------------------------- */
void random_shuffle(int n, int *idx){
  
  int i,j,t;
  
  for(i = n-1; i > 0; i--){
    j = (int)(i * genrand_real2());
    t = idx[i];
    idx[i] = idx[j];
    idx[j] = t;
  }
}


/* ---------------------------------------------------------------- */
/*   Compare integers                                               */
/* ---------------------------------------------------------------- */
int cmp_int(const void* v1, const void* v2){
  const int _v1 = *((const int*)v1);
  const int _v2 = *((const int*)v2);
  
  if(_v1 > _v2){
    return(1);
  }else if(_v1 < _v2){
    return(-1);
  }else{
    return(0);
  }
}


/* ---------------------------------------------------------------- */
/* A C-program for MT19937, with initialization improved 2002/1/26. */
/* Coded by Takuji Nishimura and Makoto Matsumoto.                  */
/*                                                                  */
/* Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,*/
/* All rights reserved.                                             */
/* Copyright (C) 2005, Mutsuo Saito,                                */
/* All rights reserved.                                             */
/* ---------------------------------------------------------------- */

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s){
  mt[0]= s & 0xffffffffUL;
  for(mti=1; mti<N; mti++){
    mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
    /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
    /* In the previous versions, MSBs of the seed affect   */
    /* only MSBs of the array mt[].                        */
    /* 2002/01/09 modified by Makoto Matsumoto             */
    mt[mti] &= 0xffffffffUL;
    /* for >32 bit machines */
  }
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void){
  unsigned long y;
  static unsigned long mag01[2]={0x0UL, MATRIX_A};
  /* mag01[x] = x * MATRIX_A  for x=0,1 */
  if(mti >= N){ /* generate N words at one time */
    int kk;
    
    if(mti == N+1)   /* if init_genrand() has not been called, */
      init_genrand(5489UL); /* a default initial seed is used */
    for(kk=0;kk<N-M;kk++){
      y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
      mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
    }
    for(;kk<N-1;kk++){
      y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
      mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
    }
    y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
    mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];
    mti = 0;
  }
  y = mt[mti++];
  
  /* Tempering */
  y ^= (y >> 11);
  y ^= (y << 7) & 0x9d2c5680UL;
  y ^= (y << 15) & 0xefc60000UL;
  y ^= (y >> 18);
  
  return y;
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void){
  return genrand_int32()*(1.0/4294967296.0); 
  /* divided by 2^32 */
}

/* ================================================================ */
/*   End of file                                                    */
/* ================================================================ */

