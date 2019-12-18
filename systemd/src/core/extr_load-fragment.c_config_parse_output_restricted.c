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
typedef  scalar_t__ ExecOutput ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OUTPUT_FILE ; 
 int /*<<< orphan*/  EXEC_OUTPUT_FILE_APPEND ; 
 int /*<<< orphan*/  EXEC_OUTPUT_NAMED_FD ; 
 int /*<<< orphan*/  EXEC_OUTPUT_SOCKET ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 scalar_t__ exec_output_from_string (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,char*,char const*) ; 

int config_parse_output_restricted(
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

        ExecOutput t, *eo = data;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        t = exec_output_from_string(rvalue);
        if (t < 0) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "Failed to parse output type, ignoring: %s", rvalue);
                return 0;
        }

        if (IN_SET(t, EXEC_OUTPUT_SOCKET, EXEC_OUTPUT_NAMED_FD, EXEC_OUTPUT_FILE, EXEC_OUTPUT_FILE_APPEND)) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "Standard output types socket, fd:, file:, append: are not supported as defaults, ignoring: %s", rvalue);
                return 0;
        }

        *eo = t;
        return 0;
}