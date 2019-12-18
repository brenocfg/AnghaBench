#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int sqlite3_uint64 ;
typedef  int LogEst ;

/* Variables and functions */
 int /*<<< orphan*/  atof (char const*) ; 
 int atoi (char const*) ; 
 scalar_t__ isFloat (char const*) ; 
 scalar_t__ isInteger (char const*) ; 
 int logEstAdd (int,int) ; 
 int logEstFromDouble (int /*<<< orphan*/ ) ; 
 int logEstFromInteger (int) ; 
 int logEstMultiply (int,int) ; 
 int logEstToInt (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int /*<<< orphan*/  showHelp (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int main(int argc, char **argv){
  int i;
  int n = 0;
  LogEst a[100];
  for(i=1; i<argc; i++){
    const char *z = argv[i];
    if( strcmp(z,"+")==0 ){
      if( n>=2 ){
        a[n-2] = logEstAdd(a[n-2],a[n-1]);
        n--;
      }
    }else if( strcmp(z,"x")==0 ){
      if( n>=2 ){
        a[n-2] = logEstMultiply(a[n-2],a[n-1]);
        n--;
      }
    }else if( strcmp(z,"dup")==0 ){
      if( n>0 ){
        a[n] = a[n-1];
        n++;
      }
    }else if( strcmp(z,"log")==0 ){
      if( n>0 ) a[n-1] = logEstFromInteger(a[n-1]) - 33;
    }else if( strcmp(z,"nlogn")==0 ){
      if( n>0 ) a[n-1] += logEstFromInteger(a[n-1]) - 33;
    }else if( strcmp(z,"inv")==0 ){
      if( n>0 ) a[n-1] = -a[n-1];
    }else if( z[0]=='^' ){
      a[n++] = (LogEst)atoi(z+1);
    }else if( isInteger(z) ){
      a[n++] = logEstFromInteger(atoi(z));
    }else if( isFloat(z) && z[0]!='-' ){
      a[n++] = logEstFromDouble(atof(z));
    }else{
      showHelp(argv[0]);
    }
  }
  for(i=n-1; i>=0; i--){
    if( a[i]<-40 ){
      printf("%5d (%f)\n", a[i], 1.0/(double)logEstToInt(-a[i]));
    }else if( a[i]<10 ){
      printf("%5d (%f)\n", a[i], logEstToInt(a[i]+100)/1024.0);
    }else{
      sqlite3_uint64 x = logEstToInt(a[i]+100)*100/1024;
      printf("%5d (%lld.%02lld)\n", a[i], x/100, x%100);
    }
  }
  return 0;
}