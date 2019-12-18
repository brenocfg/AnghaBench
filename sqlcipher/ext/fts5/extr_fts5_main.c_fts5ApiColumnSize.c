#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_14__ {scalar_t__ zContent; int nCol; scalar_t__* abUnindexed; scalar_t__ bColumnsize; } ;
struct TYPE_10__ {scalar_t__ pVtab; } ;
struct TYPE_13__ {int* aColumnSize; TYPE_1__ base; } ;
struct TYPE_11__ {TYPE_5__* pConfig; } ;
struct TYPE_12__ {int /*<<< orphan*/  pStorage; TYPE_2__ p; } ;
typedef  TYPE_3__ Fts5FullTable ;
typedef  TYPE_4__ Fts5Cursor ;
typedef  int /*<<< orphan*/  Fts5Context ;
typedef  TYPE_5__ Fts5Config ;

/* Variables and functions */
 int /*<<< orphan*/  CsrFlagClear (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CsrFlagTest (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_REQUIRE_DOCSIZE ; 
 int /*<<< orphan*/  FTS5_TOKENIZE_AUX ; 
 int SQLITE_OK ; 
 int SQLITE_RANGE ; 
 int fts5ApiColumnText (int /*<<< orphan*/ *,int,char const**,int*) ; 
 int /*<<< orphan*/  fts5ColumnSizeCb ; 
 int /*<<< orphan*/  fts5CursorRowid (TYPE_4__*) ; 
 int sqlite3Fts5StorageDocsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sqlite3Fts5Tokenize (TYPE_5__*,int /*<<< orphan*/ ,char const*,int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5ApiColumnSize(Fts5Context *pCtx, int iCol, int *pnToken){
  Fts5Cursor *pCsr = (Fts5Cursor*)pCtx;
  Fts5FullTable *pTab = (Fts5FullTable*)(pCsr->base.pVtab);
  Fts5Config *pConfig = pTab->p.pConfig;
  int rc = SQLITE_OK;

  if( CsrFlagTest(pCsr, FTS5CSR_REQUIRE_DOCSIZE) ){
    if( pConfig->bColumnsize ){
      i64 iRowid = fts5CursorRowid(pCsr);
      rc = sqlite3Fts5StorageDocsize(pTab->pStorage, iRowid, pCsr->aColumnSize);
    }else if( pConfig->zContent==0 ){
      int i;
      for(i=0; i<pConfig->nCol; i++){
        if( pConfig->abUnindexed[i]==0 ){
          pCsr->aColumnSize[i] = -1;
        }
      }
    }else{
      int i;
      for(i=0; rc==SQLITE_OK && i<pConfig->nCol; i++){
        if( pConfig->abUnindexed[i]==0 ){
          const char *z; int n;
          void *p = (void*)(&pCsr->aColumnSize[i]);
          pCsr->aColumnSize[i] = 0;
          rc = fts5ApiColumnText(pCtx, i, &z, &n);
          if( rc==SQLITE_OK ){
            rc = sqlite3Fts5Tokenize(
                pConfig, FTS5_TOKENIZE_AUX, z, n, p, fts5ColumnSizeCb
            );
          }
        }
      }
    }
    CsrFlagClear(pCsr, FTS5CSR_REQUIRE_DOCSIZE);
  }
  if( iCol<0 ){
    int i;
    *pnToken = 0;
    for(i=0; i<pConfig->nCol; i++){
      *pnToken += pCsr->aColumnSize[i];
    }
  }else if( iCol<pConfig->nCol ){
    *pnToken = pCsr->aColumnSize[iCol];
  }else{
    *pnToken = 0;
    rc = SQLITE_RANGE;
  }
  return rc;
}