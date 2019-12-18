#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONGLONG ;
struct TYPE_14__ {struct TYPE_14__* Buffer; } ;
typedef  int /*<<< orphan*/  TUNNEL ;
typedef  int SIZE_T ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BufSize ; 
 TYPE_1__* CopyUS (TYPE_1__*) ; 
 TYPE_1__* ExAllocatePool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePool (TYPE_1__*) ; 
 int /*<<< orphan*/  FsRtlAddToTunnelCache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PagedPool ; 
 int RtlCompareMemory (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlCompareUnicodeString (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

void TestFsRtlAddToTunnelCache(ULONGLONG DirectoryKey, PUNICODE_STRING s_name, PUNICODE_STRING l_name, BOOLEAN KeyByShortName)
{
    SIZE_T eq;
    LONG b;
    PUNICODE_STRING bs_name;
    PUNICODE_STRING bl_name;
    PVOID Bufb;
    PVOID Buf;

    Buf = ExAllocatePool(PagedPool, BufSize);
    ok(Buf != NULL, "Buff in TestFsRtlAddToTunnelCache is NULL after allocated memory\n");
    Bufb = ExAllocatePool(PagedPool, BufSize);
    ok(Bufb != NULL, "Buff in TestFsRtlAddToTunnelCache is NULL after allocated memory\n");

    // Allocate memory for the  bufs_name
    bs_name = CopyUS(s_name);

    // Allocate memory for the l_name and bl_name
    bl_name = CopyUS(l_name);

    memset((void*)Buf, 0, BufSize);
    memset((void*)Bufb, 0, BufSize);

    FsRtlAddToTunnelCache(T, DirectoryKey, s_name, l_name, KeyByShortName, BufSize, Buf);

    eq = RtlCompareMemory((const VOID*)Buf, (const VOID*)Bufb,  BufSize);

    ok( eq !=  sizeof(TUNNEL),"FsRtlAddToTunnelCache function did not change anything in the memory at the address Buf.\n"); 

    b = RtlCompareUnicodeString(l_name, bl_name, TRUE);
    ok (b == 0, "long name after call FsRtlAddToTunnelCache != long name befo call FsRtlAddToTunnelCache\n\n");
    b = RtlCompareUnicodeString(s_name, bs_name, TRUE);
    ok (b == 0, "short name after call FsRtlAddToTunnelCache != short name befo call FsRtlAddToTunnelCache\n\n");

    if (bs_name->Buffer) ExFreePool(bs_name->Buffer);
    ExFreePool(bs_name);
    if (bl_name->Buffer) ExFreePool(bl_name->Buffer);
    ExFreePool(bl_name);
    ExFreePool(Bufb);
    ExFreePool(Buf);
}