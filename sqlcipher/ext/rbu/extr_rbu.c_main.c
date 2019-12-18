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
typedef  int /*<<< orphan*/  zBuf ;
typedef  int /*<<< orphan*/  sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
#define  SQLITE_DONE 129 
#define  SQLITE_OK 128 
 int /*<<< orphan*/  SQLITE_STATUS_MEMORY_USED ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  report_default_vfs () ; 
 int /*<<< orphan*/  report_rbu_vfs (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_status64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3rbu_bp_progress (int /*<<< orphan*/ *,int*,int*) ; 
 int sqlite3rbu_close (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * sqlite3rbu_db (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3rbu_open (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3rbu_progress (int /*<<< orphan*/ *) ; 
 int sqlite3rbu_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3rbu_vacuum (char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv){
  int i;
  const char *zTarget;            /* Target database to apply RBU to */
  const char *zRbu;               /* Database containing RBU */
  char zBuf[200];                 /* Buffer for printf() */
  char *zErrmsg = 0;              /* Error message, if any */
  sqlite3rbu *pRbu;               /* RBU handle */
  int nStep = 0;                  /* Maximum number of step() calls */
  int nStatStep = 0;              /* Report stats after this many step calls */
  int bVacuum = 0;
  const char *zPreSql = 0;
  int rc = SQLITE_OK;
  sqlite3_int64 nProgress = 0;
  int nArgc = argc-2;

  if( argc<3 ) usage(argv[0]);
  for(i=1; i<nArgc; i++){
    const char *zArg = argv[i];
    int nArg = strlen(zArg);
    if( nArg>1 && nArg<=8 && 0==memcmp(zArg, "-vacuum", nArg) ){
      bVacuum = 1;
    }else if( nArg>1 && nArg<=7 
           && 0==memcmp(zArg, "-presql", nArg) && i<nArg-1 ){
      i++;
      zPreSql = argv[i];
    }else if( nArg>1 && nArg<=5 && 0==memcmp(zArg, "-step", nArg) && i<nArg-1 ){
      i++;
      nStep = atoi(argv[i]);
    }else if( nArg>1 && nArg<=9 
           && 0==memcmp(zArg, "-statstep", nArg) && i<nArg-1 
    ){
      i++;
      nStatStep = atoi(argv[i]);
    }else{
      usage(argv[0]);
    }
  }

  zTarget = argv[argc-2];
  zRbu = argv[argc-1];

  report_default_vfs();

  /* Open an RBU handle. A vacuum handle if -vacuum was specified, or a
  ** regular RBU update handle otherwise.  */
  if( bVacuum ){
    pRbu = sqlite3rbu_vacuum(zTarget, zRbu);
  }else{
    pRbu = sqlite3rbu_open(zTarget, zRbu, 0);
  }
  report_rbu_vfs(pRbu);

  if( zPreSql && pRbu ){
    sqlite3 *dbMain = sqlite3rbu_db(pRbu, 0);
    rc = sqlite3_exec(dbMain, zPreSql, 0, 0, 0);
    if( rc==SQLITE_OK ){
      sqlite3 *dbRbu = sqlite3rbu_db(pRbu, 1);
      rc = sqlite3_exec(dbRbu, zPreSql, 0, 0, 0);
    }
  }

  /* If nStep is less than or equal to zero, call
  ** sqlite3rbu_step() until either the RBU has been completely applied
  ** or an error occurs. Or, if nStep is greater than zero, call
  ** sqlite3rbu_step() a maximum of nStep times.  */
  if( rc==SQLITE_OK ){
    for(i=0; (nStep<=0 || i<nStep) && sqlite3rbu_step(pRbu)==SQLITE_OK; i++){
      if( nStatStep>0 && (i % nStatStep)==0 ){
        sqlite3_int64 nUsed;
        sqlite3_int64 nHighwater;
        sqlite3_status64(SQLITE_STATUS_MEMORY_USED, &nUsed, &nHighwater, 0);
        fprintf(stdout, "memory used=%lld highwater=%lld", nUsed, nHighwater);
        if( bVacuum==0 ){
          int one;
          int two;
          sqlite3rbu_bp_progress(pRbu, &one, &two);
          fprintf(stdout, "  progress=%d/%d\n", one, two);
        }else{
          fprintf(stdout, "\n");
        }
        fflush(stdout);
      }
    }
    nProgress = sqlite3rbu_progress(pRbu);
    rc = sqlite3rbu_close(pRbu, &zErrmsg);
  }

  /* Let the user know what happened. */
  switch( rc ){
    case SQLITE_OK:
      sqlite3_snprintf(sizeof(zBuf), zBuf,
          "SQLITE_OK: rbu update incomplete (%lld operations so far)\n",
          nProgress
      );
      fprintf(stdout, "%s", zBuf);
      break;

    case SQLITE_DONE:
      sqlite3_snprintf(sizeof(zBuf), zBuf,
          "SQLITE_DONE: rbu update completed (%lld operations)\n",
          nProgress
      );
      fprintf(stdout, "%s", zBuf);
      break;

    default:
      fprintf(stderr, "error=%d: %s\n", rc, zErrmsg);
      break;
  }

  sqlite3_free(zErrmsg);
  return (rc==SQLITE_OK || rc==SQLITE_DONE) ? 0 : 1;
}