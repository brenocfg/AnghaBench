#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ FullVersion; } ;
typedef  TYPE_1__ VersionLieInfo ;
struct TYPE_6__ {scalar_t__ ReplacementFunction; } ;
typedef  TYPE_2__* PHOOKAPI ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  scalar_t__ (* GETVERSIONPROC ) () ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  skip (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  winetest_ok (int,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verify_shim_imp(PHOOKAPI hook, const VersionLieInfo* info, PCSTR shim, int same)
{
    DWORD ver;
    if (!same)
    {
        skip("Skipping implementation tests for %s\n", shim);
        return;
    }
    ver = ((GETVERSIONPROC)hook->ReplacementFunction)();
    winetest_ok(info->FullVersion == ver, "Expected GetVersion to return 0x%x, was: 0x%x for %s\n", info->FullVersion, ver, shim);
}