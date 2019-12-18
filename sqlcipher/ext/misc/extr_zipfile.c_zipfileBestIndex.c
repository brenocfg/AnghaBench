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
struct sqlite3_index_constraint {scalar_t__ iColumn; scalar_t__ usable; scalar_t__ op; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; double estimatedCost; int idxNum; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
 int SQLITE_CONSTRAINT ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 
 scalar_t__ ZIPFILE_F_COLUMN_IDX ; 

__attribute__((used)) static int zipfileBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  int i;
  int idx = -1;
  int unusable = 0;

  for(i=0; i<pIdxInfo->nConstraint; i++){
    const struct sqlite3_index_constraint *pCons = &pIdxInfo->aConstraint[i];
    if( pCons->iColumn!=ZIPFILE_F_COLUMN_IDX ) continue;
    if( pCons->usable==0 ){
      unusable = 1;
    }else if( pCons->op==SQLITE_INDEX_CONSTRAINT_EQ ){
      idx = i;
    }
  }
  if( idx>=0 ){
    pIdxInfo->aConstraintUsage[idx].argvIndex = 1;
    pIdxInfo->aConstraintUsage[idx].omit = 1;
    pIdxInfo->estimatedCost = 1000.0;
    pIdxInfo->idxNum = 1;
  }else if( unusable ){
    return SQLITE_CONSTRAINT;
  }
  return SQLITE_OK;
}