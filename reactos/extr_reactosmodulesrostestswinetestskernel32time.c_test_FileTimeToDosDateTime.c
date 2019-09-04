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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ FILETIME ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ FileTimeToDosDateTime (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_FileTimeToDosDateTime(void)
{
    FILETIME ft = { 0 };
    WORD fatdate, fattime;
    BOOL ret;

    if (0)
    {
        /* Crashes */
        FileTimeToDosDateTime(NULL, NULL, NULL);
    }
    /* Parameter checking */
    SetLastError(0xdeadbeef);
    ret = FileTimeToDosDateTime(&ft, NULL, NULL);
    ok(!ret, "expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = FileTimeToDosDateTime(&ft, &fatdate, NULL);
    ok(!ret, "expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = FileTimeToDosDateTime(&ft, NULL, &fattime);
    ok(!ret, "expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = FileTimeToDosDateTime(&ft, &fatdate, &fattime);
    ok(!ret, "expected failure\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
}