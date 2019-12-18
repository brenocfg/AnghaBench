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
struct sqlite3_index_constraint {int iColumn; scalar_t__ op; scalar_t__ usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_7__ {int nConstraint; int idxNum; int nOrderBy; int orderByConsumed; double estimatedCost; TYPE_2__* aOrderBy; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_3__ sqlite3_index_info ;
struct TYPE_6__ {int iColumn; scalar_t__ desc; } ;
struct TYPE_5__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LT ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_MATCH ; 
 int SQLITE_OK ; 

__attribute__((used)) static int fuzzerBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  int iPlan = 0;
  int iDistTerm = -1;
  int iRulesetTerm = -1;
  int i;
  int seenMatch = 0;
  const struct sqlite3_index_constraint *pConstraint;
  double rCost = 1e12;

  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    if( pConstraint->iColumn==0
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_MATCH ){
      seenMatch = 1;
    }
    if( pConstraint->usable==0 ) continue;
    if( (iPlan & 1)==0 
     && pConstraint->iColumn==0
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_MATCH
    ){
      iPlan |= 1;
      pIdxInfo->aConstraintUsage[i].argvIndex = 1;
      pIdxInfo->aConstraintUsage[i].omit = 1;
      rCost /= 1e6;
    }
    if( (iPlan & 2)==0
     && pConstraint->iColumn==1
     && (pConstraint->op==SQLITE_INDEX_CONSTRAINT_LT
           || pConstraint->op==SQLITE_INDEX_CONSTRAINT_LE)
    ){
      iPlan |= 2;
      iDistTerm = i;
      rCost /= 10.0;
    }
    if( (iPlan & 4)==0
     && pConstraint->iColumn==2
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= 4;
      pIdxInfo->aConstraintUsage[i].omit = 1;
      iRulesetTerm = i;
      rCost /= 10.0;
    }
  }
  if( iPlan & 2 ){
    pIdxInfo->aConstraintUsage[iDistTerm].argvIndex = 1+((iPlan&1)!=0);
  }
  if( iPlan & 4 ){
    int idx = 1;
    if( iPlan & 1 ) idx++;
    if( iPlan & 2 ) idx++;
    pIdxInfo->aConstraintUsage[iRulesetTerm].argvIndex = idx;
  }
  pIdxInfo->idxNum = iPlan;
  if( pIdxInfo->nOrderBy==1
   && pIdxInfo->aOrderBy[0].iColumn==1
   && pIdxInfo->aOrderBy[0].desc==0
  ){
    pIdxInfo->orderByConsumed = 1;
  }
  if( seenMatch && (iPlan&1)==0 ) rCost = 1e99;
  pIdxInfo->estimatedCost = rCost;
   
  return SQLITE_OK;
}