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
struct TYPE_3__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ quota_FILE ;

/* Variables and functions */
 int _commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int fsync (int /*<<< orphan*/ ) ; 

int sqlite3_quota_fflush(quota_FILE *p, int doFsync){
  int rc;
  rc = fflush(p->f);
  if( rc==0 && doFsync ){
#if SQLITE_OS_UNIX
    rc = fsync(fileno(p->f));
#endif
#if SQLITE_OS_WIN
    rc = _commit(_fileno(p->f));
#endif
  }
  return rc!=0;
}