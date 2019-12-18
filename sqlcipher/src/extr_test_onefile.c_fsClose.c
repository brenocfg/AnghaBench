#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_9__ {scalar_t__ nRef; TYPE_5__* pFile; TYPE_1__** ppThis; TYPE_1__* pNext; } ;
typedef  TYPE_3__ fs_real_file ;
struct TYPE_10__ {TYPE_3__* pReal; } ;
typedef  TYPE_4__ fs_file ;
struct TYPE_11__ {TYPE_2__* pMethods; } ;
struct TYPE_8__ {int (* xClose ) (TYPE_5__*) ;} ;
struct TYPE_7__ {struct TYPE_7__** ppThis; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int stub1 (TYPE_5__*) ; 

__attribute__((used)) static int fsClose(sqlite3_file *pFile){
  int rc = SQLITE_OK;
  fs_file *p = (fs_file *)pFile;
  fs_real_file *pReal = p->pReal;

  /* Decrement the real_file ref-count. */
  pReal->nRef--;
  assert(pReal->nRef>=0);

  /* When the ref-count reaches 0, destroy the structure */
  if( pReal->nRef==0 ){
    *pReal->ppThis = pReal->pNext;
    if( pReal->pNext ){
      pReal->pNext->ppThis = pReal->ppThis;
    }
    rc = pReal->pFile->pMethods->xClose(pReal->pFile);
    sqlite3_free(pReal);
  }

  return rc;
}