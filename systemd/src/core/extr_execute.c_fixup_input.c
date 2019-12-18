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
struct TYPE_4__ {scalar_t__ std_input; scalar_t__ stdin_data_size; } ;
typedef  scalar_t__ ExecInput ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 scalar_t__ EXEC_INPUT_DATA ; 
 int EXEC_INPUT_NULL ; 
 scalar_t__ EXEC_INPUT_SOCKET ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ is_terminal_input (scalar_t__) ; 

__attribute__((used)) static int fixup_input(
                const ExecContext *context,
                int socket_fd,
                bool apply_tty_stdin) {

        ExecInput std_input;

        assert(context);

        std_input = context->std_input;

        if (is_terminal_input(std_input) && !apply_tty_stdin)
                return EXEC_INPUT_NULL;

        if (std_input == EXEC_INPUT_SOCKET && socket_fd < 0)
                return EXEC_INPUT_NULL;

        if (std_input == EXEC_INPUT_DATA && context->stdin_data_size == 0)
                return EXEC_INPUT_NULL;

        return std_input;
}