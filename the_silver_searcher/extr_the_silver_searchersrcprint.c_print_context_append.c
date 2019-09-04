#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int before; } ;
struct TYPE_3__ {size_t last_prev_line; int /*<<< orphan*/ ** context_prev_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ag_strndup (char const*,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_2__ opts ; 
 TYPE_1__ print_context ; 

void print_context_append(const char *line, size_t len) {
    if (opts.before == 0) {
        return;
    }
    if (print_context.context_prev_lines[print_context.last_prev_line] != NULL) {
        free(print_context.context_prev_lines[print_context.last_prev_line]);
    }
    print_context.context_prev_lines[print_context.last_prev_line] = ag_strndup(line, len);
    print_context.last_prev_line = (print_context.last_prev_line + 1) % opts.before;
}