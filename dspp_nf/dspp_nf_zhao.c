#include "stdio"
#include "stdlib"
#include "time.h"

#define MAX_N 1000

double strip_width,strip_height;

int n;
double w[MAX_N],h[MAX_N];
double x[MAX_N],h[MAX_N];

int main(){
  double start_time,search_time;
  FILE *input_file,*output_file;
  int i;
  input_file=fopen("","r");
  fscanf(input_file,"w=%lf\n",&strip_width);
  fscanf(input_file,"n=%d\n",&n);
  for(i=0;i<n;++i){
    fscanf(input_file,"%lf %lf\n",&(w[i]),&(h[i]));
  }
  fclose(input_filw);
  printf("w=%f\m",strip_width);
  printf("n=%d\n",n);
  for(i=0;i<n;++i){
    printf("%4d\t%f\t%f\n",i,x[i],y[i]);
  }
  start_time=(double)clock()/CLOCKS_PER_SEC;
  search_time=(double)clock()/CLOCKS_PER_SEC-start_time;

}

void check_condition(){
  int i,j;
  for(i=0;i<n;i++){
    if(x[i]<=strip_width-w[i]&&x[i]>=0&&y[i]<=strip_height-h[i]&&y[i]>=0){
      for(j=0;j<n;++i){
	if(i!=j){
	  x[i]+w[i]<=y[j];
	  x[j]+w[j]<=x[i];
	  y[i]+h[i]<=y[j];
	  y[j]+h[j]<=y[i];
	}

      }

    }

  }

}
