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
typedef  int BOOL ;

/* Variables and functions */
 int SQLValidDSN (char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void test_SQLValidDSN(void)
{
    static const char *invalid = "[]{}(),;?*=!@\\";
    char str[10];
    int i;
    BOOL ret;

    strcpy(str, "wine10");
    for(i = 0; i < strlen(invalid); i++)
    {
        str[4] = invalid[i];
        ret = SQLValidDSN(str);
        ok(!ret, "got %d\n", ret);
    }

    /* Too large */
    ret = SQLValidDSN("Wine123456789012345678901234567890");
    ok(!ret, "got %d\n", ret);

    /* Valid with a space */
    ret = SQLValidDSN("Wine Vinegar");
    ok(ret, "got %d\n", ret);

    /* Max DSN name value */
    ret = SQLValidDSN("12345678901234567890123456789012");
    ok(ret, "got %d\n", ret);
}