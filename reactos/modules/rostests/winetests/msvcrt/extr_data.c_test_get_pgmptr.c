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
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p_get_pgmptr (char**) ; 

__attribute__((used)) static void test_get_pgmptr(void)
{
    char *pgm = NULL;
    int res;

    if (!p_get_pgmptr)
        return;

    res = p_get_pgmptr(&pgm);

    ok( res == 0, "Wrong _get_pgmptr return value %d expected 0\n", res);
    ok( pgm != NULL, "_get_pgmptr returned a NULL pointer\n" );
}