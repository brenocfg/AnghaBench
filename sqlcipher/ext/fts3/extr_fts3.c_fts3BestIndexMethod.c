#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sqlite3_index_orderby {scalar_t__ iColumn; scalar_t__ desc; } ;
struct sqlite3_index_constraint {scalar_t__ usable; int op; scalar_t__ iColumn; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int sqlite3_int64 ;
struct TYPE_8__ {scalar_t__ idxNum; int estimatedCost; int nConstraint; int nOrderBy; char* idxStr; int orderByConsumed; struct sqlite3_index_orderby* aOrderBy; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_9__ {scalar_t__ nColumn; scalar_t__ pSegments; } ;
struct TYPE_7__ {int omit; int /*<<< orphan*/  argvIndex; } ;
typedef  TYPE_3__ Fts3Table ;

/* Variables and functions */
 scalar_t__ FTS3_DOCID_SEARCH ; 
 void* FTS3_FULLSCAN_SEARCH ; 
 scalar_t__ FTS3_FULLTEXT_SEARCH ; 
 scalar_t__ FTS3_HAVE_DOCID_GE ; 
 scalar_t__ FTS3_HAVE_DOCID_LE ; 
 scalar_t__ FTS3_HAVE_LANGID ; 
 int SQLITE_INDEX_CONSTRAINT_EQ ; 
#define  SQLITE_INDEX_CONSTRAINT_GE 131 
#define  SQLITE_INDEX_CONSTRAINT_GT 130 
#define  SQLITE_INDEX_CONSTRAINT_LE 129 
#define  SQLITE_INDEX_CONSTRAINT_LT 128 
 int SQLITE_INDEX_CONSTRAINT_MATCH ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3SetEstimatedRows (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fts3SetUniqueFlag (TYPE_2__*) ; 

__attribute__((used)) static int fts3BestIndexMethod(sqlite3_vtab *pVTab, sqlite3_index_info *pInfo){
  Fts3Table *p = (Fts3Table *)pVTab;
  int i;                          /* Iterator variable */
  int iCons = -1;                 /* Index of constraint to use */

  int iLangidCons = -1;           /* Index of langid=x constraint, if present */
  int iDocidGe = -1;              /* Index of docid>=x constraint, if present */
  int iDocidLe = -1;              /* Index of docid<=x constraint, if present */
  int iIdx;

  /* By default use a full table scan. This is an expensive option,
  ** so search through the constraints to see if a more efficient 
  ** strategy is possible.
  */
  pInfo->idxNum = FTS3_FULLSCAN_SEARCH;
  pInfo->estimatedCost = 5000000;
  for(i=0; i<pInfo->nConstraint; i++){
    int bDocid;                 /* True if this constraint is on docid */
    struct sqlite3_index_constraint *pCons = &pInfo->aConstraint[i];
    if( pCons->usable==0 ){
      if( pCons->op==SQLITE_INDEX_CONSTRAINT_MATCH ){
        /* There exists an unusable MATCH constraint. This means that if
        ** the planner does elect to use the results of this call as part
        ** of the overall query plan the user will see an "unable to use
        ** function MATCH in the requested context" error. To discourage
        ** this, return a very high cost here.  */
        pInfo->idxNum = FTS3_FULLSCAN_SEARCH;
        pInfo->estimatedCost = 1e50;
        fts3SetEstimatedRows(pInfo, ((sqlite3_int64)1) << 50);
        return SQLITE_OK;
      }
      continue;
    }

    bDocid = (pCons->iColumn<0 || pCons->iColumn==p->nColumn+1);

    /* A direct lookup on the rowid or docid column. Assign a cost of 1.0. */
    if( iCons<0 && pCons->op==SQLITE_INDEX_CONSTRAINT_EQ && bDocid ){
      pInfo->idxNum = FTS3_DOCID_SEARCH;
      pInfo->estimatedCost = 1.0;
      iCons = i;
    }

    /* A MATCH constraint. Use a full-text search.
    **
    ** If there is more than one MATCH constraint available, use the first
    ** one encountered. If there is both a MATCH constraint and a direct
    ** rowid/docid lookup, prefer the MATCH strategy. This is done even 
    ** though the rowid/docid lookup is faster than a MATCH query, selecting
    ** it would lead to an "unable to use function MATCH in the requested 
    ** context" error.
    */
    if( pCons->op==SQLITE_INDEX_CONSTRAINT_MATCH 
     && pCons->iColumn>=0 && pCons->iColumn<=p->nColumn
    ){
      pInfo->idxNum = FTS3_FULLTEXT_SEARCH + pCons->iColumn;
      pInfo->estimatedCost = 2.0;
      iCons = i;
    }

    /* Equality constraint on the langid column */
    if( pCons->op==SQLITE_INDEX_CONSTRAINT_EQ 
     && pCons->iColumn==p->nColumn + 2
    ){
      iLangidCons = i;
    }

    if( bDocid ){
      switch( pCons->op ){
        case SQLITE_INDEX_CONSTRAINT_GE:
        case SQLITE_INDEX_CONSTRAINT_GT:
          iDocidGe = i;
          break;

        case SQLITE_INDEX_CONSTRAINT_LE:
        case SQLITE_INDEX_CONSTRAINT_LT:
          iDocidLe = i;
          break;
      }
    }
  }

  /* If using a docid=? or rowid=? strategy, set the UNIQUE flag. */
  if( pInfo->idxNum==FTS3_DOCID_SEARCH ) fts3SetUniqueFlag(pInfo);

  iIdx = 1;
  if( iCons>=0 ){
    pInfo->aConstraintUsage[iCons].argvIndex = iIdx++;
    pInfo->aConstraintUsage[iCons].omit = 1;
  } 
  if( iLangidCons>=0 ){
    pInfo->idxNum |= FTS3_HAVE_LANGID;
    pInfo->aConstraintUsage[iLangidCons].argvIndex = iIdx++;
  } 
  if( iDocidGe>=0 ){
    pInfo->idxNum |= FTS3_HAVE_DOCID_GE;
    pInfo->aConstraintUsage[iDocidGe].argvIndex = iIdx++;
  } 
  if( iDocidLe>=0 ){
    pInfo->idxNum |= FTS3_HAVE_DOCID_LE;
    pInfo->aConstraintUsage[iDocidLe].argvIndex = iIdx++;
  } 

  /* Regardless of the strategy selected, FTS can deliver rows in rowid (or
  ** docid) order. Both ascending and descending are possible. 
  */
  if( pInfo->nOrderBy==1 ){
    struct sqlite3_index_orderby *pOrder = &pInfo->aOrderBy[0];
    if( pOrder->iColumn<0 || pOrder->iColumn==p->nColumn+1 ){
      if( pOrder->desc ){
        pInfo->idxStr = "DESC";
      }else{
        pInfo->idxStr = "ASC";
      }
      pInfo->orderByConsumed = 1;
    }
  }

  assert( p->pSegments==0 );
  return SQLITE_OK;
}