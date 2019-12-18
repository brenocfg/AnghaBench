#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ bCoreMutex; } ;
struct TYPE_6__ {void* (* xTask ) (void*) ;int done; void* pOut; int /*<<< orphan*/  tid; void* pIn; } ;
typedef  TYPE_1__ SQLiteThread ;

/* Variables and functions */
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void* (*) (void*),void*) ; 
 scalar_t__ sqlite3FaultSim (int) ; 
 TYPE_4__ sqlite3GlobalConfig ; 
 TYPE_1__* sqlite3Malloc (int) ; 

int sqlite3ThreadCreate(
  SQLiteThread **ppThread,  /* OUT: Write the thread object here */
  void *(*xTask)(void*),    /* Routine to run in a separate thread */
  void *pIn                 /* Argument passed into xTask() */
){
  SQLiteThread *p;
  int rc;

  assert( ppThread!=0 );
  assert( xTask!=0 );
  /* This routine is never used in single-threaded mode */
  assert( sqlite3GlobalConfig.bCoreMutex!=0 );

  *ppThread = 0;
  p = sqlite3Malloc(sizeof(*p));
  if( p==0 ) return SQLITE_NOMEM_BKPT;
  memset(p, 0, sizeof(*p));
  p->xTask = xTask;
  p->pIn = pIn;
  /* If the SQLITE_TESTCTRL_FAULT_INSTALL callback is registered to a 
  ** function that returns SQLITE_ERROR when passed the argument 200, that
  ** forces worker threads to run sequentially and deterministically 
  ** for testing purposes. */
  if( sqlite3FaultSim(200) ){
    rc = 1;
  }else{    
    rc = pthread_create(&p->tid, 0, xTask, pIn);
  }
  if( rc ){
    p->done = 1;
    p->pOut = xTask(pIn);
  }
  *ppThread = p;
  return SQLITE_OK;
}