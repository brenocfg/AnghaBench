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
struct TYPE_6__ {int szUsable; } ;
typedef  TYPE_1__ ScrubState ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * scrubBackupAllocPage (TYPE_1__*) ; 
 int scrubBackupInt32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scrubBackupRead (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scrubBackupWrite (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scrubBackupOverflow(ScrubState *p, int pgno, u32 nByte){
  u8 *a, *aBuf;

  aBuf = scrubBackupAllocPage(p);
  if( aBuf==0 ) return;
  while( nByte>0 && pgno!=0 ){
    a = scrubBackupRead(p, pgno, aBuf);
    if( a==0 ) break;
    if( nByte >= (p->szUsable)-4 ){
      nByte -= (p->szUsable) - 4;
    }else{
      u32 x = (p->szUsable - 4) - nByte;
      u32 i = p->szUsable - x;
      memset(&a[i], 0, x);
      nByte = 0;
    }
    scrubBackupWrite(p, pgno, a);
    pgno = scrubBackupInt32(a);
  }
  sqlite3_free(aBuf);      
}