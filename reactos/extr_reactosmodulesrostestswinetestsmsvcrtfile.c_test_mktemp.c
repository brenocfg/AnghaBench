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
 int /*<<< orphan*/ * _mktemp (char*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_mktemp(void)
{
    char buf[16];

    strcpy(buf, "a");
    ok(!_mktemp(buf), "_mktemp(\"a\") != NULL\n");

    strcpy(buf, "testXXXXX");
    ok(!_mktemp(buf), "_mktemp(\"testXXXXX\") != NULL\n");

    strcpy(buf, "testXXXXXX");
    ok(_mktemp(buf) != NULL, "_mktemp(\"testXXXXXX\") == NULL\n");

    strcpy(buf, "testXXXXXXa");
    ok(!_mktemp(buf), "_mktemp(\"testXXXXXXa\") != NULL\n");

    strcpy(buf, "**XXXXXX");
    ok(_mktemp(buf) != NULL, "_mktemp(\"**XXXXXX\") == NULL\n");
}