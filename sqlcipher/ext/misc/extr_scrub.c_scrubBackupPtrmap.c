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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int szUsable; int szPage; scalar_t__ nPage; scalar_t__ rcErr; } ;
typedef  TYPE_1__ ScrubState ;

/* Variables and functions */
 int /*<<< orphan*/ * scrubBackupAllocPage (TYPE_1__*) ; 
 int /*<<< orphan*/ * scrubBackupRead (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scrubBackupWrite (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scrubBackupPtrmap(ScrubState *p){
  u32 pgno = 2;
  u32 J = p->szUsable/5;
  u32 iLock = (1073742335/p->szPage)+1;
  u8 *a, *pBuf;
  if( p->rcErr ) return;
  pBuf = scrubBackupAllocPage(p);
  if( pBuf==0 ) return;
  while( pgno<=p->nPage ){
    a = scrubBackupRead(p, pgno, pBuf);
    if( a==0 ) break;
    scrubBackupWrite(p, pgno, a);
    pgno += J+1;
    if( pgno==iLock ) pgno++;
  }
  sqlite3_free(pBuf);
}