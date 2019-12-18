#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* pLock; } ;
struct TYPE_14__ {TYPE_1__* pMethods; } ;
struct TYPE_12__ {struct TYPE_12__* pNext; } ;
struct TYPE_13__ {TYPE_3__ lock; TYPE_2__* pLock; scalar_t__ zName; } ;
struct TYPE_11__ {struct TYPE_11__* pNext; TYPE_6__* pFile; TYPE_3__* pList; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* xClose ) (TYPE_6__*) ;} ;
typedef  TYPE_2__ AsyncLock ;
typedef  TYPE_3__ AsyncFileLock ;
typedef  TYPE_4__ AsyncFileData ;

/* Variables and functions */
 int SQLITE_OK ; 
 TYPE_9__ async ; 
 int getFileLock (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 

__attribute__((used)) static int unlinkAsyncFile(AsyncFileData *pData){
  AsyncFileLock **ppIter;
  int rc = SQLITE_OK;

  if( pData->zName ){
    AsyncLock *pLock = pData->pLock;
    for(ppIter=&pLock->pList; *ppIter; ppIter=&((*ppIter)->pNext)){
      if( (*ppIter)==&pData->lock ){
        *ppIter = pData->lock.pNext;
        break;
      }
    }
    if( !pLock->pList ){
      AsyncLock **pp;
      if( pLock->pFile ){
        pLock->pFile->pMethods->xClose(pLock->pFile);
      }
      for(pp=&async.pLock; *pp!=pLock; pp=&((*pp)->pNext));
      *pp = pLock->pNext;
      sqlite3_free(pLock);
    }else{
      rc = getFileLock(pLock);
    }
  }

  return rc;
}