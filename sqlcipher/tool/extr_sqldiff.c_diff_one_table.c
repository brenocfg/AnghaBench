#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_7__ {int fDebug; int /*<<< orphan*/  bSchemaOnly; int /*<<< orphan*/  db; } ;
struct TYPE_6__ {char* z; } ;
typedef  TYPE_1__ Str ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DEBUG_COLUMN_NAMES ; 
 int DEBUG_DIFF_SQL ; 
 scalar_t__ SQLITE_ROW ; 
 char** columnNames (char*,char const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * db_prepare (char*,char const*,...) ; 
 int /*<<< orphan*/  dump_table (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_5__ g ; 
 int /*<<< orphan*/  namelistFree (char**) ; 
 int /*<<< orphan*/  printQuoted (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* safeId (char const*) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_stricmp (char*,char*) ; 
 scalar_t__ sqlite3_table_column_metadata (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strFree (TYPE_1__*) ; 
 int /*<<< orphan*/  strInit (TYPE_1__*) ; 
 int /*<<< orphan*/  strPrintf (TYPE_1__*,char*,...) ; 

__attribute__((used)) static void diff_one_table(const char *zTab, FILE *out){
  char *zId = safeId(zTab); /* Name of table (translated for us in SQL) */
  char **az = 0;            /* Columns in main */
  char **az2 = 0;           /* Columns in aux */
  int nPk;                  /* Primary key columns in main */
  int nPk2;                 /* Primary key columns in aux */
  int n = 0;                /* Number of columns in main */
  int n2;                   /* Number of columns in aux */
  int nQ;                   /* Number of output columns in the diff query */
  int i;                    /* Loop counter */
  const char *zSep;         /* Separator string */
  Str sql;                  /* Comparison query */
  sqlite3_stmt *pStmt;      /* Query statement to do the diff */

  strInit(&sql);
  if( g.fDebug==DEBUG_COLUMN_NAMES ){
    /* Simply run columnNames() on all tables of the origin
    ** database and show the results.  This is used for testing
    ** and debugging of the columnNames() function.
    */
    az = columnNames("aux",zTab, &nPk, 0);
    if( az==0 ){
      printf("Rowid not accessible for %s\n", zId);
    }else{
      printf("%s:", zId);
      for(i=0; az[i]; i++){
        printf(" %s", az[i]);
        if( i+1==nPk ) printf(" *");
      }
      printf("\n");
    }
    goto end_diff_one_table;
  }
    

  if( sqlite3_table_column_metadata(g.db,"aux",zTab,0,0,0,0,0,0) ){
    if( !sqlite3_table_column_metadata(g.db,"main",zTab,0,0,0,0,0,0) ){
      /* Table missing from second database. */
      fprintf(out, "DROP TABLE %s;\n", zId);
    }
    goto end_diff_one_table;
  }

  if( sqlite3_table_column_metadata(g.db,"main",zTab,0,0,0,0,0,0) ){
    /* Table missing from source */
    dump_table(zTab, out);
    goto end_diff_one_table;
  }

  az = columnNames("main", zTab, &nPk, 0);
  az2 = columnNames("aux", zTab, &nPk2, 0);
  if( az && az2 ){
    for(n=0; az[n] && az2[n]; n++){
      if( sqlite3_stricmp(az[n],az2[n])!=0 ) break;
    }
  }
  if( az==0
   || az2==0
   || nPk!=nPk2
   || az[n]
  ){
    /* Schema mismatch */
    fprintf(out, "DROP TABLE %s; -- due to schema mismatch\n", zId);
    dump_table(zTab, out);
    goto end_diff_one_table;
  }

  /* Build the comparison query */
  for(n2=n; az2[n2]; n2++){
    fprintf(out, "ALTER TABLE %s ADD COLUMN %s;\n", zId, safeId(az2[n2]));
  }
  nQ = nPk2+1+2*(n2-nPk2);
  if( n2>nPk2 ){
    zSep = "SELECT ";
    for(i=0; i<nPk; i++){
      strPrintf(&sql, "%sB.%s", zSep, az[i]);
      zSep = ", ";
    }
    strPrintf(&sql, ", 1%s -- changed row\n", nPk==n ? "" : ",");
    while( az[i] ){
      strPrintf(&sql, "       A.%s IS NOT B.%s, B.%s%s\n",
                az[i], az2[i], az2[i], az2[i+1]==0 ? "" : ",");
      i++;
    }
    while( az2[i] ){
      strPrintf(&sql, "       B.%s IS NOT NULL, B.%s%s\n",
                az2[i], az2[i], az2[i+1]==0 ? "" : ",");
      i++;
    }
    strPrintf(&sql, "  FROM main.%s A, aux.%s B\n", zId, zId);
    zSep = " WHERE";
    for(i=0; i<nPk; i++){
      strPrintf(&sql, "%s A.%s=B.%s", zSep, az[i], az[i]);
      zSep = " AND";
    }
    zSep = "\n   AND (";
    while( az[i] ){
      strPrintf(&sql, "%sA.%s IS NOT B.%s%s\n",
                zSep, az[i], az2[i], az2[i+1]==0 ? ")" : "");
      zSep = "        OR ";
      i++;
    }
    while( az2[i] ){
      strPrintf(&sql, "%sB.%s IS NOT NULL%s\n",
                zSep, az2[i], az2[i+1]==0 ? ")" : "");
      zSep = "        OR ";
      i++;
    }
    strPrintf(&sql, " UNION ALL\n");
  }
  zSep = "SELECT ";
  for(i=0; i<nPk; i++){
    strPrintf(&sql, "%sA.%s", zSep, az[i]);
    zSep = ", ";
  }
  strPrintf(&sql, ", 2%s -- deleted row\n", nPk==n ? "" : ",");
  while( az2[i] ){
    strPrintf(&sql, "       NULL, NULL%s\n", i==n2-1 ? "" : ",");
    i++;
  }
  strPrintf(&sql, "  FROM main.%s A\n", zId);
  strPrintf(&sql, " WHERE NOT EXISTS(SELECT 1 FROM aux.%s B\n", zId);
  zSep =          "                   WHERE";
  for(i=0; i<nPk; i++){
    strPrintf(&sql, "%s A.%s=B.%s", zSep, az[i], az[i]);
    zSep = " AND";
  }
  strPrintf(&sql, ")\n");
  zSep = " UNION ALL\nSELECT ";
  for(i=0; i<nPk; i++){
    strPrintf(&sql, "%sB.%s", zSep, az[i]);
    zSep = ", ";
  }
  strPrintf(&sql, ", 3%s -- inserted row\n", nPk==n ? "" : ",");
  while( az2[i] ){
    strPrintf(&sql, "       1, B.%s%s\n", az2[i], az2[i+1]==0 ? "" : ",");
    i++;
  }
  strPrintf(&sql, "  FROM aux.%s B\n", zId);
  strPrintf(&sql, " WHERE NOT EXISTS(SELECT 1 FROM main.%s A\n", zId);
  zSep =          "                   WHERE";
  for(i=0; i<nPk; i++){
    strPrintf(&sql, "%s A.%s=B.%s", zSep, az[i], az[i]);
    zSep = " AND";
  }
  strPrintf(&sql, ")\n ORDER BY");
  zSep = " ";
  for(i=1; i<=nPk; i++){
    strPrintf(&sql, "%s%d", zSep, i);
    zSep = ", ";
  }
  strPrintf(&sql, ";\n");

  if( g.fDebug & DEBUG_DIFF_SQL ){ 
    printf("SQL for %s:\n%s\n", zId, sql.z);
    goto end_diff_one_table;
  }

  /* Drop indexes that are missing in the destination */
  pStmt = db_prepare(
    "SELECT name FROM main.sqlite_master"
    " WHERE type='index' AND tbl_name=%Q"
    "   AND sql IS NOT NULL"
    "   AND sql NOT IN (SELECT sql FROM aux.sqlite_master"
    "                    WHERE type='index' AND tbl_name=%Q"
    "                      AND sql IS NOT NULL)",
    zTab, zTab);
  while( SQLITE_ROW==sqlite3_step(pStmt) ){
    char *z = safeId((const char*)sqlite3_column_text(pStmt,0));
    fprintf(out, "DROP INDEX %s;\n", z);
    sqlite3_free(z);
  }
  sqlite3_finalize(pStmt);

  /* Run the query and output differences */
  if( !g.bSchemaOnly ){
    pStmt = db_prepare("%s", sql.z);
    while( SQLITE_ROW==sqlite3_step(pStmt) ){
      int iType = sqlite3_column_int(pStmt, nPk);
      if( iType==1 || iType==2 ){
        if( iType==1 ){       /* Change the content of a row */
          fprintf(out, "UPDATE %s", zId);
          zSep = " SET";
          for(i=nPk+1; i<nQ; i+=2){
            if( sqlite3_column_int(pStmt,i)==0 ) continue;
            fprintf(out, "%s %s=", zSep, az2[(i+nPk-1)/2]);
            zSep = ",";
            printQuoted(out, sqlite3_column_value(pStmt,i+1));
          }
        }else{                /* Delete a row */
          fprintf(out, "DELETE FROM %s", zId);
        }
        zSep = " WHERE";
        for(i=0; i<nPk; i++){
          fprintf(out, "%s %s=", zSep, az2[i]);
          printQuoted(out, sqlite3_column_value(pStmt,i));
          zSep = " AND";
        }
        fprintf(out, ";\n");
      }else{                  /* Insert a row */
        fprintf(out, "INSERT INTO %s(%s", zId, az2[0]);
        for(i=1; az2[i]; i++) fprintf(out, ",%s", az2[i]);
        fprintf(out, ") VALUES");
        zSep = "(";
        for(i=0; i<nPk2; i++){
          fprintf(out, "%s", zSep);
          zSep = ",";
          printQuoted(out, sqlite3_column_value(pStmt,i));
        }
        for(i=nPk2+2; i<nQ; i+=2){
          fprintf(out, ",");
          printQuoted(out, sqlite3_column_value(pStmt,i));
        }
        fprintf(out, ");\n");
      }
    }
    sqlite3_finalize(pStmt);
  } /* endif !g.bSchemaOnly */

  /* Create indexes that are missing in the source */
  pStmt = db_prepare(
    "SELECT sql FROM aux.sqlite_master"
    " WHERE type='index' AND tbl_name=%Q"
    "   AND sql IS NOT NULL"
    "   AND sql NOT IN (SELECT sql FROM main.sqlite_master"
    "                    WHERE type='index' AND tbl_name=%Q"
    "                      AND sql IS NOT NULL)",
    zTab, zTab);
  while( SQLITE_ROW==sqlite3_step(pStmt) ){
    fprintf(out, "%s;\n", sqlite3_column_text(pStmt,0));
  }
  sqlite3_finalize(pStmt);

end_diff_one_table:
  strFree(&sql);
  sqlite3_free(zId);
  namelistFree(az);
  namelistFree(az2);
  return;
}