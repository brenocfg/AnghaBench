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
typedef  int /*<<< orphan*/ * _INITTERMFUN ;

/* Variables and functions */
 int /*<<< orphan*/ * initcallback ; 
 int /*<<< orphan*/  initterm_test (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  p_initterm ; 

__attribute__((used)) static void test_initterm(void)
{
    int i;
    static _INITTERMFUN callbacks[4];

    if (!p_initterm)
        return;

    for (i = 0; i < 4; i++)
    {
        callbacks[i] = initcallback;
    }

    initterm_test(&callbacks[0], &callbacks[1], 1);
    initterm_test(&callbacks[0], &callbacks[2], 2);
    initterm_test(&callbacks[0], &callbacks[3], 3);

    callbacks[1] = NULL;
    initterm_test(&callbacks[0], &callbacks[3], 2);
}