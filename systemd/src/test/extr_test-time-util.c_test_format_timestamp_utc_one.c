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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FORMAT_TIMESTAMP_MAX ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 char* format_timestamp_utc (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq_ptr (char const*,char const*) ; 

__attribute__((used)) static void test_format_timestamp_utc_one(usec_t val, const char *result) {
        char buf[FORMAT_TIMESTAMP_MAX];
        const char *t;

        t = format_timestamp_utc(buf, sizeof(buf), val);
        assert_se(streq_ptr(t, result));
}