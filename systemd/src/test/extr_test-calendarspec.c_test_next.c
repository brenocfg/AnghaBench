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
typedef  int /*<<< orphan*/  CalendarSpec ;

/* Variables and functions */
 int ENOENT ; 
 int FORMAT_TIMESTAMP_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  calendar_spec_free (int /*<<< orphan*/ *) ; 
 scalar_t__ calendar_spec_from_string (char const*,int /*<<< orphan*/ **) ; 
 int calendar_spec_next_usec (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 char* format_timestamp_us (char*,int,scalar_t__) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ setenv (char*,char*,int) ; 
 char* strdupa (char*) ; 
 char* strerror_safe (int) ; 
 char* strjoina (char*,char const*) ; 
 int /*<<< orphan*/  tzset () ; 
 scalar_t__ unsetenv (char*) ; 

__attribute__((used)) static void test_next(const char *input, const char *new_tz, usec_t after, usec_t expect) {
        CalendarSpec *c;
        usec_t u;
        char *old_tz;
        char buf[FORMAT_TIMESTAMP_MAX];
        int r;

        old_tz = getenv("TZ");
        if (old_tz)
                old_tz = strdupa(old_tz);

        if (new_tz) {
                char *colon_tz;

                colon_tz = strjoina(":", new_tz);
                assert_se(setenv("TZ", colon_tz, 1) >= 0);
        } else
                assert_se(unsetenv("TZ") >= 0);
        tzset();

        assert_se(calendar_spec_from_string(input, &c) >= 0);

        printf("\"%s\"\n", input);

        u = after;
        r = calendar_spec_next_usec(c, after, &u);
        printf("At: %s\n", r < 0 ? strerror_safe(r) : format_timestamp_us(buf, sizeof buf, u));
        if (expect != (usec_t)-1)
                assert_se(r >= 0 && u == expect);
        else
                assert(r == -ENOENT);

        calendar_spec_free(c);

        if (old_tz)
                assert_se(setenv("TZ", old_tz, 1) >= 0);
        else
                assert_se(unsetenv("TZ") >= 0);
        tzset();
}