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
struct TYPE_2__ {size_t width; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (char const*,int,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__ opts ; 
 int /*<<< orphan*/  out_fd ; 

void print_line(const char *buf, size_t buf_pos, size_t prev_line_offset) {
    size_t write_chars = buf_pos - prev_line_offset + 1;
    if (opts.width > 0 && opts.width < write_chars) {
        write_chars = opts.width;
    }

    fwrite(buf + prev_line_offset, 1, write_chars, out_fd);
}