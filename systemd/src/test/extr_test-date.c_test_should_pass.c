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
typedef  scalar_t__ usec_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  buf_relative ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FORMAT_TIMESTAMP_MAX ; 
 int FORMAT_TIMESTAMP_RELATIVE_MAX ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int format_timestamp_relative (char*,int,scalar_t__) ; 
 int format_timestamp_us (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  log_error (char*,char*,int) ; 
 int /*<<< orphan*/  log_info (char*,char const*,...) ; 
 scalar_t__ parse_timestamp (char const*,scalar_t__*) ; 
 char const* strna (char*) ; 

__attribute__((used)) static void test_should_pass(const char *p) {
        usec_t t, q;
        char buf[FORMAT_TIMESTAMP_MAX], buf_relative[FORMAT_TIMESTAMP_RELATIVE_MAX];

        log_info("Test: %s", p);
        assert_se(parse_timestamp(p, &t) >= 0);
        assert_se(format_timestamp_us(buf, sizeof(buf), t));
        log_info("\"%s\" → \"%s\"", p, buf);

        assert_se(parse_timestamp(buf, &q) >= 0);
        if (q != t) {
                char tmp[FORMAT_TIMESTAMP_MAX];

                log_error("round-trip failed: \"%s\" → \"%s\"",
                          buf, format_timestamp_us(tmp, sizeof(tmp), q));
        }
        assert_se(q == t);

        assert_se(format_timestamp_relative(buf_relative, sizeof(buf_relative), t));
        log_info("%s", strna(buf_relative));
}