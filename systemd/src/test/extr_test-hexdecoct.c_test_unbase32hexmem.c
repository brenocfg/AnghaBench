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
 int /*<<< orphan*/  test_unbase32hexmem_one (char*,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_unbase32hexmem(void) {
        test_unbase32hexmem_one("", true, 0, "");

        test_unbase32hexmem_one("CO======", true, 0, "f");
        test_unbase32hexmem_one("CPNG====", true, 0, "fo");
        test_unbase32hexmem_one("CPNMU===", true, 0, "foo");
        test_unbase32hexmem_one("CPNMUOG=", true, 0, "foob");
        test_unbase32hexmem_one("CPNMUOJ1", true, 0, "fooba");
        test_unbase32hexmem_one("CPNMUOJ1E8======", true, 0, "foobar");

        test_unbase32hexmem_one("A", true, -EINVAL, NULL);
        test_unbase32hexmem_one("A=======", true, -EINVAL, NULL);
        test_unbase32hexmem_one("AAA=====", true, -EINVAL, NULL);
        test_unbase32hexmem_one("AAAAAA==", true, -EINVAL, NULL);
        test_unbase32hexmem_one("AB======", true, -EINVAL, NULL);
        test_unbase32hexmem_one("AAAB====", true, -EINVAL, NULL);
        test_unbase32hexmem_one("AAAAB===", true, -EINVAL, NULL);
        test_unbase32hexmem_one("AAAAAAB=", true, -EINVAL, NULL);

        test_unbase32hexmem_one("XPNMUOJ1", true, -EINVAL, NULL);
        test_unbase32hexmem_one("CXNMUOJ1", true, -EINVAL, NULL);
        test_unbase32hexmem_one("CPXMUOJ1", true, -EINVAL, NULL);
        test_unbase32hexmem_one("CPNXUOJ1", true, -EINVAL, NULL);
        test_unbase32hexmem_one("CPNMXOJ1", true, -EINVAL, NULL);
        test_unbase32hexmem_one("CPNMUXJ1", true, -EINVAL, NULL);
        test_unbase32hexmem_one("CPNMUOX1", true, -EINVAL, NULL);
        test_unbase32hexmem_one("CPNMUOJX", true, -EINVAL, NULL);

        test_unbase32hexmem_one("", false, 0, "");
        test_unbase32hexmem_one("CO", false, 0, "f");
        test_unbase32hexmem_one("CPNG", false, 0, "fo");
        test_unbase32hexmem_one("CPNMU", false, 0, "foo");
        test_unbase32hexmem_one("CPNMUOG", false, 0, "foob");
        test_unbase32hexmem_one("CPNMUOJ1", false, 0, "fooba");
        test_unbase32hexmem_one("CPNMUOJ1E8", false, 0, "foobar");
        test_unbase32hexmem_one("CPNMUOG=", false, -EINVAL, NULL);
        test_unbase32hexmem_one("CPNMUOJ1E8======", false, -EINVAL, NULL);

        test_unbase32hexmem_one("A", false, -EINVAL, NULL);
        test_unbase32hexmem_one("AAA", false, -EINVAL, NULL);
        test_unbase32hexmem_one("AAAAAA", false, -EINVAL, NULL);
        test_unbase32hexmem_one("AB", false, -EINVAL, NULL);
        test_unbase32hexmem_one("AAAB", false, -EINVAL, NULL);
        test_unbase32hexmem_one("AAAAB", false, -EINVAL, NULL);
        test_unbase32hexmem_one("AAAAAAB", false, -EINVAL, NULL);
}