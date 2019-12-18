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
struct sqlite3_index_constraint {scalar_t__ usable; scalar_t__ iColumn; scalar_t__ op; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_8__ {int nConstraint; int idxNum; int nOrderBy; int orderByConsumed; double estimatedCost; TYPE_2__* aOrderBy; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_3__ sqlite3_index_info ;
struct TYPE_9__ {scalar_t__ zTableName; scalar_t__ zIdColumn; scalar_t__ zParentColumn; } ;
typedef  TYPE_4__ closure_vtab ;
struct TYPE_7__ {scalar_t__ iColumn; scalar_t__ desc; } ;
struct TYPE_6__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ CLOSURE_COL_DEPTH ; 
 scalar_t__ CLOSURE_COL_ID ; 
 scalar_t__ CLOSURE_COL_IDCOLUMN ; 
 scalar_t__ CLOSURE_COL_PARENTCOLUMN ; 
 scalar_t__ CLOSURE_COL_ROOT ; 
 scalar_t__ CLOSURE_COL_TABLENAME ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LT ; 
 int SQLITE_OK ; 

__attribute__((used)) static int closureBestIndex(
  sqlite3_vtab *pTab,             /* The virtual table */
  sqlite3_index_info *pIdxInfo    /* Information about the query */
){
  int iPlan = 0;
  int i;
  int idx = 1;
  const struct sqlite3_index_constraint *pConstraint;
  closure_vtab *pVtab = (closure_vtab*)pTab;
  double rCost = 10000000.0;

  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    if( pConstraint->usable==0 ) continue;
    if( (iPlan & 1)==0 
     && pConstraint->iColumn==CLOSURE_COL_ROOT
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= 1;
      pIdxInfo->aConstraintUsage[i].argvIndex = 1;
      pIdxInfo->aConstraintUsage[i].omit = 1;
      rCost /= 100.0;
    }
    if( (iPlan & 0x0000f0)==0
     && pConstraint->iColumn==CLOSURE_COL_DEPTH
     && (pConstraint->op==SQLITE_INDEX_CONSTRAINT_LT
           || pConstraint->op==SQLITE_INDEX_CONSTRAINT_LE
           || pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ)
    ){
      iPlan |= idx<<4;
      pIdxInfo->aConstraintUsage[i].argvIndex = ++idx;
      if( pConstraint->op==SQLITE_INDEX_CONSTRAINT_LT ) iPlan |= 0x000002;
      rCost /= 5.0;
    }
    if( (iPlan & 0x000f00)==0
     && pConstraint->iColumn==CLOSURE_COL_TABLENAME
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= idx<<8;
      pIdxInfo->aConstraintUsage[i].argvIndex = ++idx;
      pIdxInfo->aConstraintUsage[i].omit = 1;
      rCost /= 5.0;
    }
    if( (iPlan & 0x00f000)==0
     && pConstraint->iColumn==CLOSURE_COL_IDCOLUMN
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= idx<<12;
      pIdxInfo->aConstraintUsage[i].argvIndex = ++idx;
      pIdxInfo->aConstraintUsage[i].omit = 1;
    }
    if( (iPlan & 0x0f0000)==0
     && pConstraint->iColumn==CLOSURE_COL_PARENTCOLUMN
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= idx<<16;
      pIdxInfo->aConstraintUsage[i].argvIndex = ++idx;
      pIdxInfo->aConstraintUsage[i].omit = 1;
    }
  }
  if( (pVtab->zTableName==0    && (iPlan & 0x000f00)==0)
   || (pVtab->zIdColumn==0     && (iPlan & 0x00f000)==0)
   || (pVtab->zParentColumn==0 && (iPlan & 0x0f0000)==0)
  ){
    /* All of tablename, idcolumn, and parentcolumn must be specified
    ** in either the CREATE VIRTUAL TABLE or in the WHERE clause constraints
    ** or else the result is an empty set. */
    iPlan = 0;
  }
  if( (iPlan&1)==0 ){
    /* If there is no usable "root=?" term, then set the index-type to 0.
    ** Also clear any argvIndex variables already set. This is necessary
    ** to prevent the core from throwing an "xBestIndex malfunction error"
    ** error (because the argvIndex values are not contiguously assigned
    ** starting from 1).  */
    rCost *= 1e30;
    for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
      pIdxInfo->aConstraintUsage[i].argvIndex = 0;
    }
    iPlan = 0;
  }
  pIdxInfo->idxNum = iPlan;
  if( pIdxInfo->nOrderBy==1
   && pIdxInfo->aOrderBy[0].iColumn==CLOSURE_COL_ID
   && pIdxInfo->aOrderBy[0].desc==0
  ){
    pIdxInfo->orderByConsumed = 1;
  }
  pIdxInfo->estimatedCost = rCost;
   
  return SQLITE_OK;
}