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
struct TYPE_7__ {TYPE_2__* pIncr; } ;
struct TYPE_6__ {TYPE_1__* pTask; } ;
struct TYPE_5__ {int bDone; } ;
typedef  TYPE_3__ PmaReader ;

/* Variables and functions */
 int /*<<< orphan*/  INCRINIT_TASK ; 
 void* SQLITE_INT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdbePmaReaderIncrMergeInit (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *vdbePmaReaderBgIncrInit(void *pCtx){
  PmaReader *pReader = (PmaReader*)pCtx;
  void *pRet = SQLITE_INT_TO_PTR(
                  vdbePmaReaderIncrMergeInit(pReader,INCRINIT_TASK)
               );
  pReader->pIncr->pTask->bDone = 1;
  return pRet;
}