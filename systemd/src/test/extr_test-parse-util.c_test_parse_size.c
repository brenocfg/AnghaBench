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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  parse_size (char*,int,int*) ; 

__attribute__((used)) static void test_parse_size(void) {
        uint64_t bytes;

        assert_se(parse_size("", 1024, &bytes) == -EINVAL);

        assert_se(parse_size("111", 1024, &bytes) == 0);
        assert_se(bytes == 111);

        assert_se(parse_size("111.4", 1024, &bytes) == 0);
        assert_se(bytes == 111);

        assert_se(parse_size(" 112 B", 1024, &bytes) == 0);
        assert_se(bytes == 112);

        assert_se(parse_size(" 112.6 B", 1024, &bytes) == 0);
        assert_se(bytes == 112);

        assert_se(parse_size("3.5 K", 1024, &bytes) == 0);
        assert_se(bytes == 3*1024 + 512);

        assert_se(parse_size("3. K", 1024, &bytes) == 0);
        assert_se(bytes == 3*1024);

        assert_se(parse_size("3.0 K", 1024, &bytes) == 0);
        assert_se(bytes == 3*1024);

        assert_se(parse_size("3. 0 K", 1024, &bytes) == -EINVAL);

        assert_se(parse_size(" 4 M 11.5K", 1024, &bytes) == 0);
        assert_se(bytes == 4*1024*1024 + 11 * 1024 + 512);

        assert_se(parse_size("3B3.5G", 1024, &bytes) == -EINVAL);

        assert_se(parse_size("3.5G3B", 1024, &bytes) == 0);
        assert_se(bytes == 3ULL*1024*1024*1024 + 512*1024*1024 + 3);

        assert_se(parse_size("3.5G 4B", 1024, &bytes) == 0);
        assert_se(bytes == 3ULL*1024*1024*1024 + 512*1024*1024 + 4);

        assert_se(parse_size("3B3G4T", 1024, &bytes) == -EINVAL);

        assert_se(parse_size("4T3G3B", 1024, &bytes) == 0);
        assert_se(bytes == (4ULL*1024 + 3)*1024*1024*1024 + 3);

        assert_se(parse_size(" 4 T 3 G 3 B", 1024, &bytes) == 0);
        assert_se(bytes == (4ULL*1024 + 3)*1024*1024*1024 + 3);

        assert_se(parse_size("12P", 1024, &bytes) == 0);
        assert_se(bytes == 12ULL * 1024*1024*1024*1024*1024);

        assert_se(parse_size("12P12P", 1024, &bytes) == -EINVAL);

        assert_se(parse_size("3E 2P", 1024, &bytes) == 0);
        assert_se(bytes == (3 * 1024 + 2ULL) * 1024*1024*1024*1024*1024);

        assert_se(parse_size("12X", 1024, &bytes) == -EINVAL);

        assert_se(parse_size("12.5X", 1024, &bytes) == -EINVAL);

        assert_se(parse_size("12.5e3", 1024, &bytes) == -EINVAL);

        assert_se(parse_size("1024E", 1024, &bytes) == -ERANGE);
        assert_se(parse_size("-1", 1024, &bytes) == -ERANGE);
        assert_se(parse_size("-1024E", 1024, &bytes) == -ERANGE);

        assert_se(parse_size("-1024P", 1024, &bytes) == -ERANGE);

        assert_se(parse_size("-10B 20K", 1024, &bytes) == -ERANGE);
}