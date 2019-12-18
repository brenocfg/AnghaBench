#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tid; void* pOut; scalar_t__ done; } ;
typedef  TYPE_1__ SQLiteThread ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

int sqlite3ThreadJoin(SQLiteThread *p, void **ppOut){
  int rc;

  assert( ppOut!=0 );
  if( NEVER(p==0) ) return SQLITE_NOMEM_BKPT;
  if( p->done ){
    *ppOut = p->pOut;
    rc = SQLITE_OK;
  }else{
    rc = pthread_join(p->tid, ppOut) ? SQLITE_ERROR : SQLITE_OK;
  }
  sqlite3_free(p);
  return rc;
}