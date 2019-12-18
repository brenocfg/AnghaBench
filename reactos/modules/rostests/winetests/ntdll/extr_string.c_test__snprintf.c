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
 scalar_t__ broken (int) ; 
 int lstrlenA (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p__snprintf (char*,int,char const*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void test__snprintf(void)
{
    const char *origstring = "XXXXXXXXXXXX";
    const char *teststring = "hello world";
    char buffer[32];
    int res;

    res = p__snprintf(NULL, 0, teststring);
    ok(res == lstrlenA(teststring) || broken(res == -1) /* <= w2k */,
       "_snprintf returned %d, expected %d.\n", res, lstrlenA(teststring));

    if (res != -1)
    {
        res = p__snprintf(NULL, 1, teststring);
        ok(res == lstrlenA(teststring) /* WinXP */ || res < 0 /* Vista and greater */,
           "_snprintf returned %d, expected %d or < 0.\n", res, lstrlenA(teststring));
    }
    res = p__snprintf(buffer, strlen(teststring) - 1, teststring);
    ok(res < 0, "_snprintf returned %d, expected < 0.\n", res);

    strcpy(buffer,  origstring);
    res = p__snprintf(buffer, strlen(teststring), teststring);
    ok(res == lstrlenA(teststring), "_snprintf returned %d, expected %d.\n", res, lstrlenA(teststring));
    ok(!strcmp(buffer, "hello worldX"), "_snprintf returned buffer '%s', expected 'hello worldX'.\n", buffer);

    strcpy(buffer, origstring);
    res = p__snprintf(buffer, strlen(teststring) + 1, teststring);
    ok(res == lstrlenA(teststring), "_snprintf returned %d, expected %d.\n", res, lstrlenA(teststring));
    ok(!strcmp(buffer, teststring), "_snprintf returned buffer '%s', expected '%s'.\n", buffer, teststring);
}