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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPIPE ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  test_unhexmem_one (char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_unhexmem(void) {
        const char *hex = "efa2149213";
        const char *hex_space = "  e f   a\n 2\r  14\n\r\t9\t2 \n1\r3 \r\r\t";
        const char *hex_invalid = "efa214921o";

        test_unhexmem_one(NULL, 0, 0);
        test_unhexmem_one("", 0, 0);
        test_unhexmem_one("", (size_t) -1, 0);
        test_unhexmem_one("   \n \t\r   \t\t \n\n\n", (size_t) -1, 0);
        test_unhexmem_one(hex_invalid, strlen(hex_invalid), -EINVAL);
        test_unhexmem_one(hex_invalid, (size_t) - 1, -EINVAL);
        test_unhexmem_one(hex, strlen(hex) - 1, -EPIPE);
        test_unhexmem_one(hex, strlen(hex), 0);
        test_unhexmem_one(hex, (size_t) -1, 0);
        test_unhexmem_one(hex_space, strlen(hex_space), 0);
        test_unhexmem_one(hex_space, (size_t) -1, 0);
}