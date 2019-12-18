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
typedef  int /*<<< orphan*/  teststring ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int Length; int MaximumLength; int /*<<< orphan*/  const* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * STRINGW ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  pRtlInitUnicodeString (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void test_RtlInitUnicodeString(void)
{
#define STRINGW {'S','o','m','e',' ','W','i','l','d',' ','S','t','r','i','n','g',0}
    static const WCHAR teststring[] = STRINGW;
    static const WCHAR originalstring[] = STRINGW;
#undef STRINGW
    UNICODE_STRING uni;

    uni.Length = 0;
    uni.MaximumLength = 0;
    uni.Buffer = (void *)0xdeadbeef;
    pRtlInitUnicodeString(&uni, teststring);
    ok(uni.Length == sizeof(teststring) - sizeof(WCHAR), "Length uninitialized\n");
    ok(uni.MaximumLength == sizeof(teststring), "MaximumLength uninitialized\n");
    ok(uni.Buffer == teststring, "Buffer not equal to teststring\n");
    ok(lstrcmpW(uni.Buffer, originalstring) == 0, "Buffer written to\n");
    pRtlInitUnicodeString(&uni, NULL);
    ok(uni.Length == 0, "Length uninitialized\n");
    ok(uni.MaximumLength == 0, "MaximumLength uninitialized\n");
    ok(uni.Buffer == NULL, "Buffer not equal to NULL\n");
/*  pRtlInitUnicodeString(NULL, teststring); */
}