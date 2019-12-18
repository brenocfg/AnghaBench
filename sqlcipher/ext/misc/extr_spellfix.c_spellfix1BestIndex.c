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
struct TYPE_7__ {int nConstraint; int idxNum; int nOrderBy; int orderByConsumed; int estimatedCost; TYPE_2__* aConstraintUsage; TYPE_1__* aOrderBy; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_3__ sqlite3_index_info ;
struct TYPE_6__ {int argvIndex; int omit; } ;
struct TYPE_5__ {scalar_t__ iColumn; scalar_t__ desc; } ;

/* Variables and functions */
 scalar_t__ SPELLFIX_COL_DISTANCE ; 
 scalar_t__ SPELLFIX_COL_LANGID ; 
 scalar_t__ SPELLFIX_COL_SCOPE ; 
 scalar_t__ SPELLFIX_COL_SCORE ; 
 scalar_t__ SPELLFIX_COL_TOP ; 
 scalar_t__ SPELLFIX_COL_WORD ; 
 int SPELLFIX_IDXNUM_DIST ; 
 int SPELLFIX_IDXNUM_DISTLE ; 
 int SPELLFIX_IDXNUM_DISTLT ; 
 int SPELLFIX_IDXNUM_LANGID ; 
 int SPELLFIX_IDXNUM_MATCH ; 
 int SPELLFIX_IDXNUM_ROWID ; 
 int SPELLFIX_IDXNUM_SCOPE ; 
 int SPELLFIX_IDXNUM_TOP ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LE ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_LT ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_MATCH ; 
 int SQLITE_OK ; 

__attribute__((used)) static int spellfix1BestIndex(sqlite3_vtab *tab, sqlite3_index_info *pIdxInfo){
  int iPlan = 0;
  int iLangTerm = -1;
  int iTopTerm = -1;
  int iScopeTerm = -1;
  int iDistTerm = -1;
  int iRowidTerm = -1;
  int i;
  const struct sqlite3_index_constraint *pConstraint;
  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    if( pConstraint->usable==0 ) continue;

    /* Terms of the form:  word MATCH $str */
    if( (iPlan & SPELLFIX_IDXNUM_MATCH)==0 
     && pConstraint->iColumn==SPELLFIX_COL_WORD
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_MATCH
    ){
      iPlan |= SPELLFIX_IDXNUM_MATCH;
      pIdxInfo->aConstraintUsage[i].argvIndex = 1;
      pIdxInfo->aConstraintUsage[i].omit = 1;
    }

    /* Terms of the form:  langid = $langid  */
    if( (iPlan & SPELLFIX_IDXNUM_LANGID)==0
     && pConstraint->iColumn==SPELLFIX_COL_LANGID
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= SPELLFIX_IDXNUM_LANGID;
      iLangTerm = i;
    }

    /* Terms of the form:  top = $top */
    if( (iPlan & SPELLFIX_IDXNUM_TOP)==0
     && pConstraint->iColumn==SPELLFIX_COL_TOP
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= SPELLFIX_IDXNUM_TOP;
      iTopTerm = i;
    }

    /* Terms of the form:  scope = $scope */
    if( (iPlan & SPELLFIX_IDXNUM_SCOPE)==0
     && pConstraint->iColumn==SPELLFIX_COL_SCOPE
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= SPELLFIX_IDXNUM_SCOPE;
      iScopeTerm = i;
    }

    /* Terms of the form:  distance < $dist or distance <= $dist */
    if( (iPlan & SPELLFIX_IDXNUM_DIST)==0
     && pConstraint->iColumn==SPELLFIX_COL_DISTANCE
     && (pConstraint->op==SQLITE_INDEX_CONSTRAINT_LT
          || pConstraint->op==SQLITE_INDEX_CONSTRAINT_LE)
    ){
      if( pConstraint->op==SQLITE_INDEX_CONSTRAINT_LT ){
        iPlan |= SPELLFIX_IDXNUM_DISTLT;
      }else{
        iPlan |= SPELLFIX_IDXNUM_DISTLE;
      }
      iDistTerm = i;
    }

    /* Terms of the form:  distance < $dist or distance <= $dist */
    if( (iPlan & SPELLFIX_IDXNUM_ROWID)==0
     && pConstraint->iColumn<0
     && pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ
    ){
      iPlan |= SPELLFIX_IDXNUM_ROWID;
      iRowidTerm = i;
    }
  }
  if( iPlan&SPELLFIX_IDXNUM_MATCH ){
    int idx = 2;
    pIdxInfo->idxNum = iPlan;
    if( pIdxInfo->nOrderBy==1
     && pIdxInfo->aOrderBy[0].iColumn==SPELLFIX_COL_SCORE
     && pIdxInfo->aOrderBy[0].desc==0
    ){
      pIdxInfo->orderByConsumed = 1;  /* Default order by iScore */
    }
    if( iPlan&SPELLFIX_IDXNUM_LANGID ){
      pIdxInfo->aConstraintUsage[iLangTerm].argvIndex = idx++;
      pIdxInfo->aConstraintUsage[iLangTerm].omit = 1;
    }
    if( iPlan&SPELLFIX_IDXNUM_TOP ){
      pIdxInfo->aConstraintUsage[iTopTerm].argvIndex = idx++;
      pIdxInfo->aConstraintUsage[iTopTerm].omit = 1;
    }
    if( iPlan&SPELLFIX_IDXNUM_SCOPE ){
      pIdxInfo->aConstraintUsage[iScopeTerm].argvIndex = idx++;
      pIdxInfo->aConstraintUsage[iScopeTerm].omit = 1;
    }
    if( iPlan&SPELLFIX_IDXNUM_DIST ){
      pIdxInfo->aConstraintUsage[iDistTerm].argvIndex = idx++;
      pIdxInfo->aConstraintUsage[iDistTerm].omit = 1;
    }
    pIdxInfo->estimatedCost = 1e5;
  }else if( (iPlan & SPELLFIX_IDXNUM_ROWID) ){
    pIdxInfo->idxNum = SPELLFIX_IDXNUM_ROWID;
    pIdxInfo->aConstraintUsage[iRowidTerm].argvIndex = 1;
    pIdxInfo->aConstraintUsage[iRowidTerm].omit = 1;
    pIdxInfo->estimatedCost = 5;
  }else{
    pIdxInfo->idxNum = 0;
    pIdxInfo->estimatedCost = 1e50;
  }
  return SQLITE_OK;
}