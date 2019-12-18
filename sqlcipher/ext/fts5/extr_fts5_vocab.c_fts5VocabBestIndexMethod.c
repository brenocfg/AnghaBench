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
struct sqlite3_index_constraint {scalar_t__ usable; scalar_t__ iColumn; scalar_t__ op; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_7__ {int nConstraint; int estimatedCost; int nOrderBy; int orderByConsumed; int idxNum; TYPE_2__* aOrderBy; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_3__ sqlite3_index_info ;
struct TYPE_6__ {scalar_t__ iColumn; scalar_t__ desc; } ;
struct TYPE_5__ {int argvIndex; } ;

/* Variables and functions */
 int FTS5_VOCAB_TERM_EQ ; 
 int FTS5_VOCAB_TERM_GE ; 
 int FTS5_VOCAB_TERM_LE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_GE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_GT ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAM (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5VocabBestIndexMethod(
  sqlite3_vtab *pUnused,
  sqlite3_index_info *pInfo
){
  int i;
  int iTermEq = -1;
  int iTermGe = -1;
  int iTermLe = -1;
  int idxNum = 0;
  int nArg = 0;

  UNUSED_PARAM(pUnused);

  for(i=0; i<pInfo->nConstraint; i++){
    struct sqlite3_index_constraint *p = &pInfo->aConstraint[i];
    if( p->usable==0 ) continue;
    if( p->iColumn==0 ){          /* term column */
      if( p->op==SQLITE_INDEX_CONSTRAINT_EQ ) iTermEq = i;
      if( p->op==SQLITE_INDEX_CONSTRAINT_LE ) iTermLe = i;
      if( p->op==SQLITE_INDEX_CONSTRAINT_LT ) iTermLe = i;
      if( p->op==SQLITE_INDEX_CONSTRAINT_GE ) iTermGe = i;
      if( p->op==SQLITE_INDEX_CONSTRAINT_GT ) iTermGe = i;
    }
  }

  if( iTermEq>=0 ){
    idxNum |= FTS5_VOCAB_TERM_EQ;
    pInfo->aConstraintUsage[iTermEq].argvIndex = ++nArg;
    pInfo->estimatedCost = 100;
  }else{
    pInfo->estimatedCost = 1000000;
    if( iTermGe>=0 ){
      idxNum |= FTS5_VOCAB_TERM_GE;
      pInfo->aConstraintUsage[iTermGe].argvIndex = ++nArg;
      pInfo->estimatedCost = pInfo->estimatedCost / 2;
    }
    if( iTermLe>=0 ){
      idxNum |= FTS5_VOCAB_TERM_LE;
      pInfo->aConstraintUsage[iTermLe].argvIndex = ++nArg;
      pInfo->estimatedCost = pInfo->estimatedCost / 2;
    }
  }

  /* This virtual table always delivers results in ascending order of
  ** the "term" column (column 0). So if the user has requested this
  ** specifically - "ORDER BY term" or "ORDER BY term ASC" - set the
  ** sqlite3_index_info.orderByConsumed flag to tell the core the results
  ** are already in sorted order.  */
  if( pInfo->nOrderBy==1 
   && pInfo->aOrderBy[0].iColumn==0 
   && pInfo->aOrderBy[0].desc==0
  ){
    pInfo->orderByConsumed = 1;
  }

  pInfo->idxNum = idxNum;
  return SQLITE_OK;
}