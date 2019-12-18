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
typedef  char const FILE ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LONG_LINE_MAX ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  fputc (char,char const*) ; 
 int /*<<< orphan*/  fputs (char const*,char const*) ; 
 int /*<<< orphan*/  log_warning (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int serialize_item(FILE *f, const char *key, const char *value) {
        assert(f);
        assert(key);

        if (!value)
                return 0;

        /* Make sure that anything we serialize we can also read back again with read_line() with a maximum line size
         * of LONG_LINE_MAX. This is a safety net only. All code calling us should filter this out earlier anyway. */
        if (strlen(key) + 1 + strlen(value) + 1 > LONG_LINE_MAX) {
                log_warning("Attempted to serialize overly long item '%s', refusing.", key);
                return -EINVAL;
        }

        fputs(key, f);
        fputc('=', f);
        fputs(value, f);
        fputc('\n', f);

        return 1;
}