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
 int /*<<< orphan*/  COMPRESS_PARSE_CHECK (char*,int,int) ; 

__attribute__((used)) static void test_config_compress(void) {
        COMPRESS_PARSE_CHECK("yes", true, 111);
        COMPRESS_PARSE_CHECK("no", false, 111);
        COMPRESS_PARSE_CHECK("y", true, 111);
        COMPRESS_PARSE_CHECK("n", false, 111);
        COMPRESS_PARSE_CHECK("true", true, 111);
        COMPRESS_PARSE_CHECK("false", false, 111);
        COMPRESS_PARSE_CHECK("t", true, 111);
        COMPRESS_PARSE_CHECK("f", false, 111);
        COMPRESS_PARSE_CHECK("on", true, 111);
        COMPRESS_PARSE_CHECK("off", false, 111);

        /* Weird size/bool overlapping case. We preserve backward compatibility instead of assuming these are byte
         * counts. */
        COMPRESS_PARSE_CHECK("1", true, 111);
        COMPRESS_PARSE_CHECK("0", false, 111);

        /* IEC sizing */
        COMPRESS_PARSE_CHECK("1B", true, 1);
        COMPRESS_PARSE_CHECK("1K", true, 1024);
        COMPRESS_PARSE_CHECK("1M", true, 1024 * 1024);
        COMPRESS_PARSE_CHECK("1G", true, 1024 * 1024 * 1024);

        /* Invalid Case */
        COMPRESS_PARSE_CHECK("-1", true, 111);
        COMPRESS_PARSE_CHECK("blah blah", true, 111);
        COMPRESS_PARSE_CHECK("", true, (uint64_t)-1);
}