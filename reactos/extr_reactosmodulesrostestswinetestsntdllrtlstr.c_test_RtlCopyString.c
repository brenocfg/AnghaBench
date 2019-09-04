#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  pRtlCopyString (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pRtlInitString (TYPE_1__*,char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_RtlCopyString(void)
{
    static const char teststring[] = "Some Wild String";
    char deststring[] = "                    ";
    STRING str;
    STRING deststr;

    pRtlInitString(&str, teststring);
    pRtlInitString(&deststr, deststring);
    pRtlCopyString(&deststr, &str);
    ok(strncmp(str.Buffer, deststring, str.Length) == 0, "String not copied\n");
}