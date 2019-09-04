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
 int /*<<< orphan*/  __getmainargs (int*,char***,char***,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ ** __p___argv () ; 
 char const** __p__acmdln () ; 
 int /*<<< orphan*/  winetest_ok (int,char*,int,int) ; 
 int /*<<< orphan*/  winetest_ok_str (char*,char const*) ; 

void
ok_argsA_imp(const char* input_args, const char* arg1, const char* arg2, const char* arg3)
{
    int argc = 0, mode = 0;
    int expect_count = arg3 == NULL ? (arg2 == NULL ? 2 : 3) : 4;
    char** argv, **env;

    /* Remove cached argv, setup our input as program argument. */
    *__p___argv() = NULL;
    *__p__acmdln() = input_args;

    /* Process the commandline stored in _acmdln */
    __getmainargs(&argc, &argv, &env, 0, &mode);

    winetest_ok(argc == expect_count, "Wrong value for argc, expected: %d, got: %d\n", expect_count, argc);
    if(argc != expect_count)
        return;

    winetest_ok_str(argv[0], "test.exe");
    winetest_ok_str(argv[1], arg1);
    if (expect_count > 2)
    {
        winetest_ok_str(argv[2], arg2);
        if (expect_count > 3)
            winetest_ok_str(argv[3], arg3);
    }
}