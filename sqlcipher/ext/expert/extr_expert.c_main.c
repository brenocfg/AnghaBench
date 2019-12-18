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
typedef  int /*<<< orphan*/  sqlite3expert ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  EXPERT_CONFIG_SAMPLE ; 
 int /*<<< orphan*/  EXPERT_REPORT_CANDIDATES ; 
 int /*<<< orphan*/  EXPERT_REPORT_INDEXES ; 
 int /*<<< orphan*/  EXPERT_REPORT_PLAN ; 
 int /*<<< orphan*/  EXPERT_REPORT_SQL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int option_integer_arg (char*) ; 
 int /*<<< orphan*/  option_requires_argument (char*) ; 
 int readSqlFromFile (int /*<<< orphan*/ *,char*,char**) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_expert_analyze (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  sqlite3_expert_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3_expert_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_expert_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_expert_new (int /*<<< orphan*/ *,char**) ; 
 char* sqlite3_expert_report (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_expert_sql (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int sqlite3_open (char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ sqlite3_strnicmp (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  usage (char**) ; 

int main(int argc, char **argv){
  const char *zDb;
  int rc = 0;
  char *zErr = 0;
  int i;
  int iVerbose = 1;               /* -verbose option */

  sqlite3 *db = 0;
  sqlite3expert *p = 0;

  if( argc<2 ) usage(argv);
  zDb = argv[argc-1];
  if( zDb[0]=='-' ) usage(argv);
  rc = sqlite3_open(zDb, &db);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "Cannot open db file: %s - %s\n", zDb, sqlite3_errmsg(db));
    exit(-2);
  }

  p = sqlite3_expert_new(db, &zErr);
  if( p==0 ){
    fprintf(stderr, "Cannot run analysis: %s\n", zErr);
    rc = 1;
  }else{
    for(i=1; i<(argc-1); i++){
      char *zArg = argv[i];
      int nArg;
      if( zArg[0]=='-' && zArg[1]=='-' && zArg[2]!=0 ) zArg++;
      nArg = (int)strlen(zArg);
      if( nArg>=2 && 0==sqlite3_strnicmp(zArg, "-file", nArg) ){
        if( ++i==(argc-1) ) option_requires_argument("-file");
        rc = readSqlFromFile(p, argv[i], &zErr);
      }

      else if( nArg>=3 && 0==sqlite3_strnicmp(zArg, "-sql", nArg) ){
        if( ++i==(argc-1) ) option_requires_argument("-sql");
        rc = sqlite3_expert_sql(p, argv[i], &zErr);
      }

      else if( nArg>=3 && 0==sqlite3_strnicmp(zArg, "-sample", nArg) ){
        int iSample;
        if( ++i==(argc-1) ) option_requires_argument("-sample");
        iSample = option_integer_arg(argv[i]);
        sqlite3_expert_config(p, EXPERT_CONFIG_SAMPLE, iSample);
      }

      else if( nArg>=2 && 0==sqlite3_strnicmp(zArg, "-verbose", nArg) ){
        if( ++i==(argc-1) ) option_requires_argument("-verbose");
        iVerbose = option_integer_arg(argv[i]);
      }

      else{
        usage(argv);
      }
    }
  }

  if( rc==SQLITE_OK ){
    rc = sqlite3_expert_analyze(p, &zErr);
  }

  if( rc==SQLITE_OK ){
    int nQuery = sqlite3_expert_count(p);
    if( iVerbose>0 ){
      const char *zCand = sqlite3_expert_report(p,0,EXPERT_REPORT_CANDIDATES);
      fprintf(stdout, "-- Candidates -------------------------------\n");
      fprintf(stdout, "%s\n", zCand);
    }
    for(i=0; i<nQuery; i++){
      const char *zSql = sqlite3_expert_report(p, i, EXPERT_REPORT_SQL);
      const char *zIdx = sqlite3_expert_report(p, i, EXPERT_REPORT_INDEXES);
      const char *zEQP = sqlite3_expert_report(p, i, EXPERT_REPORT_PLAN);
      if( zIdx==0 ) zIdx = "(no new indexes)\n";
      if( iVerbose>0 ){
        fprintf(stdout, "-- Query %d ----------------------------------\n",i+1);
        fprintf(stdout, "%s\n\n", zSql);
      }
      fprintf(stdout, "%s\n%s\n", zIdx, zEQP);
    }
  }else{
    fprintf(stderr, "Error: %s\n", zErr ? zErr : "?");
  }

  sqlite3_expert_destroy(p);
  sqlite3_free(zErr);
  return rc;
}