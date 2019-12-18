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
struct TYPE_3__ {int bTotalsValid; int /*<<< orphan*/  aTotalSize; int /*<<< orphan*/  nTotalRow; int /*<<< orphan*/  pIndex; } ;
typedef  TYPE_1__ Fts5Storage ;

/* Variables and functions */
 int SQLITE_OK ; 
 int sqlite3Fts5IndexGetAverages (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5StorageLoadTotals(Fts5Storage *p, int bCache){
  int rc = SQLITE_OK;
  if( p->bTotalsValid==0 ){
    rc = sqlite3Fts5IndexGetAverages(p->pIndex, &p->nTotalRow, p->aTotalSize);
    p->bTotalsValid = bCache;
  }
  return rc;
}