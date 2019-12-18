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
struct TYPE_5__ {int estimatedRows; int nConstraint; double estimatedCost; int idxNum; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ EXPLN_COLUMN_SQL ; 
 int SQLITE_CONSTRAINT ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 

__attribute__((used)) static int explainBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  int i;                  /* Loop counter */
  int idx = -1;           /* Index of a usable == constraint against SQL */
  int unusable = 0;       /* True if there are unusable constraints on SQL */

  pIdxInfo->estimatedRows = 500;
  for(i=0; i<pIdxInfo->nConstraint; i++){
    struct sqlite3_index_constraint *p = &pIdxInfo->aConstraint[i];
    if( p->iColumn!=EXPLN_COLUMN_SQL ) continue;
    if( !p->usable ){
      unusable = 1;
    }else if( p->op==SQLITE_INDEX_CONSTRAINT_EQ ){
      idx = i;
    }
  }
  if( idx>=0 ){
    /* There exists a usable == constraint against the SQL column */
    pIdxInfo->estimatedCost = 10.0;
    pIdxInfo->idxNum = 1;
    pIdxInfo->aConstraintUsage[idx].argvIndex = 1;
    pIdxInfo->aConstraintUsage[idx].omit = 1;
  }else if( unusable ){
    /* There are unusable constraints against the SQL column.  Do not allow
    ** this plan to continue forward. */
    return SQLITE_CONSTRAINT;
  }
  return SQLITE_OK;
}