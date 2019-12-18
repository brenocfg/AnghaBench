#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* aiRowLogEst; int nKeyCol; scalar_t__ pPartIdxWhere; TYPE_1__* pTable; int /*<<< orphan*/  hasStat1; } ;
struct TYPE_5__ {int nRowLogEst; } ;
typedef  int LogEst ;
typedef  TYPE_2__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  ArraySize (int*) ; 
 scalar_t__ IsUniqueIndex (TYPE_2__*) ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int sqlite3LogEst (int) ; 

void sqlite3DefaultRowEst(Index *pIdx){
  /*                10,  9,  8,  7,  6 */
  LogEst aVal[] = { 33, 32, 30, 28, 26 };
  LogEst *a = pIdx->aiRowLogEst;
  int nCopy = MIN(ArraySize(aVal), pIdx->nKeyCol);
  int i;

  /* Indexes with default row estimates should not have stat1 data */
  assert( !pIdx->hasStat1 );

  /* Set the first entry (number of rows in the index) to the estimated 
  ** number of rows in the table, or half the number of rows in the table
  ** for a partial index.   But do not let the estimate drop below 10. */
  a[0] = pIdx->pTable->nRowLogEst;
  if( pIdx->pPartIdxWhere!=0 ) a[0] -= 10;  assert( 10==sqlite3LogEst(2) );
  if( a[0]<33 ) a[0] = 33;                  assert( 33==sqlite3LogEst(10) );

  /* Estimate that a[1] is 10, a[2] is 9, a[3] is 8, a[4] is 7, a[5] is
  ** 6 and each subsequent value (if any) is 5.  */
  memcpy(&a[1], aVal, nCopy*sizeof(LogEst));
  for(i=nCopy+1; i<=pIdx->nKeyCol; i++){
    a[i] = 23;                    assert( 23==sqlite3LogEst(5) );
  }

  assert( 0==sqlite3LogEst(1) );
  if( IsUniqueIndex(pIdx) ) a[pIdx->nKeyCol] = 0;
}