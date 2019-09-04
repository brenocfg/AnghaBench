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
 int /*<<< orphan*/  PathStripPathA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_PathStripPathA(void)
{
    const char const_path[] = "test";
    char path[] = "short//path\\file.txt";

    PathStripPathA(path);
    ok(!strcmp(path, "file.txt"), "path = %s\n", path);

    /* following test should not crash */
    /* LavView 2013 depends on that behaviour */
    PathStripPathA((char*)const_path);
}