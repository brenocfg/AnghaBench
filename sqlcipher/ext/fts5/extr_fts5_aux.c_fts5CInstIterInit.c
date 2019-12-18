#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int iCol; int /*<<< orphan*/  nInst; int /*<<< orphan*/ * pFts; TYPE_1__ const* pApi; } ;
struct TYPE_7__ {int (* xInstCount ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ Fts5ExtensionApi ;
typedef  int /*<<< orphan*/  Fts5Context ;
typedef  TYPE_2__ CInstIter ;

/* Variables and functions */
 int SQLITE_OK ; 
 int fts5CInstIterNext (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5CInstIterInit(
  const Fts5ExtensionApi *pApi,
  Fts5Context *pFts,
  int iCol,
  CInstIter *pIter
){
  int rc;

  memset(pIter, 0, sizeof(CInstIter));
  pIter->pApi = pApi;
  pIter->pFts = pFts;
  pIter->iCol = iCol;
  rc = pApi->xInstCount(pFts, &pIter->nInst);

  if( rc==SQLITE_OK ){
    rc = fts5CInstIterNext(pIter);
  }

  return rc;
}