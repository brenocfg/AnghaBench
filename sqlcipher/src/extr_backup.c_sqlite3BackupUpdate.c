#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_backup ;
typedef  int /*<<< orphan*/  Pgno ;

/* Variables and functions */
 int /*<<< orphan*/  backupUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void sqlite3BackupUpdate(sqlite3_backup *pBackup, Pgno iPage, const u8 *aData){
  if( pBackup ) backupUpdate(pBackup, iPage, aData);
}