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
struct TYPE_7__ {int pQueueFirst; int /*<<< orphan*/  nFile; TYPE_2__* pQueueLast; } ;
struct TYPE_6__ {size_t op; int /*<<< orphan*/  iOffset; TYPE_1__* pFileData; struct TYPE_6__* pNext; } ;
struct TYPE_5__ {char* zName; } ;
typedef  TYPE_2__ AsyncWrite ;

/* Variables and functions */
 size_t ASYNC_CLOSE ; 
 int /*<<< orphan*/  ASYNC_COND_QUEUE ; 
 int /*<<< orphan*/  ASYNC_MUTEX_QUEUE ; 
 int /*<<< orphan*/  ASYNC_TRACE (char*) ; 
 size_t ASYNC_UNLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ async ; 
 int /*<<< orphan*/  async_cond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * azOpcodeName ; 

__attribute__((used)) static void addAsyncWrite(AsyncWrite *pWrite){
  /* We must hold the queue mutex in order to modify the queue pointers */
  if( pWrite->op!=ASYNC_UNLOCK ){
    async_mutex_enter(ASYNC_MUTEX_QUEUE);
  }

  /* Add the record to the end of the write-op queue */
  assert( !pWrite->pNext );
  if( async.pQueueLast ){
    assert( async.pQueueFirst );
    async.pQueueLast->pNext = pWrite;
  }else{
    async.pQueueFirst = pWrite;
  }
  async.pQueueLast = pWrite;
  ASYNC_TRACE(("PUSH %p (%s %s %d)\n", pWrite, azOpcodeName[pWrite->op],
         pWrite->pFileData ? pWrite->pFileData->zName : "-", pWrite->iOffset));

  if( pWrite->op==ASYNC_CLOSE ){
    async.nFile--;
  }

  /* The writer thread might have been idle because there was nothing
  ** on the write-op queue for it to do.  So wake it up. */
  async_cond_signal(ASYNC_COND_QUEUE);

  /* Drop the queue mutex */
  if( pWrite->op!=ASYNC_UNLOCK ){
    async_mutex_leave(ASYNC_MUTEX_QUEUE);
  }
}