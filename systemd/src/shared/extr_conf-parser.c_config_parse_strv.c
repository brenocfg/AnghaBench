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
 int ENOMEM ; 
 int EXTRACT_RETAIN_ESCAPE ; 
 int EXTRACT_UNQUOTE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int extract_first_word (char const**,char**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ isempty (char const*) ; 
 int log_oom () ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int strv_consume (char***,char*) ; 
 char** strv_free (char**) ; 

int config_parse_strv(
                const char *unit,
                const char *filename,
                unsigned line,
                const char *section,
                unsigned section_line,
                const char *lvalue,
                int ltype,
                const char *rvalue,
                void *data,
                void *userdata) {

        char ***sv = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue)) {
                *sv = strv_free(*sv);
                return 0;
        }

        for (;;) {
                char *word = NULL;

                r = extract_first_word(&rvalue, &word, NULL, EXTRACT_UNQUOTE|EXTRACT_RETAIN_ESCAPE);
                if (r == 0)
                        break;
                if (r == -ENOMEM)
                        return log_oom();
                if (r < 0) {
                        log_syntax(unit, LOG_ERR, filename, line, r, "Invalid syntax, ignoring: %s", rvalue);
                        break;
                }

                r = strv_consume(sv, word);
                if (r < 0)
                        return log_oom();
        }

        return 0;
}