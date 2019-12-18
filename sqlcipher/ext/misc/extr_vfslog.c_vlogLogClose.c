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
typedef  int /*<<< orphan*/  sqlite3_mutex ;
struct TYPE_6__ {scalar_t__ nRef; scalar_t__ zFilename; int /*<<< orphan*/  out; TYPE_1__** ppPrev; TYPE_1__* pNext; } ;
typedef  TYPE_2__ VLogLog ;
struct TYPE_5__ {struct TYPE_5__** ppPrev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MUTEX_STATIC_MASTER ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * sqlite3_mutex_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlogLogClose(VLogLog *p){
  if( p ){
    sqlite3_mutex *pMutex;
    p->nRef--;
    if( p->nRef>0 || p->zFilename==0 ) return;
    pMutex = sqlite3_mutex_alloc(SQLITE_MUTEX_STATIC_MASTER);
    sqlite3_mutex_enter(pMutex);
    *p->ppPrev = p->pNext;
    if( p->pNext ) p->pNext->ppPrev = p->ppPrev;
    sqlite3_mutex_leave(pMutex);
    fclose(p->out);
    sqlite3_free(p);
  }
}