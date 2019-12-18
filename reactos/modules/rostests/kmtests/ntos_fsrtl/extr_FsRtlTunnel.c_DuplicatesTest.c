#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int MaximumLength; scalar_t__ Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  TUNNEL ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PTUNNEL ;

/* Variables and functions */
 void* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExFreePool (scalar_t__) ; 
 int /*<<< orphan*/  FsRtlAddToTunnelCache (scalar_t__,int,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  FsRtlDeleteKeyFromTunnelCache (scalar_t__,int) ; 
 int /*<<< orphan*/  FsRtlDeleteTunnelCache (scalar_t__) ; 
 int /*<<< orphan*/  FsRtlFindInTunnelCache (scalar_t__,int,TYPE_1__*,TYPE_1__*,TYPE_1__*,int*,int*) ; 
 int /*<<< orphan*/  FsRtlInitializeTunnelCache (scalar_t__) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  RtlZeroMemory (scalar_t__,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  ok_bool_false (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_bool_true (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_eq_pointer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ok_eq_uint (int,int) ; 
 int /*<<< orphan*/  ok_eq_ulong (int,int) ; 

__attribute__((used)) static
void DuplicatesTest()
{
    UNICODE_STRING ShortName, LongName, OutShort, OutLong, ShortName2, LongName2;
    ULONG First, Second, OutLength, OutData;
    PTUNNEL Tunnel;
    PVOID Buffer;

    First = 1;
    Second = 2;
    RtlInitUnicodeString(&ShortName, L"LONGFI~1.TXT");
    RtlInitUnicodeString(&LongName, L"Longfilename.txt");
    RtlInitUnicodeString(&ShortName2, L"LONGFI~2.TXT");
    RtlInitUnicodeString(&LongName2, L"Longfilenamr.txt");
    Tunnel = ExAllocatePool(NonPagedPool, sizeof(TUNNEL));
    RtlZeroMemory(Tunnel, sizeof(TUNNEL));
    OutShort.MaximumLength = 13 * sizeof(WCHAR);
    OutShort.Buffer = ExAllocatePool(PagedPool, OutShort.MaximumLength);
    OutLong.MaximumLength = 17 * sizeof(WCHAR);
    OutLong.Buffer = Buffer = ExAllocatePool(PagedPool, OutLong.MaximumLength);

    FsRtlInitializeTunnelCache(Tunnel);
    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName, &LongName, TRUE, sizeof(ULONG), &First);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "First call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 1);
    ok_eq_pointer(OutLong.Buffer, Buffer);

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName, &LongName, TRUE, sizeof(ULONG), &Second);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Second call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);
    ok_eq_pointer(OutLong.Buffer, Buffer);

    OutLong.MaximumLength = 13 * sizeof(WCHAR);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Third call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);
    ok(OutLong.Buffer != Buffer, "Buffer didn't get reallocated!\n");
    ok_eq_uint(OutLong.MaximumLength, 16 * sizeof(WCHAR));

    FsRtlDeleteKeyFromTunnelCache(Tunnel, 1);
    ok_bool_false(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Fourth call");

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName, &LongName, TRUE, sizeof(ULONG), &First);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Fifth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 1);

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName2, &LongName2, TRUE, sizeof(ULONG), &First);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Sixth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 1);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName2, &OutShort, &OutLong, &OutLength, &OutData), "Seventh call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 1);

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName, &LongName, TRUE, sizeof(ULONG), &Second);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Eighth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName2, &OutShort, &OutLong, &OutLength, &OutData), "Ninth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 1);

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName2, &LongName2, TRUE, sizeof(ULONG), &Second);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Tenth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName2, &OutShort, &OutLong, &OutLength, &OutData), "Eleventh call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);

    FsRtlDeleteKeyFromTunnelCache(Tunnel, 1);
    ok_bool_false(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Twelfth call");
    ok_bool_false(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName2, &OutShort, &OutLong, &OutLength, &OutData), "Thirteenth call");

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName, &LongName, TRUE, sizeof(ULONG), &First);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Fourteenth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 1);

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName, &LongName, TRUE, sizeof(ULONG), &Second);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Fifteenth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName2, &LongName2, TRUE, sizeof(ULONG), &First);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Sixteenth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName2, &OutShort, &OutLong, &OutLength, &OutData), "Seventeenth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 1);

    FsRtlAddToTunnelCache(Tunnel, 1, &ShortName2, &LongName2, TRUE, sizeof(ULONG), &Second);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName, &OutShort, &OutLong, &OutLength, &OutData), "Eighteenth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);
    ok_bool_true(FsRtlFindInTunnelCache(Tunnel, 1, &ShortName2, &OutShort, &OutLong, &OutLength, &OutData), "Nineteenth call");
    ok_eq_ulong(OutLength, sizeof(ULONG));
    ok_eq_ulong(OutData, 2);

    FsRtlDeleteTunnelCache(Tunnel);
    ExFreePool(OutShort.Buffer);
    ExFreePool(OutLong.Buffer);
    ExFreePool(Buffer);
    ExFreePool(Tunnel);
}