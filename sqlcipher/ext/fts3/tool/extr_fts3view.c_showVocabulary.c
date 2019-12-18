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
typedef  int /*<<< orphan*/  sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  findOption (char*,int,char*) ; 
 int /*<<< orphan*/ * prepare (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  runSql (int /*<<< orphan*/ *,char*,...) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_randomness (int,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void showVocabulary(sqlite3 *db, const char *zTab){
  char *zAux;
  sqlite3_uint64 r;
  sqlite3_stmt *pStmt;
  int nDoc = 0;
  int nToken = 0;
  int nOccurrence = 0;
  int nTop;
  int n, i;

  sqlite3_randomness(sizeof(r), &r);
  zAux = sqlite3_mprintf("viewer_%llx", zTab, r);
  runSql(db, "BEGIN");
  pStmt = prepare(db, "SELECT count(*) FROM %Q", zTab);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    nDoc = sqlite3_column_int(pStmt, 0);
  }
  sqlite3_finalize(pStmt);
  printf("Number of documents...................... %9d\n", nDoc);

  runSql(db, "CREATE VIRTUAL TABLE %s USING fts4aux(%Q)", zAux, zTab);
  pStmt = prepare(db, 
             "SELECT count(*), sum(occurrences) FROM %s WHERE col='*'",
             zAux);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    nToken = sqlite3_column_int(pStmt, 0);
    nOccurrence = sqlite3_column_int(pStmt, 1);
  }
  sqlite3_finalize(pStmt);
  printf("Total tokens in all documents............ %9d\n", nOccurrence);
  printf("Total number of distinct tokens.......... %9d\n", nToken);
  if( nToken==0 ) goto end_vocab;

  n = 0;
  pStmt = prepare(db, "SELECT count(*) FROM %s"
                      " WHERE col='*' AND occurrences==1", zAux);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    n = sqlite3_column_int(pStmt, 0);
  }
  sqlite3_finalize(pStmt);
  printf("Tokens used exactly once................. %9d %5.2f%%\n",
          n, n*100.0/nToken);

  n = 0;
  pStmt = prepare(db, "SELECT count(*) FROM %s"
                      " WHERE col='*' AND documents==1", zAux);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    n = sqlite3_column_int(pStmt, 0);
  }
  sqlite3_finalize(pStmt);
  printf("Tokens used in only one document......... %9d %5.2f%%\n",
          n, n*100.0/nToken);

  if( nDoc>=2000 ){
    n = 0;
    pStmt = prepare(db, "SELECT count(*) FROM %s"
                        " WHERE col='*' AND occurrences<=%d", zAux, nDoc/1000);
    while( sqlite3_step(pStmt)==SQLITE_ROW ){
      n = sqlite3_column_int(pStmt, 0);
    }
    sqlite3_finalize(pStmt);
    printf("Tokens used in 0.1%% or less of docs...... %9d %5.2f%%\n",
            n, n*100.0/nToken);
  }

  if( nDoc>=200 ){
    n = 0;
    pStmt = prepare(db, "SELECT count(*) FROM %s"
                        " WHERE col='*' AND occurrences<=%d", zAux, nDoc/100);
    while( sqlite3_step(pStmt)==SQLITE_ROW ){
      n = sqlite3_column_int(pStmt, 0);
    }
    sqlite3_finalize(pStmt);
    printf("Tokens used in 1%% or less of docs........ %9d %5.2f%%\n",
            n, n*100.0/nToken);
  }

  nTop = atoi(findOption("top", 1, "25"));
  printf("The %d most common tokens:\n", nTop);
  pStmt = prepare(db,
            "SELECT term, documents FROM %s"
            " WHERE col='*'"
            " ORDER BY documents DESC, term"
            " LIMIT %d", zAux, nTop);
  i = 0;
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    i++;
    n = sqlite3_column_int(pStmt, 1);
    printf("  %2d. %-30s %9d docs %5.2f%%\n", i,
      sqlite3_column_text(pStmt, 0), n, n*100.0/nDoc);
  }
  sqlite3_finalize(pStmt);

end_vocab:
  runSql(db, "ROLLBACK");
  sqlite3_free(zAux);
}