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
struct TYPE_5__ {int nConstraint; double estimatedCost; int /*<<< orphan*/  idxNum; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUERY_FULLTEXT ; 
 int /*<<< orphan*/  QUERY_GENERIC ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_MATCH ; 
 int SQLITE_OK ; 

__attribute__((used)) static int fulltextBestIndex(sqlite3_vtab *pVTab, sqlite3_index_info *pInfo){
  int i;

  for(i=0; i<pInfo->nConstraint; ++i){
    const struct sqlite3_index_constraint *pConstraint;
    pConstraint = &pInfo->aConstraint[i];
    if( pConstraint->iColumn==0 &&
        pConstraint->op==SQLITE_INDEX_CONSTRAINT_MATCH &&
        pConstraint->usable ){   /* a full-text search */
      pInfo->aConstraintUsage[i].argvIndex = 1;
      pInfo->aConstraintUsage[i].omit = 1;
      pInfo->idxNum = QUERY_FULLTEXT;
      pInfo->estimatedCost = 1.0;   /* an arbitrary value for now */
      return SQLITE_OK;
    }
  }
  pInfo->idxNum = QUERY_GENERIC;
  return SQLITE_OK;
}