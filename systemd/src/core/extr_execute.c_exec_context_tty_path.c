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
struct TYPE_4__ {char const* tty_path; scalar_t__ stdio_as_fds; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

__attribute__((used)) static const char *exec_context_tty_path(const ExecContext *context) {
        assert(context);

        if (context->stdio_as_fds)
                return NULL;

        if (context->tty_path)
                return context->tty_path;

        return "/dev/console";
}