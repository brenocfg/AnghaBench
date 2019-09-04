#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ print_break; } ;

/* Variables and functions */
 scalar_t__ first_file_match ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ opts ; 
 int /*<<< orphan*/  out_fd ; 

void print_file_separator(void) {
    if (first_file_match == 0 && opts.print_break) {
        fprintf(out_fd, "\n");
    }
    first_file_match = 0;
}