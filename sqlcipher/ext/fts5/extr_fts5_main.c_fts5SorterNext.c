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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {TYPE_1__* pSorter; } ;
struct TYPE_6__ {int nIdx; int* aIdx; int /*<<< orphan*/  const* aPoslist; int /*<<< orphan*/  pStmt; int /*<<< orphan*/  iRowid; } ;
typedef  TYPE_1__ Fts5Sorter ;
typedef  TYPE_2__ Fts5Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  CsrFlagSet (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_EOF ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  fts5CsrNewrow (TYPE_2__*) ; 
 int /*<<< orphan*/  fts5GetVarint32 (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * sqlite3_column_blob (int /*<<< orphan*/ ,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5SorterNext(Fts5Cursor *pCsr){
  Fts5Sorter *pSorter = pCsr->pSorter;
  int rc;

  rc = sqlite3_step(pSorter->pStmt);
  if( rc==SQLITE_DONE ){
    rc = SQLITE_OK;
    CsrFlagSet(pCsr, FTS5CSR_EOF);
  }else if( rc==SQLITE_ROW ){
    const u8 *a;
    const u8 *aBlob;
    int nBlob;
    int i;
    int iOff = 0;
    rc = SQLITE_OK;

    pSorter->iRowid = sqlite3_column_int64(pSorter->pStmt, 0);
    nBlob = sqlite3_column_bytes(pSorter->pStmt, 1);
    aBlob = a = sqlite3_column_blob(pSorter->pStmt, 1);

    /* nBlob==0 in detail=none mode. */
    if( nBlob>0 ){
      for(i=0; i<(pSorter->nIdx-1); i++){
        int iVal;
        a += fts5GetVarint32(a, iVal);
        iOff += iVal;
        pSorter->aIdx[i] = iOff;
      }
      pSorter->aIdx[i] = &aBlob[nBlob] - a;
      pSorter->aPoslist = a;
    }

    fts5CsrNewrow(pCsr);
  }

  return rc;
}