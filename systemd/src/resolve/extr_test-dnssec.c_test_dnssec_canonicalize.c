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
 int EINVAL ; 
 int /*<<< orphan*/  test_dnssec_canonicalize_one (char*,char*,int) ; 

__attribute__((used)) static void test_dnssec_canonicalize(void) {
        test_dnssec_canonicalize_one("", ".", 1);
        test_dnssec_canonicalize_one(".", ".", 1);
        test_dnssec_canonicalize_one("foo", "foo.", 4);
        test_dnssec_canonicalize_one("foo.", "foo.", 4);
        test_dnssec_canonicalize_one("FOO.", "foo.", 4);
        test_dnssec_canonicalize_one("FOO.bar.", "foo.bar.", 8);
        test_dnssec_canonicalize_one("FOO..bar.", NULL, -EINVAL);
}