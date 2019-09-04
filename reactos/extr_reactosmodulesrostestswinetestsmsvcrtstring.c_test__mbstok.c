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

/* Variables and functions */
 unsigned char* _mbstok (int /*<<< orphan*/ *,unsigned char const*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,unsigned char*,...) ; 
 int /*<<< orphan*/  strtok (char*,char*) ; 

__attribute__((used)) static void test__mbstok(void)
{
    const unsigned char delim[] = "t";

    char str[] = "!.!test";
    unsigned char *ret;

    strtok(str, "!");

    ret = _mbstok(NULL, delim);
    /* most versions of msvcrt use the same buffer for strtok and _mbstok */
    ok(!ret || broken((char*)ret==str+4),
            "_mbstok(NULL, \"t\") = %p, expected NULL (%p)\n", ret, str);

    ret = _mbstok(NULL, delim);
    ok(!ret, "_mbstok(NULL, \"t\") = %p, expected NULL\n", ret);
}