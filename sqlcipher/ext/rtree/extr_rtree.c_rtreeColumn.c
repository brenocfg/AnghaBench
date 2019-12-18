#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ pVtab; } ;
typedef  TYPE_1__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_17__ {int nDim2; scalar_t__ eCoordType; int /*<<< orphan*/  zReadAuxSql; int /*<<< orphan*/  db; } ;
struct TYPE_16__ {int /*<<< orphan*/  i; int /*<<< orphan*/  f; } ;
struct TYPE_15__ {int bAuxValid; scalar_t__ pReadAux; } ;
struct TYPE_14__ {int /*<<< orphan*/  iCell; } ;
typedef  TYPE_2__ RtreeSearchPoint ;
typedef  int /*<<< orphan*/  RtreeNode ;
typedef  TYPE_3__ RtreeCursor ;
typedef  TYPE_4__ RtreeCoord ;
typedef  TYPE_5__ Rtree ;

/* Variables and functions */
 scalar_t__ RTREE_COORD_INT32 ; 
 scalar_t__ RTREE_COORD_REAL32 ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nodeGetCoord (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 int /*<<< orphan*/  nodeGetRowid (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtreeNodeOfFirstSearchPoint (TYPE_3__*,int*) ; 
 TYPE_2__* rtreeSearchPointFirst (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_value (scalar_t__,int) ; 
 int sqlite3_prepare_v3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_step (scalar_t__) ; 

__attribute__((used)) static int rtreeColumn(sqlite3_vtab_cursor *cur, sqlite3_context *ctx, int i){
  Rtree *pRtree = (Rtree *)cur->pVtab;
  RtreeCursor *pCsr = (RtreeCursor *)cur;
  RtreeSearchPoint *p = rtreeSearchPointFirst(pCsr);
  RtreeCoord c;
  int rc = SQLITE_OK;
  RtreeNode *pNode = rtreeNodeOfFirstSearchPoint(pCsr, &rc);

  if( rc ) return rc;
  if( p==0 ) return SQLITE_OK;
  if( i==0 ){
    sqlite3_result_int64(ctx, nodeGetRowid(pRtree, pNode, p->iCell));
  }else if( i<=pRtree->nDim2 ){
    nodeGetCoord(pRtree, pNode, p->iCell, i-1, &c);
#ifndef SQLITE_RTREE_INT_ONLY
    if( pRtree->eCoordType==RTREE_COORD_REAL32 ){
      sqlite3_result_double(ctx, c.f);
    }else
#endif
    {
      assert( pRtree->eCoordType==RTREE_COORD_INT32 );
      sqlite3_result_int(ctx, c.i);
    }
  }else{
    if( !pCsr->bAuxValid ){
      if( pCsr->pReadAux==0 ){
        rc = sqlite3_prepare_v3(pRtree->db, pRtree->zReadAuxSql, -1, 0,
                                &pCsr->pReadAux, 0);
        if( rc ) return rc;
      }
      sqlite3_bind_int64(pCsr->pReadAux, 1, 
          nodeGetRowid(pRtree, pNode, p->iCell));
      rc = sqlite3_step(pCsr->pReadAux);
      if( rc==SQLITE_ROW ){
        pCsr->bAuxValid = 1;
      }else{
        sqlite3_reset(pCsr->pReadAux);
        if( rc==SQLITE_DONE ) rc = SQLITE_OK;
        return rc;
      }
    }
    sqlite3_result_value(ctx,
         sqlite3_column_value(pCsr->pReadAux, i - pRtree->nDim2 + 1));
  }  
  return SQLITE_OK;
}