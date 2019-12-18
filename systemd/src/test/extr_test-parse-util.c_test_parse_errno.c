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
 int EILSEQ ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int parse_errno (char*) ; 

__attribute__((used)) static void test_parse_errno(void) {
        assert_se(parse_errno("EILSEQ") == EILSEQ);
        assert_se(parse_errno("EINVAL") == EINVAL);
        assert_se(parse_errno("0") == 0);
        assert_se(parse_errno("1") == 1);
        assert_se(parse_errno("4095") == 4095);

        assert_se(parse_errno("-1") == -ERANGE);
        assert_se(parse_errno("-3") == -ERANGE);
        assert_se(parse_errno("4096") == -ERANGE);

        assert_se(parse_errno("") == -EINVAL);
        assert_se(parse_errno("12.3") == -EINVAL);
        assert_se(parse_errno("123junk") == -EINVAL);
        assert_se(parse_errno("junk123") == -EINVAL);
        assert_se(parse_errno("255EILSEQ") == -EINVAL);
        assert_se(parse_errno("EINVAL12") == -EINVAL);
        assert_se(parse_errno("-EINVAL") == -EINVAL);
        assert_se(parse_errno("EINVALaaa") == -EINVAL);
}