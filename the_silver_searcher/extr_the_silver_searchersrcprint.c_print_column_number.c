#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t start; } ;
typedef  TYPE_1__ match_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long,char const) ; 
 int /*<<< orphan*/  out_fd ; 

void print_column_number(const match_t matches[], size_t last_printed_match,
                         size_t prev_line_offset, const char sep) {
    size_t column = 0;
    if (prev_line_offset <= matches[last_printed_match].start) {
        column = (matches[last_printed_match].start - prev_line_offset) + 1;
    }
    fprintf(out_fd, "%lu%c", (unsigned long)column, sep);
}