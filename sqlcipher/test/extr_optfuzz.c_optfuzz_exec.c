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
typedef  int /*<<< orphan*/  zLine ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_NULL ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int SQLITE_TEXT ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * prepare_sql (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  run_sql (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,char const**) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*) ; 
 int /*<<< orphan*/  sqlite3_sql (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int optfuzz_exec(
  sqlite3 *dbRun,             /* The database on which the SQL executes */
  const char *zSql,           /* The SQL to be executed */
  sqlite3 *dbOut,             /* Store results in this database */
  const char *zOutTab,        /* Store results in this table of dbOut */
  int *pnStmt,                /* Write the number of statements here */
  int *pnRow,                 /* Write the number of rows here */
  int bTrace                  /* Print query results if true */
){
  int rc = SQLITE_OK;         /* Return code */
  const char *zLeftover;      /* Tail of unprocessed SQL */
  sqlite3_stmt *pStmt = 0;    /* The current SQL statement */
  sqlite3_stmt *pIns = 0;     /* Statement to insert into dbOut */
  const char *zCol;           /* Single column value */
  int nCol;                   /* Number of output columns */
  char zLine[4000];           /* Complete row value */

  run_sql(dbOut, "BEGIN");
  run_sql(dbOut, "CREATE TABLE IF NOT EXISTS staging(x TEXT)");
  run_sql(dbOut, "CREATE TABLE IF NOT EXISTS \"%w\"(x TEXT)", zOutTab);
  pIns = prepare_sql(dbOut, "INSERT INTO staging(x) VALUES(?1)");
  *pnRow = *pnStmt = 0;
  while( rc==SQLITE_OK && zSql && zSql[0] ){
    zLeftover = 0;
    rc = sqlite3_prepare_v2(dbRun, zSql, -1, &pStmt, &zLeftover);
    zSql = zLeftover;
    assert( rc==SQLITE_OK || pStmt==0 );
    if( rc!=SQLITE_OK ){
      printf("Error with [%s]\n%s\n", zSql, sqlite3_errmsg(dbRun));
      break;
    }
    if( !pStmt ) continue;
    (*pnStmt)++;
    nCol = sqlite3_column_count(pStmt);
    run_sql(dbOut, "DELETE FROM staging;");
    while( sqlite3_step(pStmt)==SQLITE_ROW ){
      int i, j;
      for(i=j=0; i<nCol && j<sizeof(zLine)-50; i++){
        int eType = sqlite3_column_type(pStmt, i);
        if( eType==SQLITE_NULL ){
          zCol = "NULL";
        }else{
          zCol = (const char*)sqlite3_column_text(pStmt, i);
        }
        if( i ) zLine[j++] = ',';
        if( eType==SQLITE_TEXT ){
          sqlite3_snprintf(sizeof(zLine)-j, zLine+j, "'%q'", zCol);
        }else{
          sqlite3_snprintf(sizeof(zLine)-j, zLine+j, "%s", zCol);
        }
        j += (int)strlen(zLine+j);
      }
      /* Detect if any row is too large and throw an error, because we will
      ** want to go back and look more closely at that case */
      if( j>=sizeof(zLine)-100 ){
        printf("Excessively long output line: %d bytes\n" ,j);
        exit(1);
      }
      if( bTrace ){
        printf("%s\n", zLine);
      }
      (*pnRow)++;
      sqlite3_bind_text(pIns, 1, zLine, j, SQLITE_TRANSIENT);
      rc = sqlite3_step(pIns);
      assert( rc==SQLITE_DONE );
      rc = sqlite3_reset(pIns);
    }
    run_sql(dbOut,
      "INSERT INTO \"%w\"(x) VALUES('### %q ###')",
      zOutTab, sqlite3_sql(pStmt)
    );
    run_sql(dbOut, 
      "INSERT INTO \"%w\"(x) SELECT group_concat(x,char(10))"
      "  FROM (SELECT x FROM staging ORDER BY x)",
      zOutTab
    );
    run_sql(dbOut, "COMMIT");
    sqlite3_finalize(pStmt);
    pStmt = 0;
  }
  sqlite3_finalize(pStmt);
  sqlite3_finalize(pIns);
  return rc;
}