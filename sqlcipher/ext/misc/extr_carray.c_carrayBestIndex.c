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
struct sqlite3_index_constraint {scalar_t__ usable; scalar_t__ op; int iColumn; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; double estimatedCost; int estimatedRows; int idxNum; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
#define  CARRAY_COLUMN_COUNT 130 
#define  CARRAY_COLUMN_CTYPE 129 
#define  CARRAY_COLUMN_POINTER 128 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 

__attribute__((used)) static int carrayBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  int i;                 /* Loop over constraints */
  int ptrIdx = -1;       /* Index of the pointer= constraint, or -1 if none */
  int cntIdx = -1;       /* Index of the count= constraint, or -1 if none */
  int ctypeIdx = -1;     /* Index of the ctype= constraint, or -1 if none */

  const struct sqlite3_index_constraint *pConstraint;
  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    if( pConstraint->usable==0 ) continue;
    if( pConstraint->op!=SQLITE_INDEX_CONSTRAINT_EQ ) continue;
    switch( pConstraint->iColumn ){
      case CARRAY_COLUMN_POINTER:
        ptrIdx = i;
        break;
      case CARRAY_COLUMN_COUNT:
        cntIdx = i;
        break;
      case CARRAY_COLUMN_CTYPE:
        ctypeIdx = i;
        break;
    }
  }
  if( ptrIdx>=0 && cntIdx>=0 ){
    pIdxInfo->aConstraintUsage[ptrIdx].argvIndex = 1;
    pIdxInfo->aConstraintUsage[ptrIdx].omit = 1;
    pIdxInfo->aConstraintUsage[cntIdx].argvIndex = 2;
    pIdxInfo->aConstraintUsage[cntIdx].omit = 1;
    pIdxInfo->estimatedCost = (double)1;
    pIdxInfo->estimatedRows = 100;
    pIdxInfo->idxNum = 2;
    if( ctypeIdx>=0 ){
      pIdxInfo->aConstraintUsage[ctypeIdx].argvIndex = 3;
      pIdxInfo->aConstraintUsage[ctypeIdx].omit = 1;
      pIdxInfo->idxNum = 3;
    }
  }else{
    pIdxInfo->estimatedCost = (double)2147483647;
    pIdxInfo->estimatedRows = 2147483647;
    pIdxInfo->idxNum = 0;
  }
  return SQLITE_OK;
}