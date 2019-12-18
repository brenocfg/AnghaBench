#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nCol; int* aiCol; } ;
struct TYPE_9__ {int /*<<< orphan*/  rc; TYPE_1__* pConfig; } ;
struct TYPE_8__ {int nCol; } ;
typedef  TYPE_2__ Fts5Parse ;
typedef  TYPE_3__ Fts5Colset ;

/* Variables and functions */
 scalar_t__ sqlite3Fts5MallocZero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 

Fts5Colset *sqlite3Fts5ParseColsetInvert(Fts5Parse *pParse, Fts5Colset *p){
  Fts5Colset *pRet;
  int nCol = pParse->pConfig->nCol;

  pRet = (Fts5Colset*)sqlite3Fts5MallocZero(&pParse->rc, 
      sizeof(Fts5Colset) + sizeof(int)*nCol
  );
  if( pRet ){
    int i;
    int iOld = 0;
    for(i=0; i<nCol; i++){
      if( iOld>=p->nCol || p->aiCol[iOld]!=i ){
        pRet->aiCol[pRet->nCol++] = i;
      }else{
        iOld++;
      }
    }
  }

  sqlite3_free(p);
  return pRet;
}