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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  TUNNEL ;
typedef  int SIZE_T ;

/* Variables and functions */
 void* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FsRtlInitializeTunnelCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PagedPool ; 
 int RtlCompareMemory (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * T ; 
 int /*<<< orphan*/ * Tb ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void TestFsRtlInitializeTunnelCache()
{
    SIZE_T eq;
    T = ExAllocatePool(PagedPool, sizeof(TUNNEL));
    ok(T != NULL, "PTUNEL is NULL after allocated memory\n");
    Tb = ExAllocatePool(PagedPool, sizeof(TUNNEL));
    ok(Tb != NULL, "PTUNEL is NULL after allocated memory\n");

    memset((void*)T, 0, sizeof(TUNNEL));
    memset((void*)Tb, 0, sizeof(TUNNEL));

    FsRtlInitializeTunnelCache(T);

    eq = RtlCompareMemory((const VOID*)T, (const VOID*)Tb,  sizeof(TUNNEL));

    ok ( eq != sizeof(TUNNEL), "FsRtlInitializeTunnelCache function did not change anything in the memory at the address PTUNEL.\n"); 
}