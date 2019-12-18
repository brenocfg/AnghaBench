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
struct TYPE_4__ {scalar_t__ truncateOnCommit; scalar_t__ iReCksum; scalar_t__ writeLock; } ;
typedef  TYPE_1__ Wal ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  WAL_WRITE_LOCK ; 
 int /*<<< orphan*/  walUnlockExclusive (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int sqlite3WalEndWriteTransaction(Wal *pWal){
  if( pWal->writeLock ){
    walUnlockExclusive(pWal, WAL_WRITE_LOCK, 1);
    pWal->writeLock = 0;
    pWal->iReCksum = 0;
    pWal->truncateOnCommit = 0;
  }
  return SQLITE_OK;
}