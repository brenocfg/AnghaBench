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
 int /*<<< orphan*/  test_bad (char*) ; 
 int /*<<< orphan*/  test_empty () ; 
 int /*<<< orphan*/  test_good () ; 

int main(void)
{
    test_good();
    test_empty();
    test_bad("");
    test_bad("A\r\n" "123456789");
    test_bad("Z\r\n" "123456789");

    return 0;
}