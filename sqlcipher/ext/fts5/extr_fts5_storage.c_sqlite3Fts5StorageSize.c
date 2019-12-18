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
typedef  scalar_t__ i64 ;
struct TYPE_6__ {scalar_t__* aTotalSize; TYPE_1__* pConfig; } ;
struct TYPE_5__ {int nCol; } ;
typedef  TYPE_2__ Fts5Storage ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_RANGE ; 
 int fts5StorageLoadTotals (TYPE_2__*,int /*<<< orphan*/ ) ; 

int sqlite3Fts5StorageSize(Fts5Storage *p, int iCol, i64 *pnToken){
  int rc = fts5StorageLoadTotals(p, 0);
  if( rc==SQLITE_OK ){
    *pnToken = 0;
    if( iCol<0 ){
      int i;
      for(i=0; i<p->pConfig->nCol; i++){
        *pnToken += p->aTotalSize[i];
      }
    }else if( iCol<p->pConfig->nCol ){
      *pnToken = p->aTotalSize[iCol];
    }else{
      rc = SQLITE_RANGE;
    }
  }
  return rc;
}