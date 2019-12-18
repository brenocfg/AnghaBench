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
struct sqlite3_index_constraint {int iColumn; scalar_t__ op; scalar_t__ usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; double estimatedCost; scalar_t__ idxNum; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ QUERY_FULLTEXT ; 
 scalar_t__ QUERY_GENERIC ; 
 scalar_t__ QUERY_ROWID ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_MATCH ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static int fulltextBestIndex(sqlite3_vtab *pVTab, sqlite3_index_info *pInfo){
  int i;
  TRACE(("FTS1 BestIndex\n"));

  for(i=0; i<pInfo->nConstraint; ++i){
    const struct sqlite3_index_constraint *pConstraint;
    pConstraint = &pInfo->aConstraint[i];
    if( pConstraint->usable ) {
      if( pConstraint->iColumn==-1 &&
          pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ ){
        pInfo->idxNum = QUERY_ROWID;      /* lookup by rowid */
        TRACE(("FTS1 QUERY_ROWID\n"));
      } else if( pConstraint->iColumn>=0 &&
                 pConstraint->op==SQLITE_INDEX_CONSTRAINT_MATCH ){
        /* full-text search */
        pInfo->idxNum = QUERY_FULLTEXT + pConstraint->iColumn;
        TRACE(("FTS1 QUERY_FULLTEXT %d\n", pConstraint->iColumn));
      } else continue;

      pInfo->aConstraintUsage[i].argvIndex = 1;
      pInfo->aConstraintUsage[i].omit = 1;

      /* An arbitrary value for now.
       * TODO: Perhaps rowid matches should be considered cheaper than
       * full-text searches. */
      pInfo->estimatedCost = 1.0;   

      return SQLITE_OK;
    }
  }
  pInfo->idxNum = QUERY_GENERIC;
  return SQLITE_OK;
}