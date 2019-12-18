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
struct TYPE_5__ {int iStart; int iEnd; scalar_t__ iInst; scalar_t__ nInst; int iCol; int /*<<< orphan*/  pFts; TYPE_1__* pApi; } ;
struct TYPE_4__ {int (* xInst ) (int /*<<< orphan*/ ,scalar_t__,int*,int*,int*) ;int (* xPhraseSize ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_2__ CInstIter ;

/* Variables and functions */
 int SQLITE_OK ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int*,int*,int*) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fts5CInstIterNext(CInstIter *pIter){
  int rc = SQLITE_OK;
  pIter->iStart = -1;
  pIter->iEnd = -1;

  while( rc==SQLITE_OK && pIter->iInst<pIter->nInst ){
    int ip; int ic; int io;
    rc = pIter->pApi->xInst(pIter->pFts, pIter->iInst, &ip, &ic, &io);
    if( rc==SQLITE_OK ){
      if( ic==pIter->iCol ){
        int iEnd = io - 1 + pIter->pApi->xPhraseSize(pIter->pFts, ip);
        if( pIter->iStart<0 ){
          pIter->iStart = io;
          pIter->iEnd = iEnd;
        }else if( io<=pIter->iEnd ){
          if( iEnd>pIter->iEnd ) pIter->iEnd = iEnd;
        }else{
          break;
        }
      }
      pIter->iInst++;
    }
  }

  return rc;
}