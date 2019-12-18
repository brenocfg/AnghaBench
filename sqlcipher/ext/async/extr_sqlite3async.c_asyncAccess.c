#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* xAccess ) (TYPE_2__*,char const*,int,int*) ;scalar_t__ pAppData; } ;
typedef  TYPE_2__ sqlite3_vfs ;
struct TYPE_10__ {TYPE_3__* pQueueFirst; } ;
struct TYPE_9__ {scalar_t__ op; TYPE_1__* pFileData; scalar_t__ zBuf; struct TYPE_9__* pNext; } ;
struct TYPE_7__ {scalar_t__ zName; } ;
typedef  TYPE_3__ AsyncWrite ;

/* Variables and functions */
 scalar_t__ ASYNC_DELETE ; 
 int /*<<< orphan*/  ASYNC_MUTEX_QUEUE ; 
 scalar_t__ ASYNC_OPENEXCLUSIVE ; 
 int /*<<< orphan*/  ASYNC_TRACE (char*) ; 
 int SQLITE_ACCESS_EXISTS ; 
 int SQLITE_ACCESS_READ ; 
 int SQLITE_ACCESS_READWRITE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__ async ; 
 int /*<<< orphan*/  async_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_mutex_leave (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 
 int stub1 (TYPE_2__*,char const*,int,int*) ; 

__attribute__((used)) static int asyncAccess(
  sqlite3_vfs *pAsyncVfs, 
  const char *zName, 
  int flags,
  int *pResOut
){
  int rc;
  int ret;
  AsyncWrite *p;
  sqlite3_vfs *pVfs = (sqlite3_vfs *)pAsyncVfs->pAppData;

  assert(flags==SQLITE_ACCESS_READWRITE 
      || flags==SQLITE_ACCESS_READ 
      || flags==SQLITE_ACCESS_EXISTS 
  );

  async_mutex_enter(ASYNC_MUTEX_QUEUE);
  rc = pVfs->xAccess(pVfs, zName, flags, &ret);
  if( rc==SQLITE_OK && flags==SQLITE_ACCESS_EXISTS ){
    for(p=async.pQueueFirst; p; p = p->pNext){
      if( p->op==ASYNC_DELETE && 0==strcmp(p->zBuf, zName) ){
        ret = 0;
      }else if( p->op==ASYNC_OPENEXCLUSIVE 
             && p->pFileData->zName
             && 0==strcmp(p->pFileData->zName, zName) 
      ){
        ret = 1;
      }
    }
  }
  ASYNC_TRACE(("ACCESS(%s): %s = %d\n", 
    flags==SQLITE_ACCESS_READWRITE?"read-write":
    flags==SQLITE_ACCESS_READ?"read":"exists"
    , zName, ret)
  );
  async_mutex_leave(ASYNC_MUTEX_QUEUE);
  *pResOut = ret;
  return rc;
}