#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_9__ {int nOrderBy; int orderByConsumed; int nConstraint; int estimatedCost; TYPE_3__* aConstraintUsage; scalar_t__ idxNum; TYPE_2__* aConstraint; TYPE_1__* aOrderBy; } ;
typedef  TYPE_4__ sqlite3_index_info ;
struct TYPE_8__ {int /*<<< orphan*/  argvIndex; } ;
struct TYPE_7__ {int op; int iColumn; scalar_t__ usable; } ;
struct TYPE_6__ {scalar_t__ iColumn; scalar_t__ desc; } ;

/* Variables and functions */
 scalar_t__ FTS4AUX_EQ_CONSTRAINT ; 
 scalar_t__ FTS4AUX_GE_CONSTRAINT ; 
 scalar_t__ FTS4AUX_LE_CONSTRAINT ; 
 int SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_INDEX_CONSTRAINT_GE ; 
 int SQLITE_INDEX_CONSTRAINT_GT ; 
 int SQLITE_INDEX_CONSTRAINT_LE ; 
 int SQLITE_INDEX_CONSTRAINT_LT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3auxBestIndexMethod(
  sqlite3_vtab *pVTab, 
  sqlite3_index_info *pInfo
){
  int i;
  int iEq = -1;
  int iGe = -1;
  int iLe = -1;
  int iLangid = -1;
  int iNext = 1;                  /* Next free argvIndex value */

  UNUSED_PARAMETER(pVTab);

  /* This vtab delivers always results in "ORDER BY term ASC" order. */
  if( pInfo->nOrderBy==1 
   && pInfo->aOrderBy[0].iColumn==0 
   && pInfo->aOrderBy[0].desc==0
  ){
    pInfo->orderByConsumed = 1;
  }

  /* Search for equality and range constraints on the "term" column. 
  ** And equality constraints on the hidden "languageid" column. */
  for(i=0; i<pInfo->nConstraint; i++){
    if( pInfo->aConstraint[i].usable ){
      int op = pInfo->aConstraint[i].op;
      int iCol = pInfo->aConstraint[i].iColumn;

      if( iCol==0 ){
        if( op==SQLITE_INDEX_CONSTRAINT_EQ ) iEq = i;
        if( op==SQLITE_INDEX_CONSTRAINT_LT ) iLe = i;
        if( op==SQLITE_INDEX_CONSTRAINT_LE ) iLe = i;
        if( op==SQLITE_INDEX_CONSTRAINT_GT ) iGe = i;
        if( op==SQLITE_INDEX_CONSTRAINT_GE ) iGe = i;
      }
      if( iCol==4 ){
        if( op==SQLITE_INDEX_CONSTRAINT_EQ ) iLangid = i;
      }
    }
  }

  if( iEq>=0 ){
    pInfo->idxNum = FTS4AUX_EQ_CONSTRAINT;
    pInfo->aConstraintUsage[iEq].argvIndex = iNext++;
    pInfo->estimatedCost = 5;
  }else{
    pInfo->idxNum = 0;
    pInfo->estimatedCost = 20000;
    if( iGe>=0 ){
      pInfo->idxNum += FTS4AUX_GE_CONSTRAINT;
      pInfo->aConstraintUsage[iGe].argvIndex = iNext++;
      pInfo->estimatedCost /= 2;
    }
    if( iLe>=0 ){
      pInfo->idxNum += FTS4AUX_LE_CONSTRAINT;
      pInfo->aConstraintUsage[iLe].argvIndex = iNext++;
      pInfo->estimatedCost /= 2;
    }
  }
  if( iLangid>=0 ){
    pInfo->aConstraintUsage[iLangid].argvIndex = iNext++;
    pInfo->estimatedCost--;
  }

  return SQLITE_OK;
}