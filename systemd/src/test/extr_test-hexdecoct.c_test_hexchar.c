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
 int /*<<< orphan*/  assert_se (int) ; 
 char hexchar (int) ; 

__attribute__((used)) static void test_hexchar(void) {
        assert_se(hexchar(0xa) == 'a');
        assert_se(hexchar(0x0) == '0');
}