#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_8__ {int bSchemaPK; } ;
struct TYPE_7__ {char* z; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Str ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ SQLITE_BLOB ; 
 scalar_t__ SQLITE_INTEGER ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  checkSchemasMatch (char const*) ; 
 char** columnNames (char*,char const*,int*,int*) ; 
 int /*<<< orphan*/ * db_prepare (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_6__ g ; 
 int /*<<< orphan*/  getRbudiffQuery (char const*,char**,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printQuoted (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rbuDeltaCreate (char const*,int,char const*,int,char*) ; 
 int /*<<< orphan*/  runtimeError (char*,char const*) ; 
 char* sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc (int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strFree (TYPE_1__*) ; 
 int /*<<< orphan*/  strPrintf (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  strPrintfArray (TYPE_1__*,char*,char*,char**,int) ; 

__attribute__((used)) static void rbudiff_one_table(const char *zTab, FILE *out){
  int bOtaRowid;                  /* True to use an ota_rowid column */
  int nPK;                        /* Number of primary key columns in table */
  char **azCol;                   /* NULL terminated array of col names */
  int i;
  int nCol;
  Str ct = {0, 0, 0};             /* The "CREATE TABLE data_xxx" statement */
  Str sql = {0, 0, 0};            /* Query to find differences */
  Str insert = {0, 0, 0};         /* First part of output INSERT statement */
  sqlite3_stmt *pStmt = 0;
  int nRow = 0;                   /* Total rows in data_xxx table */

  /* --rbu mode must use real primary keys. */
  g.bSchemaPK = 1;

  /* Check that the schemas of the two tables match. Exit early otherwise. */
  checkSchemasMatch(zTab);

  /* Grab the column names and PK details for the table(s). If no usable PK
  ** columns are found, bail out early.  */
  azCol = columnNames("main", zTab, &nPK, &bOtaRowid);
  if( azCol==0 ){
    runtimeError("table %s has no usable PK columns", zTab);
  }
  for(nCol=0; azCol[nCol]; nCol++);

  /* Build and output the CREATE TABLE statement for the data_xxx table */
  strPrintf(&ct, "CREATE TABLE IF NOT EXISTS 'data_%q'(", zTab);
  if( bOtaRowid ) strPrintf(&ct, "rbu_rowid, ");
  strPrintfArray(&ct, ", ", "%s", &azCol[bOtaRowid], -1);
  strPrintf(&ct, ", rbu_control);");

  /* Get the SQL for the query to retrieve data from the two databases */
  getRbudiffQuery(zTab, azCol, nPK, bOtaRowid, &sql);

  /* Build the first part of the INSERT statement output for each row
  ** in the data_xxx table. */
  strPrintf(&insert, "INSERT INTO 'data_%q' (", zTab);
  if( bOtaRowid ) strPrintf(&insert, "rbu_rowid, ");
  strPrintfArray(&insert, ", ", "%s", &azCol[bOtaRowid], -1);
  strPrintf(&insert, ", rbu_control) VALUES(");

  pStmt = db_prepare("%s", sql.z);

  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    
    /* If this is the first row output, print out the CREATE TABLE 
    ** statement first. And then set ct.z to NULL so that it is not 
    ** printed again.  */
    if( ct.z ){
      fprintf(out, "%s\n", ct.z);
      strFree(&ct);
    }

    /* Output the first part of the INSERT statement */
    fprintf(out, "%s", insert.z);
    nRow++;

    if( sqlite3_column_type(pStmt, nCol)==SQLITE_INTEGER ){
      for(i=0; i<=nCol; i++){
        if( i>0 ) fprintf(out, ", ");
        printQuoted(out, sqlite3_column_value(pStmt, i));
      }
    }else{
      char *zOtaControl;
      int nOtaControl = sqlite3_column_bytes(pStmt, nCol);

      zOtaControl = (char*)sqlite3_malloc(nOtaControl+1);
      memcpy(zOtaControl, sqlite3_column_text(pStmt, nCol), nOtaControl+1);

      for(i=0; i<nCol; i++){
        int bDone = 0;
        if( i>=nPK 
            && sqlite3_column_type(pStmt, i)==SQLITE_BLOB
            && sqlite3_column_type(pStmt, nCol+1+i)==SQLITE_BLOB
        ){
          const char *aSrc = sqlite3_column_blob(pStmt, nCol+1+i);
          int nSrc = sqlite3_column_bytes(pStmt, nCol+1+i);
          const char *aFinal = sqlite3_column_blob(pStmt, i);
          int nFinal = sqlite3_column_bytes(pStmt, i);
          char *aDelta;
          int nDelta;

          aDelta = sqlite3_malloc(nFinal + 60);
          nDelta = rbuDeltaCreate(aSrc, nSrc, aFinal, nFinal, aDelta);
          if( nDelta<nFinal ){
            int j;
            fprintf(out, "x'");
            for(j=0; j<nDelta; j++) fprintf(out, "%02x", (u8)aDelta[j]);
            fprintf(out, "'");
            zOtaControl[i-bOtaRowid] = 'f';
            bDone = 1;
          }
          sqlite3_free(aDelta);
        }

        if( bDone==0 ){
          printQuoted(out, sqlite3_column_value(pStmt, i));
        }
        fprintf(out, ", ");
      }
      fprintf(out, "'%s'", zOtaControl);
      sqlite3_free(zOtaControl);
    }

    /* And the closing bracket of the insert statement */
    fprintf(out, ");\n");
  }

  sqlite3_finalize(pStmt);
  if( nRow>0 ){
    Str cnt = {0, 0, 0};
    strPrintf(&cnt, "INSERT INTO rbu_count VALUES('data_%q', %d);", zTab, nRow);
    fprintf(out, "%s\n", cnt.z);
    strFree(&cnt);
  }

  strFree(&ct);
  strFree(&sql);
  strFree(&insert);
}