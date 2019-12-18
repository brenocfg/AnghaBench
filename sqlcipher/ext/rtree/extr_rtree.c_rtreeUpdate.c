#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_16__ {int nDim2; scalar_t__ eCoordType; int iReinsertHeight; int nAux; int /*<<< orphan*/ * pWriteAux; int /*<<< orphan*/  db; int /*<<< orphan*/ * pReadRowid; scalar_t__ nNodeRef; } ;
struct TYPE_15__ {scalar_t__ iRowid; TYPE_1__* aCoord; } ;
struct TYPE_14__ {scalar_t__ f; scalar_t__ i; } ;
typedef  int /*<<< orphan*/  RtreeNode ;
typedef  TYPE_2__ RtreeCell ;
typedef  TYPE_3__ Rtree ;

/* Variables and functions */
 int ChooseLeaf (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RTREE_COORD_REAL32 ; 
 int SQLITE_LOCKED_VTAB ; 
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_REPLACE ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int nodeRelease (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int rtreeConstraintError (TYPE_3__*,int) ; 
 int rtreeDeleteRowid (TYPE_3__*,scalar_t__) ; 
 int rtreeInsertCell (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int rtreeNewRowid (TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  rtreeReference (TYPE_3__*) ; 
 int /*<<< orphan*/  rtreeRelease (TYPE_3__*) ; 
 scalar_t__ rtreeValueDown (int /*<<< orphan*/ *) ; 
 scalar_t__ rtreeValueUp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_bind_value (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 void* sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_vtab_on_conflict (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtreeUpdate(
  sqlite3_vtab *pVtab, 
  int nData, 
  sqlite3_value **aData, 
  sqlite_int64 *pRowid
){
  Rtree *pRtree = (Rtree *)pVtab;
  int rc = SQLITE_OK;
  RtreeCell cell;                 /* New cell to insert if nData>1 */
  int bHaveRowid = 0;             /* Set to 1 after new rowid is determined */

  if( pRtree->nNodeRef ){
    /* Unable to write to the btree while another cursor is reading from it,
    ** since the write might do a rebalance which would disrupt the read
    ** cursor. */
    return SQLITE_LOCKED_VTAB;
  }
  rtreeReference(pRtree);
  assert(nData>=1);

  cell.iRowid = 0;  /* Used only to suppress a compiler warning */

  /* Constraint handling. A write operation on an r-tree table may return
  ** SQLITE_CONSTRAINT for two reasons:
  **
  **   1. A duplicate rowid value, or
  **   2. The supplied data violates the "x2>=x1" constraint.
  **
  ** In the first case, if the conflict-handling mode is REPLACE, then
  ** the conflicting row can be removed before proceeding. In the second
  ** case, SQLITE_CONSTRAINT must be returned regardless of the
  ** conflict-handling mode specified by the user.
  */
  if( nData>1 ){
    int ii;
    int nn = nData - 4;

    if( nn > pRtree->nDim2 ) nn = pRtree->nDim2;
    /* Populate the cell.aCoord[] array. The first coordinate is aData[3].
    **
    ** NB: nData can only be less than nDim*2+3 if the rtree is mis-declared
    ** with "column" that are interpreted as table constraints.
    ** Example:  CREATE VIRTUAL TABLE bad USING rtree(x,y,CHECK(y>5));
    ** This problem was discovered after years of use, so we silently ignore
    ** these kinds of misdeclared tables to avoid breaking any legacy.
    */

#ifndef SQLITE_RTREE_INT_ONLY
    if( pRtree->eCoordType==RTREE_COORD_REAL32 ){
      for(ii=0; ii<nn; ii+=2){
        cell.aCoord[ii].f = rtreeValueDown(aData[ii+3]);
        cell.aCoord[ii+1].f = rtreeValueUp(aData[ii+4]);
        if( cell.aCoord[ii].f>cell.aCoord[ii+1].f ){
          rc = rtreeConstraintError(pRtree, ii+1);
          goto constraint;
        }
      }
    }else
#endif
    {
      for(ii=0; ii<nn; ii+=2){
        cell.aCoord[ii].i = sqlite3_value_int(aData[ii+3]);
        cell.aCoord[ii+1].i = sqlite3_value_int(aData[ii+4]);
        if( cell.aCoord[ii].i>cell.aCoord[ii+1].i ){
          rc = rtreeConstraintError(pRtree, ii+1);
          goto constraint;
        }
      }
    }

    /* If a rowid value was supplied, check if it is already present in 
    ** the table. If so, the constraint has failed. */
    if( sqlite3_value_type(aData[2])!=SQLITE_NULL ){
      cell.iRowid = sqlite3_value_int64(aData[2]);
      if( sqlite3_value_type(aData[0])==SQLITE_NULL
       || sqlite3_value_int64(aData[0])!=cell.iRowid
      ){
        int steprc;
        sqlite3_bind_int64(pRtree->pReadRowid, 1, cell.iRowid);
        steprc = sqlite3_step(pRtree->pReadRowid);
        rc = sqlite3_reset(pRtree->pReadRowid);
        if( SQLITE_ROW==steprc ){
          if( sqlite3_vtab_on_conflict(pRtree->db)==SQLITE_REPLACE ){
            rc = rtreeDeleteRowid(pRtree, cell.iRowid);
          }else{
            rc = rtreeConstraintError(pRtree, 0);
            goto constraint;
          }
        }
      }
      bHaveRowid = 1;
    }
  }

  /* If aData[0] is not an SQL NULL value, it is the rowid of a
  ** record to delete from the r-tree table. The following block does
  ** just that.
  */
  if( sqlite3_value_type(aData[0])!=SQLITE_NULL ){
    rc = rtreeDeleteRowid(pRtree, sqlite3_value_int64(aData[0]));
  }

  /* If the aData[] array contains more than one element, elements
  ** (aData[2]..aData[argc-1]) contain a new record to insert into
  ** the r-tree structure.
  */
  if( rc==SQLITE_OK && nData>1 ){
    /* Insert the new record into the r-tree */
    RtreeNode *pLeaf = 0;

    /* Figure out the rowid of the new row. */
    if( bHaveRowid==0 ){
      rc = rtreeNewRowid(pRtree, &cell.iRowid);
    }
    *pRowid = cell.iRowid;

    if( rc==SQLITE_OK ){
      rc = ChooseLeaf(pRtree, &cell, 0, &pLeaf);
    }
    if( rc==SQLITE_OK ){
      int rc2;
      pRtree->iReinsertHeight = -1;
      rc = rtreeInsertCell(pRtree, pLeaf, &cell, 0);
      rc2 = nodeRelease(pRtree, pLeaf);
      if( rc==SQLITE_OK ){
        rc = rc2;
      }
    }
    if( rc==SQLITE_OK && pRtree->nAux ){
      sqlite3_stmt *pUp = pRtree->pWriteAux;
      int jj;
      sqlite3_bind_int64(pUp, 1, *pRowid);
      for(jj=0; jj<pRtree->nAux; jj++){
        sqlite3_bind_value(pUp, jj+2, aData[pRtree->nDim2+3+jj]);
      }
      sqlite3_step(pUp);
      rc = sqlite3_reset(pUp);
    }
  }

constraint:
  rtreeRelease(pRtree);
  return rc;
}