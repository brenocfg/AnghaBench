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
typedef  int /*<<< orphan*/  y ;
typedef  int /*<<< orphan*/  x ;
struct rlimit {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;

/* Variables and functions */
 int RLIMIT_AS ; 
 int RLIMIT_DATA ; 
 int RLIMIT_STACK ; 
 scalar_t__ atoi (char*) ; 
 int bVdbeDebug ; 
 int eVerbosity ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  getrlimit (int,struct rlimit*) ; 
 int /*<<< orphan*/  memset (struct rlimit*,int /*<<< orphan*/ ,int) ; 
 void* mxCb ; 
 int numberOfVChar (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int /*<<< orphan*/  setrlimit (int,struct rlimit*) ; 
 int /*<<< orphan*/  sqlite3MemTraceActivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strtol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* szMax ; 

int LLVMFuzzerInitialize(int *pArgc, char ***pArgv){
  int i, j, n;
  int argc = *pArgc;
  char **argv = *pArgv;
  for(i=j=1; i<argc; i++){
    char *z = argv[i];
    if( z[0]=='-' ){
      z++;
      if( z[0]=='-' ) z++;
      if( z[0]=='v' && (n = numberOfVChar(z))>0 ){
        eVerbosity += n;
        continue;
      }
      if( strcmp(z,"vdbe-debug")==0 ){
        bVdbeDebug = 1;
        continue;
      }
      if( strcmp(z,"limit")==0 ){
        if( i+1==argc ){
          fprintf(stderr, "missing argument to %s\n", argv[i]);
          exit(1);
        }
        mxCb = strtol(argv[++i], 0, 0);
        continue;
      }
      if( strcmp(z,"memtrace")==0 ){
        sqlite3MemTraceActivate(stdout);
        continue;
      }
      if( strcmp(z,"mem")==0 ){
        bVdbeDebug = 1;
        continue;
      }
      if( strcmp(z,"max-db-size")==0 ){
        if( i+1==argc ){
          fprintf(stderr, "missing argument to %s\n", argv[i]);
          exit(1);
        }
        szMax = strtol(argv[++i], 0, 0);
        continue;
      }
#ifndef _WIN32
      if( strcmp(z,"max-stack")==0
       || strcmp(z,"max-data")==0
       || strcmp(z,"max-as")==0
      ){
        struct rlimit x,y;
        int resource = RLIMIT_STACK;
        char *zType = "RLIMIT_STACK";
        if( i+1==argc ){
          fprintf(stderr, "missing argument to %s\n", argv[i]);
          exit(1);
        }
        if( z[4]=='d' ){
          resource = RLIMIT_DATA;
          zType = "RLIMIT_DATA";
        }
        if( z[4]=='a' ){
          resource = RLIMIT_AS;
          zType = "RLIMIT_AS";
        }
        memset(&x,0,sizeof(x));
        getrlimit(resource, &x);
        y.rlim_cur = atoi(argv[++i]);
        y.rlim_max = x.rlim_cur;
        setrlimit(resource, &y);
        memset(&y,0,sizeof(y));
        getrlimit(resource, &y);
        printf("%s changed from %d to %d\n", 
               zType, (int)x.rlim_cur, (int)y.rlim_cur);
        continue;
      }
#endif /* _WIN32 */
    }
    argv[j++] = argv[i];
  }
  argv[j] = 0;
  *pArgc = j;
  return 0;
}