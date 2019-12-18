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
struct sqlite3_index_constraint {scalar_t__ iColumn; scalar_t__ usable; scalar_t__ op; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_7__ {int nConstraint; double estimatedCost; int estimatedRows; int nOrderBy; int orderByConsumed; int idxNum; TYPE_2__* aOrderBy; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_3__ sqlite3_index_info ;
struct TYPE_6__ {scalar_t__ desc; } ;
struct TYPE_5__ {int argvIndex; int omit; } ;

/* Variables and functions */
 scalar_t__ SERIES_COLUMN_START ; 
 scalar_t__ SERIES_COLUMN_STEP ; 
 scalar_t__ SERIES_COLUMN_STOP ; 
 int SQLITE_CONSTRAINT ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_SERIES_CONSTRAINT_VERIFY ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int seriesBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  int i, j;              /* Loop over constraints */
  int idxNum = 0;        /* The query plan bitmask */
  int unusableMask = 0;  /* Mask of unusable constraints */
  int nArg = 0;          /* Number of arguments that seriesFilter() expects */
  int aIdx[3];           /* Constraints on start, stop, and step */
  const struct sqlite3_index_constraint *pConstraint;

  /* This implementation assumes that the start, stop, and step columns
  ** are the last three columns in the virtual table. */
  assert( SERIES_COLUMN_STOP == SERIES_COLUMN_START+1 );
  assert( SERIES_COLUMN_STEP == SERIES_COLUMN_START+2 );
  aIdx[0] = aIdx[1] = aIdx[2] = -1;
  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    int iCol;    /* 0 for start, 1 for stop, 2 for step */
    int iMask;   /* bitmask for those column */
    if( pConstraint->iColumn<SERIES_COLUMN_START ) continue;
    iCol = pConstraint->iColumn - SERIES_COLUMN_START;
    assert( iCol>=0 && iCol<=2 );
    iMask = 1 << iCol;
    if( pConstraint->usable==0 ){
      unusableMask |=  iMask;
      continue;
    }else if( pConstraint->op==SQLITE_INDEX_CONSTRAINT_EQ ){
      idxNum |= iMask;
      aIdx[iCol] = i;
    }
  }
  for(i=0; i<3; i++){
    if( (j = aIdx[i])>=0 ){
      pIdxInfo->aConstraintUsage[j].argvIndex = ++nArg;
      pIdxInfo->aConstraintUsage[j].omit = !SQLITE_SERIES_CONSTRAINT_VERIFY;
    }
  }
  if( (unusableMask & ~idxNum)!=0 ){
    /* The start, stop, and step columns are inputs.  Therefore if there
    ** are unusable constraints on any of start, stop, or step then
    ** this plan is unusable */
    return SQLITE_CONSTRAINT;
  }
  if( (idxNum & 3)==3 ){
    /* Both start= and stop= boundaries are available.  This is the 
    ** the preferred case */
    pIdxInfo->estimatedCost = (double)(2 - ((idxNum&4)!=0));
    pIdxInfo->estimatedRows = 1000;
    if( pIdxInfo->nOrderBy==1 ){
      if( pIdxInfo->aOrderBy[0].desc ) idxNum |= 8;
      pIdxInfo->orderByConsumed = 1;
    }
  }else{
    /* If either boundary is missing, we have to generate a huge span
    ** of numbers.  Make this case very expensive so that the query
    ** planner will work hard to avoid it. */
    pIdxInfo->estimatedRows = 2147483647;
  }
  pIdxInfo->idxNum = idxNum;
  return SQLITE_OK;
}