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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  azDb ;
typedef  int /*<<< orphan*/  Str ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SQLITE_CONFIG_HEAP ; 
 int /*<<< orphan*/  SQLITE_CONFIG_LOG ; 
 int /*<<< orphan*/  SQLITE_CONFIG_LOOKASIDE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_OPEN_READWRITE ; 
 scalar_t__ SQLITE_ROW ; 
 unsigned int SQL_OUTPUT ; 
 unsigned int SQL_TRACE ; 
 int /*<<< orphan*/  StrAppend (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  StrFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  createVFile (char*,char*) ; 
 int /*<<< orphan*/  fatalError (char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  formatVfs () ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  inmemVfsRegister () ; 
 int integerValue (char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  progressHandler ; 
 char** realloc (char**,int) ; 
 int /*<<< orphan*/  reformatVfs () ; 
 int /*<<< orphan*/  runSql (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  setAlarm (int) ; 
 int /*<<< orphan*/  showHelp (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlLog ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_config (int /*<<< orphan*/ ,void*,...) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_memory_used () ; 
 int sqlite3_open_v2 (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_progress_handler (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  timeoutHandler ; 

int main(int argc, char **argv){
  int i;                 /* Loop counter */
  int nDb = 0;           /* Number of databases to fuzz */
  char **azDb = 0;       /* Names of the databases (limit: 20) */
  int verboseFlag = 0;   /* True for extra output */
  int noLookaside = 0;   /* Disable lookaside if true */
  int vdbeLimitFlag = 0; /* Stop after 100,000 VDBE ops */
  int nHeap = 0;         /* True for fixed heap size */
  int iTimeout = 0;      /* Timeout delay in seconds */
  int rc;                /* Result code from SQLite3 API calls */
  sqlite3 *db;           /* The database connection */
  sqlite3_stmt *pStmt;   /* A single SQL statement */
  Str sql;               /* SQL to run */
  unsigned runFlags = 0; /* Flags passed to runSql */

  for(i=1; i<argc; i++){
    char *z = argv[i];
    if( z[0]!='-' ){
      azDb = realloc(azDb, sizeof(azDb[0])*(nDb+1));
      if( azDb==0 ) fatalError("out of memory");
      azDb[nDb++] = z;
      continue;
    }
    z++;
    if( z[0]=='-' ) z++;
    if( strcmp(z, "help")==0 ){
      showHelp(argv[0]);
    }else if( strcmp(z, "limit-mem")==0 ){
      if( i==argc-1 ) fatalError("missing argument to %s", argv[i]);
      nHeap = integerValue(argv[++i]);
    }else if( strcmp(z, "no-lookaside")==0 ){
      noLookaside = 1;
    }else if( strcmp(z, "timeout")==0 ){
      if( i==argc-1 ) fatalError("missing argument to %s", argv[i]);
      iTimeout = integerValue(argv[++i]);
    }else if( strcmp(z, "trace")==0 ){
      runFlags |= SQL_OUTPUT|SQL_TRACE;
    }else if( strcmp(z, "limit-vdbe")==0 ){
      vdbeLimitFlag = 1;
    }else if( strcmp(z, "v")==0 || strcmp(z, "verbose")==0 ){
      verboseFlag = 1;
      runFlags |= SQL_TRACE;
    }else{
      fatalError("unknown command-line option: \"%s\"\n", argv[i]);
    }
  }
  if( nDb==0 ){
    showHelp(argv[0]);
  }
  if( verboseFlag ){
    sqlite3_config(SQLITE_CONFIG_LOG, sqlLog);
  }
  if( nHeap>0 ){
    void *pHeap = malloc( nHeap );
    if( pHeap==0 ) fatalError("cannot allocate %d-byte heap\n", nHeap);
    rc = sqlite3_config(SQLITE_CONFIG_HEAP, pHeap, nHeap, 32);
    if( rc ) fatalError("heap configuration failed: %d\n", rc);
  }
  if( noLookaside ){
    sqlite3_config(SQLITE_CONFIG_LOOKASIDE, 0, 0);
  }
  inmemVfsRegister();
  formatVfs();
  StrInit(&sql);
#ifdef __unix__
  signal(SIGALRM, timeoutHandler);
#endif
  for(i=0; i<nDb; i++){
    if( verboseFlag && nDb>1 ){
      printf("DATABASE-FILE: %s\n", azDb[i]);
      fflush(stdout);
    }
    if( iTimeout ) setAlarm(iTimeout);
    createVFile("test.db", azDb[i]);
    rc = sqlite3_open_v2("test.db", &db, SQLITE_OPEN_READWRITE, "inmem");
    if( rc ){
      printf("cannot open test.db for \"%s\"\n", azDb[i]);
      reformatVfs();
      continue;
    }
#ifndef SQLITE_OMIT_PROGRESS_CALLBACK
    if( vdbeLimitFlag ){
      sqlite3_progress_handler(db, 100000, progressHandler, &vdbeLimitFlag);
    }
#endif
    rc = sqlite3_prepare_v2(db, "SELECT sql FROM autoexec", -1, &pStmt, 0);
    if( rc==SQLITE_OK ){
      while( SQLITE_ROW==sqlite3_step(pStmt) ){
        StrAppend(&sql, (const char*)sqlite3_column_text(pStmt, 0));
        StrAppend(&sql, "\n");
      }
    }
    sqlite3_finalize(pStmt);
    StrAppend(&sql, "PRAGMA integrity_check;\n");
    runSql(db, StrStr(&sql), runFlags);
    sqlite3_close(db);
    reformatVfs();
    StrFree(&sql);
    if( sqlite3_memory_used()>0 ){
      free(azDb);
      reformatVfs();
      fatalError("memory leak of %lld bytes", sqlite3_memory_used());
    }
  }
  StrFree(&sql);
  reformatVfs();
  return 0;
}