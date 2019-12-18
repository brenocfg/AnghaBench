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
typedef  int u32 ;
struct TYPE_6__ {int szUsable; int szPage; scalar_t__ rcErr; } ;
typedef  TYPE_1__ ScrubState ;

/* Variables and functions */
 int /*<<< orphan*/ * aZero ; 
 int i ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * scrubBackupAllocPage (TYPE_1__*) ; 
 int scrubBackupInt32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scrubBackupRead (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scrubBackupWrite (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scrubBackupFreelist(ScrubState *p, int pgno, u32 nFree){
  u8 *a, *aBuf;
  u32 n, mx;

  if( p->rcErr ) return;
  aBuf = scrubBackupAllocPage(p);
  if( aBuf==0 ) return;
 
  while( pgno && nFree){
    a = scrubBackupRead(p, pgno, aBuf);
    if( a==0 ) break;
    n = scrubBackupInt32(&a[4]);
    mx = p->szUsable/4 - 2;
    if( n<mx ){
      memset(&a[n*4+8], 0, 4*(mx-n));
    }
    scrubBackupWrite(p, pgno, a);
    pgno = scrubBackupInt32(a);
#if 0
    /* There is really no point in copying the freelist leaf pages.
    ** Simply leave them uninitialized in the destination database.  The
    ** OS filesystem should zero those pages for us automatically.
    */
    for(i=0; i<n && nFree; i++){
      u32 iLeaf = scrubBackupInt32(&a[i*4+8]);
      if( aZero==0 ){
        aZero = scrubBackupAllocPage(p);
        if( aZero==0 ){ pgno = 0; break; }
        memset(aZero, 0, p->szPage);
      }
      scrubBackupWrite(p, iLeaf, aZero);
      nFree--;
    }
#endif
  }
  sqlite3_free(aBuf);
}