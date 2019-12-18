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
 int /*<<< orphan*/  test_array_bsearch () ; 
 int /*<<< orphan*/  test_array_find () ; 
 int /*<<< orphan*/  test_array_foreach () ; 
 int /*<<< orphan*/  test_array_insert_remove () ; 

int main(void)
{
    test_array_insert_remove();
    test_array_foreach();
    test_array_find();
    test_array_bsearch();
}