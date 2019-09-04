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
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int BufSize ; 
 int /*<<< orphan*/ * ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FsRtlFindInTunnelCache (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

BOOLEAN TestFsRtlFindInTunnelCache(ULONG DirectoryKey, PUNICODE_STRING name, PUNICODE_STRING s_name, PUNICODE_STRING l_name)
{
    // Allocate memory for the Buf
    ULONG BufsizeTemp = BufSize;
    PVOID Buf = ExAllocatePool(PagedPool, BufSize*2);
    ok(Buf != NULL, "Buff in FsRtlFindInTunnelCache is NULL after allocated memory\n");

    return FsRtlFindInTunnelCache(T, DirectoryKey, name, s_name, l_name, &BufsizeTemp, Buf); 
}