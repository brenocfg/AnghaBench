#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
struct TYPE_2__ {char const* (* xNextSystemCall ) (int /*<<< orphan*/ *,char const*) ;} ;

/* Variables and functions */
 TYPE_1__* REALVFS (int /*<<< orphan*/ *) ; 
 char const* stub1 (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const char *vlogNextSystemCall(sqlite3_vfs *pVfs, const char *zName)
{
    return REALVFS(pVfs)->xNextSystemCall(pVfs, zName);
}