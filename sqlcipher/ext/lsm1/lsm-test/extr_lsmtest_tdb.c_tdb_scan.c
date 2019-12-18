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
struct TYPE_6__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ TestDb ;
struct TYPE_5__ {int (* xScan ) (TYPE_2__*,void*,int,void*,int,void*,int,void (*) (void*,void*,int,void*,int)) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,void*,int,void*,int,void*,int,void (*) (void*,void*,int,void*,int)) ; 

int tdb_scan(
  TestDb *pDb,                    /* Database handle */
  void *pCtx,                     /* Context pointer to pass to xCallback */
  int bReverse,                   /* True to scan in reverse order */
  void *pKey1, int nKey1,         /* Start of search */
  void *pKey2, int nKey2,         /* End of search */
  void (*xCallback)(void *pCtx, void *pKey, int nKey, void *pVal, int nVal)
){
  return pDb->pMethods->xScan(
      pDb, pCtx, bReverse, pKey1, nKey1, pKey2, nKey2, xCallback
  );
}