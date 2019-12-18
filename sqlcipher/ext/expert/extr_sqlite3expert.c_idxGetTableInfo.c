#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {char* zName; char* zColl; int /*<<< orphan*/  iPk; } ;
struct TYPE_6__ {int nCol; char* zName; TYPE_2__* aCol; } ;
typedef  TYPE_1__ IdxTable ;
typedef  TYPE_2__ IdxColumn ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int STRLEN (char const*) ; 
 int /*<<< orphan*/  idxFinalize (int*,int /*<<< orphan*/ *) ; 
 TYPE_1__* idxMalloc (int*,int) ; 
 int idxPrintfPrepareStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char**,char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int sqlite3_table_column_metadata (int /*<<< orphan*/ *,char*,char const*,char const*,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int idxGetTableInfo(
  sqlite3 *db,                    /* Database connection to read details from */
  const char *zTab,               /* Table name */
  IdxTable **ppOut,               /* OUT: New object (if successful) */
  char **pzErrmsg                 /* OUT: Error message (if not) */
){
  sqlite3_stmt *p1 = 0;
  int nCol = 0;
  int nTab = STRLEN(zTab);
  int nByte = sizeof(IdxTable) + nTab + 1;
  IdxTable *pNew = 0;
  int rc, rc2;
  char *pCsr = 0;

  rc = idxPrintfPrepareStmt(db, &p1, pzErrmsg, "PRAGMA table_info=%Q", zTab);
  while( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(p1) ){
    const char *zCol = (const char*)sqlite3_column_text(p1, 1);
    nByte += 1 + STRLEN(zCol);
    rc = sqlite3_table_column_metadata(
        db, "main", zTab, zCol, 0, &zCol, 0, 0, 0
    );
    nByte += 1 + STRLEN(zCol);
    nCol++;
  }
  rc2 = sqlite3_reset(p1);
  if( rc==SQLITE_OK ) rc = rc2;

  nByte += sizeof(IdxColumn) * nCol;
  if( rc==SQLITE_OK ){
    pNew = idxMalloc(&rc, nByte);
  }
  if( rc==SQLITE_OK ){
    pNew->aCol = (IdxColumn*)&pNew[1];
    pNew->nCol = nCol;
    pCsr = (char*)&pNew->aCol[nCol];
  }

  nCol = 0;
  while( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(p1) ){
    const char *zCol = (const char*)sqlite3_column_text(p1, 1);
    int nCopy = STRLEN(zCol) + 1;
    pNew->aCol[nCol].zName = pCsr;
    pNew->aCol[nCol].iPk = sqlite3_column_int(p1, 5);
    memcpy(pCsr, zCol, nCopy);
    pCsr += nCopy;

    rc = sqlite3_table_column_metadata(
        db, "main", zTab, zCol, 0, &zCol, 0, 0, 0
    );
    if( rc==SQLITE_OK ){
      nCopy = STRLEN(zCol) + 1;
      pNew->aCol[nCol].zColl = pCsr;
      memcpy(pCsr, zCol, nCopy);
      pCsr += nCopy;
    }

    nCol++;
  }
  idxFinalize(&rc, p1);

  if( rc!=SQLITE_OK ){
    sqlite3_free(pNew);
    pNew = 0;
  }else{
    pNew->zName = pCsr;
    memcpy(pNew->zName, zTab, nTab+1);
  }

  *ppOut = pNew;
  return rc;
}