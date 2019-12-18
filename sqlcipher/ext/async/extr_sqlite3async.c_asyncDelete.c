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
typedef  int /*<<< orphan*/  sqlite3_vfs ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_DELETE ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int addNewAsyncWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int asyncDelete(sqlite3_vfs *pAsyncVfs, const char *z, int syncDir){
  UNUSED_PARAMETER(pAsyncVfs);
  return addNewAsyncWrite(0, ASYNC_DELETE, syncDir, (int)strlen(z)+1, z);
}