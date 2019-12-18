#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ eState; int /*<<< orphan*/  journalMode; int /*<<< orphan*/  jfd; int /*<<< orphan*/  pWal; int /*<<< orphan*/  tempFile; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  PAGER_JOURNALMODE_WAL ; 
 scalar_t__ PAGER_OPEN ; 
 scalar_t__ PAGER_READER ; 
 int SQLITE_CANTOPEN ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_1__*) ; 
 int pagerOpenWal (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3OsClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PagerWalSupported (TYPE_1__*) ; 

int sqlite3PagerOpenWal(
  Pager *pPager,                  /* Pager object */
  int *pbOpen                     /* OUT: Set to true if call is a no-op */
){
  int rc = SQLITE_OK;             /* Return code */

  assert( assert_pager_state(pPager) );
  assert( pPager->eState==PAGER_OPEN   || pbOpen );
  assert( pPager->eState==PAGER_READER || !pbOpen );
  assert( pbOpen==0 || *pbOpen==0 );
  assert( pbOpen!=0 || (!pPager->tempFile && !pPager->pWal) );

  if( !pPager->tempFile && !pPager->pWal ){
    if( !sqlite3PagerWalSupported(pPager) ) return SQLITE_CANTOPEN;

    /* Close any rollback journal previously open */
    sqlite3OsClose(pPager->jfd);

    rc = pagerOpenWal(pPager);
    if( rc==SQLITE_OK ){
      pPager->journalMode = PAGER_JOURNALMODE_WAL;
      pPager->eState = PAGER_OPEN;
    }
  }else{
    *pbOpen = 1;
  }

  return rc;
}