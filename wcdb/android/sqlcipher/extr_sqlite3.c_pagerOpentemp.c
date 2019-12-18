#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_3__ {int /*<<< orphan*/  pVfs; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_EXCLUSIVE ; 
 int SQLITE_OPEN_READWRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ *) ; 
 int sqlite3OsOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_opentemp_count ; 

__attribute__((used)) static int pagerOpentemp(
  Pager *pPager,        /* The pager object */
  sqlite3_file *pFile,  /* Write the file descriptor here */
  int vfsFlags          /* Flags passed through to the VFS */
){
  int rc;               /* Return code */

#ifdef SQLITE_TEST
  sqlite3_opentemp_count++;  /* Used for testing and analysis only */
#endif

  vfsFlags |=  SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
            SQLITE_OPEN_EXCLUSIVE | SQLITE_OPEN_DELETEONCLOSE;
  rc = sqlite3OsOpen(pPager->pVfs, 0, pFile, vfsFlags, 0);
  assert( rc!=SQLITE_OK || isOpen(pFile) );
  return rc;
}