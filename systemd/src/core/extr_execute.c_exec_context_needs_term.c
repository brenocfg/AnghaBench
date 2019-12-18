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
struct TYPE_4__ {int /*<<< orphan*/  tty_path; int /*<<< orphan*/  std_error; int /*<<< orphan*/  std_output; int /*<<< orphan*/  std_input; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ is_terminal_input (int /*<<< orphan*/ ) ; 
 scalar_t__ is_terminal_output (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool exec_context_needs_term(const ExecContext *c) {
        assert(c);

        /* Return true if the execution context suggests we should set $TERM to something useful. */

        if (is_terminal_input(c->std_input))
                return true;

        if (is_terminal_output(c->std_output))
                return true;

        if (is_terminal_output(c->std_error))
                return true;

        return !!c->tty_path;
}