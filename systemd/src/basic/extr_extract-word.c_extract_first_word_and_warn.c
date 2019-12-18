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
typedef  int ExtractFlags ;

/* Variables and functions */
 int EINVAL ; 
 int EXTRACT_CUNESCAPE_RELAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int extract_first_word (char const**,char**,char const*,int) ; 
 int log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 

int extract_first_word_and_warn(
                const char **p,
                char **ret,
                const char *separators,
                ExtractFlags flags,
                const char *unit,
                const char *filename,
                unsigned line,
                const char *rvalue) {

        /* Try to unquote it, if it fails, warn about it and try again
         * but this time using EXTRACT_CUNESCAPE_RELAX to keep the
         * backslashes verbatim in invalid escape sequences. */

        const char *save;
        int r;

        save = *p;
        r = extract_first_word(p, ret, separators, flags);
        if (r >= 0)
                return r;

        if (r == -EINVAL && !(flags & EXTRACT_CUNESCAPE_RELAX)) {

                /* Retry it with EXTRACT_CUNESCAPE_RELAX. */
                *p = save;
                r = extract_first_word(p, ret, separators, flags|EXTRACT_CUNESCAPE_RELAX);
                if (r >= 0) {
                        /* It worked this time, hence it must have been an invalid escape sequence. */
                        log_syntax(unit, LOG_WARNING, filename, line, EINVAL, "Ignoring unknown escape sequences: \"%s\"", *ret);
                        return r;
                }

                /* If it's still EINVAL; then it must be unbalanced quoting, report this. */
                if (r == -EINVAL)
                        return log_syntax(unit, LOG_ERR, filename, line, r, "Unbalanced quoting, ignoring: \"%s\"", rvalue);
        }

        /* Can be any error, report it */
        return log_syntax(unit, LOG_ERR, filename, line, r, "Unable to decode word \"%s\", ignoring: %m", rvalue);
}