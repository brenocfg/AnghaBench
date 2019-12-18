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
typedef  int /*<<< orphan*/  ShowStatus ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_show_status (char const*,int /*<<< orphan*/ *) ; 

int config_parse_show_status(
                const char* unit,
                const char *filename,
                unsigned line,
                const char *section,
                unsigned section_line,
                const char *lvalue,
                int ltype,
                const char *rvalue,
                void *data,
                void *userdata) {

        int k;
        ShowStatus *b = data;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        k = parse_show_status(rvalue, b);
        if (k < 0) {
                log_syntax(unit, LOG_ERR, filename, line, k, "Failed to parse show status setting, ignoring: %s", rvalue);
                return 0;
        }

        return 0;
}