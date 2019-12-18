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
struct sqlite3_index_constraint {scalar_t__ usable; scalar_t__ op; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_7__ {int nConstraint; int idxNum; int nOrderBy; int orderByConsumed; double estimatedCost; TYPE_2__* aOrderBy; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_3__ sqlite3_index_info ;
struct TYPE_6__ {scalar_t__ desc; } ;
struct TYPE_5__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ SQLITE_INDEX_CONSTRAINT_GE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_GT ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LT ; 
 int SQLITE_OK ; 

__attribute__((used)) static int wholenumberBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  int i;
  int idxNum = 0;
  int argvIdx = 1;
  int ltIdx = -1;
  int gtIdx = -1;
  const struct sqlite3_index_constraint *pConstraint;
  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    if( pConstraint->usable==0 ) continue;
    if( (idxNum & 3)==0 && pConstraint->op==SQLITE_INDEX_CONSTRAINT_GT ){
      idxNum |= 1;
      ltIdx = i;
    }
    if( (idxNum & 3)==0 && pConstraint->op==SQLITE_INDEX_CONSTRAINT_GE ){
      idxNum |= 2;
      ltIdx = i;
    }
    if( (idxNum & 12)==0 && pConstraint->op==SQLITE_INDEX_CONSTRAINT_LT ){
      idxNum |= 4;
      gtIdx = i;
    }
    if( (idxNum & 12)==0 && pConstraint->op==SQLITE_INDEX_CONSTRAINT_LE ){
      idxNum |= 8;
      gtIdx = i;
    }
  }
  pIdxInfo->idxNum = idxNum;
  if( ltIdx>=0 ){
    pIdxInfo->aConstraintUsage[ltIdx].argvIndex = argvIdx++;
    pIdxInfo->aConstraintUsage[ltIdx].omit = 1;
  }
  if( gtIdx>=0 ){
    pIdxInfo->aConstraintUsage[gtIdx].argvIndex = argvIdx;
    pIdxInfo->aConstraintUsage[gtIdx].omit = 1;
  }
  if( pIdxInfo->nOrderBy==1
   && pIdxInfo->aOrderBy[0].desc==0
  ){
    pIdxInfo->orderByConsumed = 1;
  }
  if( (idxNum & 12)==0 ){
    pIdxInfo->estimatedCost = (double)100000000;
  }else if( (idxNum & 3)==0 ){
    pIdxInfo->estimatedCost = (double)5;
  }else{
    pIdxInfo->estimatedCost = (double)1;
  }
  return SQLITE_OK;
}