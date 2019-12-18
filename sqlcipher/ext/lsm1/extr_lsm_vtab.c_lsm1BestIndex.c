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
struct sqlite3_index_constraint {scalar_t__ usable; scalar_t__ iColumn; int op; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; double estimatedCost; int estimatedRows; int orderByConsumed; int idxNum; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
#define  SQLITE_INDEX_CONSTRAINT_EQ 132 
#define  SQLITE_INDEX_CONSTRAINT_GE 131 
#define  SQLITE_INDEX_CONSTRAINT_GT 130 
#define  SQLITE_INDEX_CONSTRAINT_LE 129 
#define  SQLITE_INDEX_CONSTRAINT_LT 128 
 int SQLITE_OK ; 

__attribute__((used)) static int lsm1BestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  int i;                 /* Loop over constraints */
  int idxNum = 99;       /* The query plan */
  int nArg = 0;          /* Number of arguments to xFilter */
  int argIdx = -1;       /* Index of the key== constraint, or -1 if none */
  int iIdx2 = -1;        /* The index of the second key */
  int omit1 = 0;
  int omit2 = 0;

  const struct sqlite3_index_constraint *pConstraint;
  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint && idxNum<16; i++, pConstraint++){
    if( pConstraint->usable==0 ) continue;
    if( pConstraint->iColumn!=0 ) continue;
    switch( pConstraint->op ){
      case SQLITE_INDEX_CONSTRAINT_EQ: {
        if( idxNum>0 ){
          argIdx = i;
          iIdx2 = -1;
          idxNum = 0;
          omit1 = 1;
        }
        break;
      }
      case SQLITE_INDEX_CONSTRAINT_GE:
      case SQLITE_INDEX_CONSTRAINT_GT: {
        if( idxNum==99 ){
          argIdx = i;
          idxNum = 2;
          omit1 = pConstraint->op==SQLITE_INDEX_CONSTRAINT_GE;
        }else if( idxNum==3 ){
          iIdx2 = idxNum;
          omit2 = omit1;
          argIdx = i;
          idxNum = 1;
          omit1 = pConstraint->op==SQLITE_INDEX_CONSTRAINT_GE;
        }
        break;
      }
      case SQLITE_INDEX_CONSTRAINT_LE:
      case SQLITE_INDEX_CONSTRAINT_LT: {
        if( idxNum==99 ){
          argIdx = i;
          idxNum = 3;
          omit1 = pConstraint->op==SQLITE_INDEX_CONSTRAINT_LE;
        }else if( idxNum==2 ){
          iIdx2 = i;
          idxNum = 1;
          omit1 = pConstraint->op==SQLITE_INDEX_CONSTRAINT_LE;
        }
        break;
      }
    }
  }
  if( argIdx>=0 ){
    pIdxInfo->aConstraintUsage[argIdx].argvIndex = ++nArg;
    pIdxInfo->aConstraintUsage[argIdx].omit = omit1;
  }
  if( iIdx2>=0 ){
    pIdxInfo->aConstraintUsage[iIdx2].argvIndex = ++nArg;
    pIdxInfo->aConstraintUsage[iIdx2].omit = omit2;
  }
  if( idxNum==0 ){
    pIdxInfo->estimatedCost = (double)1;
    pIdxInfo->estimatedRows = 1;
    pIdxInfo->orderByConsumed = 1;
  }else if( idxNum==1 ){
    pIdxInfo->estimatedCost = (double)100;
    pIdxInfo->estimatedRows = 100;
  }else if( idxNum<99 ){
    pIdxInfo->estimatedCost = (double)5000;
    pIdxInfo->estimatedRows = 5000;
  }else{
    /* Full table scan */
    pIdxInfo->estimatedCost = (double)2147483647;
    pIdxInfo->estimatedRows = 2147483647;
  }
  pIdxInfo->idxNum = idxNum;
  return SQLITE_OK;
}