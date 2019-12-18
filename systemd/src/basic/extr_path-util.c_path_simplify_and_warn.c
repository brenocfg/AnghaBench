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
 int /*<<< orphan*/  FLAGS_SET (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 unsigned int PATH_CHECK_ABSOLUTE ; 
 unsigned int PATH_CHECK_FATAL ; 
 unsigned int PATH_CHECK_RELATIVE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*,char*,char*) ; 
 int log_syntax_invalid_utf8 (char const*,int /*<<< orphan*/ ,char const*,unsigned int,char*) ; 
 int path_is_absolute (char*) ; 
 int /*<<< orphan*/  path_is_normalized (char*) ; 
 int /*<<< orphan*/  path_is_valid (char*) ; 
 int /*<<< orphan*/  path_simplify (char*,int) ; 
 char* strlen (char*) ; 
 int /*<<< orphan*/  utf8_is_valid (char*) ; 

int path_simplify_and_warn(
                char *path,
                unsigned flag,
                const char *unit,
                const char *filename,
                unsigned line,
                const char *lvalue) {

        bool fatal = flag & PATH_CHECK_FATAL;

        assert(!FLAGS_SET(flag, PATH_CHECK_ABSOLUTE | PATH_CHECK_RELATIVE));

        if (!utf8_is_valid(path))
                return log_syntax_invalid_utf8(unit, LOG_ERR, filename, line, path);

        if (flag & (PATH_CHECK_ABSOLUTE | PATH_CHECK_RELATIVE)) {
                bool absolute;

                absolute = path_is_absolute(path);

                if (!absolute && (flag & PATH_CHECK_ABSOLUTE))
                        return log_syntax(unit, LOG_ERR, filename, line, SYNTHETIC_ERRNO(EINVAL),
                                          "%s= path is not absolute%s: %s",
                                          lvalue, fatal ? "" : ", ignoring", path);

                if (absolute && (flag & PATH_CHECK_RELATIVE))
                        return log_syntax(unit, LOG_ERR, filename, line, SYNTHETIC_ERRNO(EINVAL),
                                          "%s= path is absolute%s: %s",
                                          lvalue, fatal ? "" : ", ignoring", path);
        }

        path_simplify(path, true);

        if (!path_is_valid(path))
                return log_syntax(unit, LOG_ERR, filename, line, SYNTHETIC_ERRNO(EINVAL),
                                  "%s= path has invalid length (%zu bytes)%s.",
                                  lvalue, strlen(path), fatal ? "" : ", ignoring");

        if (!path_is_normalized(path))
                return log_syntax(unit, LOG_ERR, filename, line, SYNTHETIC_ERRNO(EINVAL),
                                  "%s= path is not normalized%s: %s",
                                  lvalue, fatal ? "" : ", ignoring", path);

        return 0;
}