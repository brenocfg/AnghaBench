#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ nRef; scalar_t__ hShm; int /*<<< orphan*/  zFilename; int /*<<< orphan*/  pShmMutex; TYPE_3__* pFirst; TYPE_1__* pInode; } ;
typedef  TYPE_2__ unixShmNode ;
struct TYPE_10__ {struct TYPE_10__* pNext; TYPE_2__* pShmNode; } ;
typedef  TYPE_3__ unixShm ;
struct TYPE_11__ {TYPE_3__* pShm; TYPE_1__* pInode; } ;
typedef  TYPE_4__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_8__ {TYPE_2__* pShmNode; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  osUnlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unixEnterMutex () ; 
 int unixFileMutexNotheld (TYPE_4__*) ; 
 int /*<<< orphan*/  unixLeaveMutex () ; 
 int /*<<< orphan*/  unixShmPurge (TYPE_4__*) ; 

__attribute__((used)) static int unixShmUnmap(
  sqlite3_file *fd,               /* The underlying database file */
  int deleteFlag                  /* Delete shared-memory if true */
){
  unixShm *p;                     /* The connection to be closed */
  unixShmNode *pShmNode;          /* The underlying shared-memory file */
  unixShm **pp;                   /* For looping over sibling connections */
  unixFile *pDbFd;                /* The underlying database file */

  pDbFd = (unixFile*)fd;
  p = pDbFd->pShm;
  if( p==0 ) return SQLITE_OK;
  pShmNode = p->pShmNode;

  assert( pShmNode==pDbFd->pInode->pShmNode );
  assert( pShmNode->pInode==pDbFd->pInode );

  /* Remove connection p from the set of connections associated
  ** with pShmNode */
  sqlite3_mutex_enter(pShmNode->pShmMutex);
  for(pp=&pShmNode->pFirst; (*pp)!=p; pp = &(*pp)->pNext){}
  *pp = p->pNext;

  /* Free the connection p */
  sqlite3_free(p);
  pDbFd->pShm = 0;
  sqlite3_mutex_leave(pShmNode->pShmMutex);

  /* If pShmNode->nRef has reached 0, then close the underlying
  ** shared-memory file, too */
  assert( unixFileMutexNotheld(pDbFd) );
  unixEnterMutex();
  assert( pShmNode->nRef>0 );
  pShmNode->nRef--;
  if( pShmNode->nRef==0 ){
    if( deleteFlag && pShmNode->hShm>=0 ){
      osUnlink(pShmNode->zFilename);
    }
    unixShmPurge(pDbFd);
  }
  unixLeaveMutex();

  return SQLITE_OK;
}