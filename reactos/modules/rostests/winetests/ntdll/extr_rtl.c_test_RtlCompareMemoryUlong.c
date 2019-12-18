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

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*,int*,int) ; 
 int pRtlCompareMemoryUlong (int*,int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlCompareMemoryUlong(void)
{
    ULONG a[10];
    ULONG result;

    if (!pRtlCompareMemoryUlong)
    {
        win_skip("RtlCompareMemoryUlong is not available\n");
        return;
    }

    a[0]= 0x0123;
    a[1]= 0x4567;
    a[2]= 0x89ab;
    a[3]= 0xcdef;
    result = pRtlCompareMemoryUlong(a, 0, 0x0123);
    ok(result == 0, "RtlCompareMemoryUlong(%p, 0, 0x0123) returns %u, expected 0\n", a, result);
    result = pRtlCompareMemoryUlong(a, 3, 0x0123);
    ok(result == 0, "RtlCompareMemoryUlong(%p, 3, 0x0123) returns %u, expected 0\n", a, result);
    result = pRtlCompareMemoryUlong(a, 4, 0x0123);
    ok(result == 4, "RtlCompareMemoryUlong(%p, 4, 0x0123) returns %u, expected 4\n", a, result);
    result = pRtlCompareMemoryUlong(a, 5, 0x0123);
    ok(result == 4, "RtlCompareMemoryUlong(%p, 5, 0x0123) returns %u, expected 4\n", a, result);
    result = pRtlCompareMemoryUlong(a, 7, 0x0123);
    ok(result == 4, "RtlCompareMemoryUlong(%p, 7, 0x0123) returns %u, expected 4\n", a, result);
    result = pRtlCompareMemoryUlong(a, 8, 0x0123);
    ok(result == 4, "RtlCompareMemoryUlong(%p, 8, 0x0123) returns %u, expected 4\n", a, result);
    result = pRtlCompareMemoryUlong(a, 9, 0x0123);
    ok(result == 4, "RtlCompareMemoryUlong(%p, 9, 0x0123) returns %u, expected 4\n", a, result);
    result = pRtlCompareMemoryUlong(a, 4, 0x0127);
    ok(result == 0, "RtlCompareMemoryUlong(%p, 4, 0x0127) returns %u, expected 0\n", a, result);
    result = pRtlCompareMemoryUlong(a, 4, 0x7123);
    ok(result == 0, "RtlCompareMemoryUlong(%p, 4, 0x7123) returns %u, expected 0\n", a, result);
    result = pRtlCompareMemoryUlong(a, 16, 0x4567);
    ok(result == 0, "RtlCompareMemoryUlong(%p, 16, 0x4567) returns %u, expected 0\n", a, result);

    a[1]= 0x0123;
    result = pRtlCompareMemoryUlong(a, 3, 0x0123);
    ok(result == 0, "RtlCompareMemoryUlong(%p, 3, 0x0123) returns %u, expected 0\n", a, result);
    result = pRtlCompareMemoryUlong(a, 4, 0x0123);
    ok(result == 4, "RtlCompareMemoryUlong(%p, 4, 0x0123) returns %u, expected 4\n", a, result);
    result = pRtlCompareMemoryUlong(a, 5, 0x0123);
    ok(result == 4, "RtlCompareMemoryUlong(%p, 5, 0x0123) returns %u, expected 4\n", a, result);
    result = pRtlCompareMemoryUlong(a, 7, 0x0123);
    ok(result == 4, "RtlCompareMemoryUlong(%p, 7, 0x0123) returns %u, expected 4\n", a, result);
    result = pRtlCompareMemoryUlong(a, 8, 0x0123);
    ok(result == 8, "RtlCompareMemoryUlong(%p, 8, 0x0123) returns %u, expected 8\n", a, result);
    result = pRtlCompareMemoryUlong(a, 9, 0x0123);
    ok(result == 8, "RtlCompareMemoryUlong(%p, 9, 0x0123) returns %u, expected 8\n", a, result);
}