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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {int n; int* a; } ;
typedef  TYPE_1__ Blob ;

/* Variables and functions */
 int FTS_CORRUPT_VTAB ; 
 int SQLITE_OK ; 
 scalar_t__ fts3GetVarint32 (int*,int*) ; 
 scalar_t__ sqlite3Fts3GetVarint (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3IncrmergeHintPop(Blob *pHint, i64 *piAbsLevel, int *pnInput){
  const int nHint = pHint->n;
  int i;

  i = pHint->n-2;
  while( i>0 && (pHint->a[i-1] & 0x80) ) i--;
  while( i>0 && (pHint->a[i-1] & 0x80) ) i--;

  pHint->n = i;
  i += sqlite3Fts3GetVarint(&pHint->a[i], piAbsLevel);
  i += fts3GetVarint32(&pHint->a[i], pnInput);
  if( i!=nHint ) return FTS_CORRUPT_VTAB;

  return SQLITE_OK;
}