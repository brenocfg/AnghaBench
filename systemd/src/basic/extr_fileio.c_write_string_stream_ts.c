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
struct timespec {int dummy; } ;
typedef  int WriteStringFileFlags ;
typedef  char const FILE ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ EOF ; 
 int WRITE_STRING_FILE_AVOID_NEWLINE ; 
 int WRITE_STRING_FILE_DISABLE_BUFFER ; 
 int WRITE_STRING_FILE_SYNC ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  endswith (char const*,char*) ; 
 int errno ; 
 scalar_t__ ferror (char const*) ; 
 int fflush_and_check (char const*) ; 
 int fflush_sync_and_check (char const*) ; 
 int /*<<< orphan*/  fileno (char const*) ; 
 scalar_t__ fputc (char,char const*) ; 
 scalar_t__ fputs (char const*,char const*) ; 
 scalar_t__ futimens (int /*<<< orphan*/ ,struct timespec*) ; 
 char* strjoina (char const*,char*) ; 

int write_string_stream_ts(
                FILE *f,
                const char *line,
                WriteStringFileFlags flags,
                struct timespec *ts) {

        bool needs_nl;
        int r;

        assert(f);
        assert(line);

        if (ferror(f))
                return -EIO;

        needs_nl = !(flags & WRITE_STRING_FILE_AVOID_NEWLINE) && !endswith(line, "\n");

        if (needs_nl && (flags & WRITE_STRING_FILE_DISABLE_BUFFER)) {
                /* If STDIO buffering was disabled, then let's append the newline character to the string itself, so
                 * that the write goes out in one go, instead of two */

                line = strjoina(line, "\n");
                needs_nl = false;
        }

        if (fputs(line, f) == EOF)
                return -errno;

        if (needs_nl)
                if (fputc('\n', f) == EOF)
                        return -errno;

        if (flags & WRITE_STRING_FILE_SYNC)
                r = fflush_sync_and_check(f);
        else
                r = fflush_and_check(f);
        if (r < 0)
                return r;

        if (ts) {
                struct timespec twice[2] = {*ts, *ts};

                if (futimens(fileno(f), twice) < 0)
                        return -errno;
        }

        return 0;
}