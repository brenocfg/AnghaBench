#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sqlite3_index_constraint {scalar_t__ iColumn; scalar_t__ op; int /*<<< orphan*/  usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; int idxNum; char* idxStr; double estimatedCost; int estimatedRows; TYPE_1__* aConstraintUsage; int /*<<< orphan*/  idxFlags; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_FUNCTION ; 
 int /*<<< orphan*/  SQLITE_INDEX_SCAN_UNIQUE ; 
 int SQLITE_OK ; 

__attribute__((used)) static int geopolyBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  int ii;
  int iRowidTerm = -1;
  int iFuncTerm = -1;
  int idxNum = 0;

  for(ii=0; ii<pIdxInfo->nConstraint; ii++){
    struct sqlite3_index_constraint *p = &pIdxInfo->aConstraint[ii];
    if( !p->usable ) continue;
    if( p->iColumn<0 && p->op==SQLITE_INDEX_CONSTRAINT_EQ  ){
      iRowidTerm = ii;
      break;
    }
    if( p->iColumn==0 && p->op>=SQLITE_INDEX_CONSTRAINT_FUNCTION ){
      /* p->op==SQLITE_INDEX_CONSTRAINT_FUNCTION for geopoly_overlap()
      ** p->op==(SQLITE_INDEX_CONTRAINT_FUNCTION+1) for geopoly_within().
      ** See geopolyFindFunction() */
      iFuncTerm = ii;
      idxNum = p->op - SQLITE_INDEX_CONSTRAINT_FUNCTION + 2;
    }
  }

  if( iRowidTerm>=0 ){
    pIdxInfo->idxNum = 1;
    pIdxInfo->idxStr = "rowid";
    pIdxInfo->aConstraintUsage[iRowidTerm].argvIndex = 1;
    pIdxInfo->aConstraintUsage[iRowidTerm].omit = 1;
    pIdxInfo->estimatedCost = 30.0;
    pIdxInfo->estimatedRows = 1;
    pIdxInfo->idxFlags = SQLITE_INDEX_SCAN_UNIQUE;
    return SQLITE_OK;
  }
  if( iFuncTerm>=0 ){
    pIdxInfo->idxNum = idxNum;
    pIdxInfo->idxStr = "rtree";
    pIdxInfo->aConstraintUsage[iFuncTerm].argvIndex = 1;
    pIdxInfo->aConstraintUsage[iFuncTerm].omit = 0;
    pIdxInfo->estimatedCost = 300.0;
    pIdxInfo->estimatedRows = 10;
    return SQLITE_OK;
  }
  pIdxInfo->idxNum = 4;
  pIdxInfo->idxStr = "fullscan";
  pIdxInfo->estimatedCost = 3000000.0;
  pIdxInfo->estimatedRows = 100000;
  return SQLITE_OK;
}