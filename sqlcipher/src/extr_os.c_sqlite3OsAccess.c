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
struct TYPE_4__ {int (* xAccess ) (TYPE_1__*,char const*,int,int*) ;} ;
typedef  TYPE_1__ sqlite3_vfs ;

/* Variables and functions */
 int /*<<< orphan*/  DO_OS_MALLOC_TEST (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,char const*,int,int*) ; 

int sqlite3OsAccess(
  sqlite3_vfs *pVfs,
  const char *zPath,
  int flags,
  int *pResOut
){
  DO_OS_MALLOC_TEST(0);
  return pVfs->xAccess(pVfs, zPath, flags, pResOut);
}