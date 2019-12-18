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
struct sqlite3_index_constraint {scalar_t__ iColumn; scalar_t__ op; scalar_t__ usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {double estimatedCost; int estimatedRows; int nConstraint; int idxNum; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ BINFO_COLUMN_SCHEMA ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 

__attribute__((used)) static int binfoBestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  int i;
  pIdxInfo->estimatedCost = 10000.0;  /* Cost estimate */
  pIdxInfo->estimatedRows = 100;
  for(i=0; i<pIdxInfo->nConstraint; i++){
    struct sqlite3_index_constraint *p = &pIdxInfo->aConstraint[i];
    if( p->usable
     && p->iColumn==BINFO_COLUMN_SCHEMA
     && p->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      pIdxInfo->estimatedCost = 1000.0;
      pIdxInfo->idxNum = 1;
      pIdxInfo->aConstraintUsage[i].argvIndex = 1;
      pIdxInfo->aConstraintUsage[i].omit = 1;
      break;
    }
  }
  return SQLITE_OK;
}