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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3Fts3ErrMsg (char**,char*,int /*<<< orphan*/ ) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 char* sqlite3_column_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 
 char* sqlite3_mprintf (char*,char const*,char const*) ; 
 int sqlite3_prepare (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int fts3ContentColumns(
  sqlite3 *db,                    /* Database handle */
  const char *zDb,                /* Name of db (i.e. "main", "temp" etc.) */
  const char *zTbl,               /* Name of content table */
  const char ***pazCol,           /* OUT: Malloc'd array of column names */
  int *pnCol,                     /* OUT: Size of array *pazCol */
  int *pnStr,                     /* OUT: Bytes of string content */
  char **pzErr                    /* OUT: error message */
){
  int rc = SQLITE_OK;             /* Return code */
  char *zSql;                     /* "SELECT *" statement on zTbl */  
  sqlite3_stmt *pStmt = 0;        /* Compiled version of zSql */

  zSql = sqlite3_mprintf("SELECT * FROM %Q.%Q", zDb, zTbl);
  if( !zSql ){
    rc = SQLITE_NOMEM;
  }else{
    rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
    if( rc!=SQLITE_OK ){
      sqlite3Fts3ErrMsg(pzErr, "%s", sqlite3_errmsg(db));
    }
  }
  sqlite3_free(zSql);

  if( rc==SQLITE_OK ){
    const char **azCol;           /* Output array */
    sqlite3_int64 nStr = 0;       /* Size of all column names (incl. 0x00) */
    int nCol;                     /* Number of table columns */
    int i;                        /* Used to iterate through columns */

    /* Loop through the returned columns. Set nStr to the number of bytes of
    ** space required to store a copy of each column name, including the
    ** nul-terminator byte.  */
    nCol = sqlite3_column_count(pStmt);
    for(i=0; i<nCol; i++){
      const char *zCol = sqlite3_column_name(pStmt, i);
      nStr += strlen(zCol) + 1;
    }

    /* Allocate and populate the array to return. */
    azCol = (const char **)sqlite3_malloc64(sizeof(char *) * nCol + nStr);
    if( azCol==0 ){
      rc = SQLITE_NOMEM;
    }else{
      char *p = (char *)&azCol[nCol];
      for(i=0; i<nCol; i++){
        const char *zCol = sqlite3_column_name(pStmt, i);
        int n = (int)strlen(zCol)+1;
        memcpy(p, zCol, n);
        azCol[i] = p;
        p += n;
      }
    }
    sqlite3_finalize(pStmt);

    /* Set the output variables. */
    *pnCol = nCol;
    *pnStr = nStr;
    *pazCol = azCol;
  }

  return rc;
}