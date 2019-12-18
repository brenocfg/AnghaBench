#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  r ;
struct TYPE_10__ {int writableSchema; int rc; int /*<<< orphan*/  pArg; int /*<<< orphan*/  (* xCallback ) (char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  nErr; int /*<<< orphan*/  db; } ;
struct TYPE_9__ {char* z; } ;
typedef  TYPE_1__ DText ;
typedef  TYPE_2__ DState ;

/* Variables and functions */
#define  SQLITE_BLOB 132 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  appendText (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeColumnList (char**) ; 
 int /*<<< orphan*/  freeText (TYPE_1__*) ; 
 int /*<<< orphan*/  initText (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int*,double*,int) ; 
 int /*<<< orphan*/  output_formatted (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  output_quoted_escaped_string (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  quoteChar (char const*) ; 
 scalar_t__ sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 double sqlite3_column_double (int /*<<< orphan*/ *,int) ; 
 double sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_strglob (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (char*,int /*<<< orphan*/ ) ; 
 char** tableColumnList (TYPE_2__*,char const*) ; 

__attribute__((used)) static int dump_callback(void *pArg, int nArg, char **azArg, char **azCol){
  int rc;
  const char *zTable;
  const char *zType;
  const char *zSql;
  DState *p = (DState*)pArg;
  sqlite3_stmt *pStmt;

  (void)azCol;
  if( nArg!=3 ) return 1;
  zTable = azArg[0];
  zType = azArg[1];
  zSql = azArg[2];

  if( strcmp(zTable, "sqlite_sequence")==0 ){
    p->xCallback("DELETE FROM sqlite_sequence;\n", p->pArg);
  }else if( sqlite3_strglob("sqlite_stat?", zTable)==0 ){
    p->xCallback("ANALYZE sqlite_master;\n", p->pArg);
  }else if( strncmp(zTable, "sqlite_", 7)==0 ){
    return 0;
  }else if( strncmp(zSql, "CREATE VIRTUAL TABLE", 20)==0 ){
    if( !p->writableSchema ){
      p->xCallback("PRAGMA writable_schema=ON;\n", p->pArg);
      p->writableSchema = 1;
    }
    output_formatted(p,
       "INSERT INTO sqlite_master(type,name,tbl_name,rootpage,sql)"
       "VALUES('table','%q','%q',0,'%q');",
       zTable, zTable, zSql);
    return 0;
  }else{
    if( sqlite3_strglob("CREATE TABLE ['\"]*", zSql)==0 ){
      p->xCallback("CREATE TABLE IF NOT EXISTS ", p->pArg);
      p->xCallback(zSql+13, p->pArg);
    }else{
      p->xCallback(zSql, p->pArg);
    }
    p->xCallback(";\n", p->pArg);
  }

  if( strcmp(zType, "table")==0 ){
    DText sSelect;
    DText sTable;
    char **azTCol;
    int i;
    int nCol;

    azTCol = tableColumnList(p, zTable);
    if( azTCol==0 ) return 0;

    initText(&sTable);
    appendText(&sTable, "INSERT INTO ", 0);

    /* Always quote the table name, even if it appears to be pure ascii,
    ** in case it is a keyword. Ex:  INSERT INTO "table" ... */
    appendText(&sTable, zTable, quoteChar(zTable));

    /* If preserving the rowid, add a column list after the table name.
    ** In other words:  "INSERT INTO tab(rowid,a,b,c,...) VALUES(...)"
    ** instead of the usual "INSERT INTO tab VALUES(...)".
    */
    if( azTCol[0] ){
      appendText(&sTable, "(", 0);
      appendText(&sTable, azTCol[0], 0);
      for(i=1; azTCol[i]; i++){
        appendText(&sTable, ",", 0);
        appendText(&sTable, azTCol[i], quoteChar(azTCol[i]));
      }
      appendText(&sTable, ")", 0);
    }
    appendText(&sTable, " VALUES(", 0);

    /* Build an appropriate SELECT statement */
    initText(&sSelect);
    appendText(&sSelect, "SELECT ", 0);
    if( azTCol[0] ){
      appendText(&sSelect, azTCol[0], 0);
      appendText(&sSelect, ",", 0);
    }
    for(i=1; azTCol[i]; i++){
      appendText(&sSelect, azTCol[i], quoteChar(azTCol[i]));
      if( azTCol[i+1] ){
        appendText(&sSelect, ",", 0);
      }
    }
    nCol = i;
    if( azTCol[0]==0 ) nCol--;
    freeColumnList(azTCol);
    appendText(&sSelect, " FROM ", 0);
    appendText(&sSelect, zTable, quoteChar(zTable));

    rc = sqlite3_prepare_v2(p->db, sSelect.z, -1, &pStmt, 0);
    if( rc!=SQLITE_OK ){
      p->nErr++;
      if( p->rc==SQLITE_OK ) p->rc = rc;
    }else{
      while( SQLITE_ROW==sqlite3_step(pStmt) ){
        p->xCallback(sTable.z, p->pArg);
        for(i=0; i<nCol; i++){
          if( i ) p->xCallback(",", p->pArg);
          switch( sqlite3_column_type(pStmt,i) ){
            case SQLITE_INTEGER: {
              output_formatted(p, "%lld", sqlite3_column_int64(pStmt,i));
              break;
            }
            case SQLITE_FLOAT: {
              double r = sqlite3_column_double(pStmt,i);
              sqlite3_uint64 ur;
              memcpy(&ur,&r,sizeof(r));
              if( ur==0x7ff0000000000000LL ){
                p->xCallback("1e999", p->pArg);
              }else if( ur==0xfff0000000000000LL ){
                p->xCallback("-1e999", p->pArg);
              }else{
                output_formatted(p, "%!.20g", r);
              }
              break;
            }
            case SQLITE_NULL: {
              p->xCallback("NULL", p->pArg);
              break;
            }
            case SQLITE_TEXT: {
              output_quoted_escaped_string(p, 
                   (const char*)sqlite3_column_text(pStmt,i));
              break;
            }
            case SQLITE_BLOB: {
              int nByte = sqlite3_column_bytes(pStmt,i);
              unsigned char *a = (unsigned char*)sqlite3_column_blob(pStmt,i);
              int j;
              p->xCallback("x'", p->pArg);
              for(j=0; j<nByte; j++){
                char zWord[3];
                zWord[0] = "0123456789abcdef"[(a[j]>>4)&15];
                zWord[1] = "0123456789abcdef"[a[j]&15];
                zWord[2] = 0;
                p->xCallback(zWord, p->pArg);
              }
              p->xCallback("'", p->pArg);
              break;
            }
          }
        }
        p->xCallback(");\n", p->pArg);
      }
    }
    sqlite3_finalize(pStmt);
    freeText(&sTable);
    freeText(&sSelect);
  }
  return 0;
}