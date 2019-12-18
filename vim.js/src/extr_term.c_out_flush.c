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

/* Variables and functions */
 int /*<<< orphan*/  out_buf ; 
 int out_pos ; 
 int /*<<< orphan*/  ui_write (int /*<<< orphan*/ ,int) ; 

void
out_flush()
{
    int	    len;

    if (out_pos != 0)
    {
	/* set out_pos to 0 before ui_write, to avoid recursiveness */
	len = out_pos;
	out_pos = 0;
	ui_write(out_buf, len);
    }
}