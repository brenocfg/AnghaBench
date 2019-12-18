#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sqlite3_index_constraint_usage {int omit; int argvIndex; } ;
struct sqlite3_index_constraint {scalar_t__ iColumn; scalar_t__ op; scalar_t__ usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_3__ {double estimatedCost; int nConstraint; int idxNum; struct sqlite3_index_constraint_usage* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_1__ sqlite3_index_info ;

/* Variables and functions */
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 

__attribute__((used)) static int fsdirBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  int ii;

  pIdxInfo->estimatedCost = 1000000000.0;

  for(ii=0; ii<pIdxInfo->nConstraint; ii++){
    struct sqlite3_index_constraint const *p = &pIdxInfo->aConstraint[ii];
    if( p->iColumn==0 && p->usable && p->op==SQLITE_INDEX_CONSTRAINT_EQ ){
      struct sqlite3_index_constraint_usage *pUsage;
      pUsage = &pIdxInfo->aConstraintUsage[ii];
      pUsage->omit = 1;
      pUsage->argvIndex = 1;
      pIdxInfo->idxNum = 1;
      pIdxInfo->estimatedCost = 1.0;
      break;
    }
  }

  return SQLITE_OK;
}