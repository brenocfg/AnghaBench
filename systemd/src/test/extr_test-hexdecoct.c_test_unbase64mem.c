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
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  test_unbase64mem_one (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_unbase64mem(void) {

        test_unbase64mem_one("", "", 0);
        test_unbase64mem_one("Zg==", "f", 0);
        test_unbase64mem_one("Zm8=", "fo", 0);
        test_unbase64mem_one("Zm9v", "foo", 0);
        test_unbase64mem_one("Zm9vYg==", "foob", 0);
        test_unbase64mem_one("Zm9vYmE=", "fooba", 0);
        test_unbase64mem_one("Zm9vYmFy", "foobar", 0);

        test_unbase64mem_one(" ", "", 0);
        test_unbase64mem_one(" \n\r ", "", 0);
        test_unbase64mem_one("    Zg\n==       ", "f", 0);
        test_unbase64mem_one(" Zm 8=\r", "fo", 0);
        test_unbase64mem_one("  Zm9\n\r\r\nv   ", "foo", 0);
        test_unbase64mem_one(" Z m9vYg==\n\r", "foob", 0);
        test_unbase64mem_one(" Zm 9vYmE=   ", "fooba", 0);
        test_unbase64mem_one("   Z m9v    YmFy   ", "foobar", 0);

        test_unbase64mem_one("A", NULL, -EPIPE);
        test_unbase64mem_one("A====", NULL, -EINVAL);
        test_unbase64mem_one("AAB==", NULL, -EINVAL);
        test_unbase64mem_one(" A A A B = ", NULL, -EINVAL);
        test_unbase64mem_one(" Z m 8 = q u u x ", NULL, -ENAMETOOLONG);
}