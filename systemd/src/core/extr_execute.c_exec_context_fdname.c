#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * stdio_fdname; int /*<<< orphan*/  std_error; int /*<<< orphan*/  std_output; int /*<<< orphan*/  std_input; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_INPUT_NAMED_FD ; 
 int /*<<< orphan*/  EXEC_OUTPUT_NAMED_FD ; 
#define  STDERR_FILENO 130 
#define  STDIN_FILENO 129 
#define  STDOUT_FILENO 128 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

const char* exec_context_fdname(const ExecContext *c, int fd_index) {
        assert(c);

        switch (fd_index) {

        case STDIN_FILENO:
                if (c->std_input != EXEC_INPUT_NAMED_FD)
                        return NULL;

                return c->stdio_fdname[STDIN_FILENO] ?: "stdin";

        case STDOUT_FILENO:
                if (c->std_output != EXEC_OUTPUT_NAMED_FD)
                        return NULL;

                return c->stdio_fdname[STDOUT_FILENO] ?: "stdout";

        case STDERR_FILENO:
                if (c->std_error != EXEC_OUTPUT_NAMED_FD)
                        return NULL;

                return c->stdio_fdname[STDERR_FILENO] ?: "stderr";

        default:
                return NULL;
        }
}