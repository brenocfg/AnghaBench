#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int /*<<< orphan*/ * Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  Buf2 ;
typedef  int /*<<< orphan*/  Buf1 ;

/* Variables and functions */
 scalar_t__ RtlComputePrivatizedDllName_U (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlInitEmptyUnicodeString (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,char*) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  cleanup (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_strings (TYPE_1__*,TYPE_1__*,char*) ; 

__attribute__((used)) static void test_allocations(void)
{
    WCHAR Buf1[10];
    WCHAR Buf2[10];

    UNICODE_STRING Str1, Str2;
    UNICODE_STRING DllName;
    NTSTATUS Status;

    RtlInitEmptyUnicodeString(&Str1, Buf1, sizeof(Buf1));
    RtlInitEmptyUnicodeString(&Str2, Buf2, sizeof(Buf2));

    RtlInitUnicodeString(&DllName, L"kernel32.dll");
    Status = RtlComputePrivatizedDllName_U(&DllName, &Str1, &Str2);
    ok(Status == STATUS_SUCCESS, "0x%lx\n", Status);
    ok_strings(&Str1, &Str2, L"kernel32.dll");
    ok(Str1.Buffer != Buf1, "Expected a changed buffer\n");
    ok(Str2.Buffer != Buf2, "Expected a changed buffer\n");
    cleanup(&Str1, Buf1, sizeof(Buf1));
    cleanup(&Str2, Buf2, sizeof(Buf2));
}