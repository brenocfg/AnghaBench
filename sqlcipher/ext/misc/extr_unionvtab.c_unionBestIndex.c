#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sqlite3_index_constraint {scalar_t__ iColumn; int op; scalar_t__ usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int sqlite3_int64 ;
struct TYPE_6__ {int nConstraint; int estimatedRows; double estimatedCost; int idxNum; struct sqlite3_index_constraint* aConstraint; TYPE_1__* aConstraintUsage; int /*<<< orphan*/  idxFlags; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_7__ {scalar_t__ iPK; } ;
typedef  TYPE_3__ UnionTab ;
struct TYPE_5__ {int argvIndex; int omit; } ;

/* Variables and functions */
#define  SQLITE_INDEX_CONSTRAINT_EQ 132 
#define  SQLITE_INDEX_CONSTRAINT_GE 131 
#define  SQLITE_INDEX_CONSTRAINT_GT 130 
#define  SQLITE_INDEX_CONSTRAINT_LE 129 
#define  SQLITE_INDEX_CONSTRAINT_LT 128 
 int /*<<< orphan*/  SQLITE_INDEX_SCAN_UNIQUE ; 
 int SQLITE_OK ; 

__attribute__((used)) static int unionBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  UnionTab *pTab = (UnionTab*)tab;
  int iEq = -1;
  int iLt = -1;
  int iGt = -1;
  int i;

  for(i=0; i<pIdxInfo->nConstraint; i++){
    struct sqlite3_index_constraint *p = &pIdxInfo->aConstraint[i];
    if( p->usable && (p->iColumn<0 || p->iColumn==pTab->iPK) ){
      switch( p->op ){
        case SQLITE_INDEX_CONSTRAINT_EQ:
          iEq = i;
          break;
        case SQLITE_INDEX_CONSTRAINT_LE:
        case SQLITE_INDEX_CONSTRAINT_LT:
          iLt = i;
          break;
        case SQLITE_INDEX_CONSTRAINT_GE:
        case SQLITE_INDEX_CONSTRAINT_GT:
          iGt = i;
          break;
      }
    }
  }

  if( iEq>=0 ){
    pIdxInfo->estimatedRows = 1;
    pIdxInfo->idxFlags = SQLITE_INDEX_SCAN_UNIQUE;
    pIdxInfo->estimatedCost = 3.0;
    pIdxInfo->idxNum = SQLITE_INDEX_CONSTRAINT_EQ;
    pIdxInfo->aConstraintUsage[iEq].argvIndex = 1;
    pIdxInfo->aConstraintUsage[iEq].omit = 1;
  }else{
    int iCons = 1;
    int idxNum = 0;
    sqlite3_int64 nRow = 1000000;
    if( iLt>=0 ){
      nRow = nRow / 2;
      pIdxInfo->aConstraintUsage[iLt].argvIndex = iCons++;
      pIdxInfo->aConstraintUsage[iLt].omit = 1;
      idxNum |= pIdxInfo->aConstraint[iLt].op;
    }
    if( iGt>=0 ){
      nRow = nRow / 2;
      pIdxInfo->aConstraintUsage[iGt].argvIndex = iCons++;
      pIdxInfo->aConstraintUsage[iGt].omit = 1;
      idxNum |= pIdxInfo->aConstraint[iGt].op;
    }
    pIdxInfo->estimatedRows = nRow;
    pIdxInfo->estimatedCost = 3.0 * (double)nRow;
    pIdxInfo->idxNum = idxNum;
  }

  return SQLITE_OK;
}