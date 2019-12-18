#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int readLock; } ;
typedef  TYPE_1__ Wal ;

/* Variables and functions */
 int /*<<< orphan*/  WAL_READ_LOCK (int) ; 
 int /*<<< orphan*/  sqlite3WalEndWriteTransaction (TYPE_1__*) ; 
 int /*<<< orphan*/  walUnlockShared (TYPE_1__*,int /*<<< orphan*/ ) ; 

void sqlite3WalEndReadTransaction(Wal *pWal){
  sqlite3WalEndWriteTransaction(pWal);
  if( pWal->readLock>=0 ){
    walUnlockShared(pWal, WAL_READ_LOCK(pWal->readLock));
    pWal->readLock = -1;
  }
}