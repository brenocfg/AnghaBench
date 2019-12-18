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
struct TYPE_11__ {int /*<<< orphan*/  zErrMsg; } ;
struct TYPE_12__ {size_t nSrc; TYPE_2__ base; TYPE_4__* aSrc; scalar_t__ bSwarm; } ;
typedef  TYPE_3__ UnionTab ;
struct TYPE_13__ {scalar_t__ iMin; scalar_t__ iMax; int /*<<< orphan*/  zTab; int /*<<< orphan*/  db; } ;
typedef  TYPE_4__ UnionSrc ;
struct TYPE_10__ {scalar_t__ pVtab; } ;
struct TYPE_14__ {size_t iTab; scalar_t__ iMaxRowid; int /*<<< orphan*/  pStmt; TYPE_1__ base; } ;
typedef  TYPE_5__ UnionCsr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 
 int unionFinalizeCsrStmt (TYPE_5__*) ; 
 int /*<<< orphan*/  unionIncrRefcount (TYPE_3__*,size_t) ; 
 int unionOpenDatabase (TYPE_3__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unionPreparePrintf (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int doUnionNext(UnionCsr *pCsr){
  int rc = SQLITE_OK;
  assert( pCsr->pStmt );
  if( sqlite3_step(pCsr->pStmt)!=SQLITE_ROW ){
    UnionTab *pTab = (UnionTab*)pCsr->base.pVtab;
    rc = unionFinalizeCsrStmt(pCsr);
    if( rc==SQLITE_OK && pTab->bSwarm ){
      pCsr->iTab++;
      if( pCsr->iTab<pTab->nSrc ){
        UnionSrc *pSrc = &pTab->aSrc[pCsr->iTab];
        if( pCsr->iMaxRowid>=pSrc->iMin ){
          /* It is necessary to scan the next table. */
          rc = unionOpenDatabase(pTab, pCsr->iTab, &pTab->base.zErrMsg);
          pCsr->pStmt = unionPreparePrintf(&rc, &pTab->base.zErrMsg, pSrc->db,
              "SELECT rowid, * FROM %Q %s %lld",
              pSrc->zTab,
              (pSrc->iMax>pCsr->iMaxRowid ? "WHERE _rowid_ <=" : "-- "),
              pCsr->iMaxRowid
          );
          if( rc==SQLITE_OK ){
            assert( pCsr->pStmt );
            unionIncrRefcount(pTab, pCsr->iTab);
            rc = SQLITE_ROW;
          }
        }
      }
    }
  }

  return rc;
}