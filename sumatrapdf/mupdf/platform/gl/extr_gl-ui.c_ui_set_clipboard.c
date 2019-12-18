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
 int /*<<< orphan*/  clipboard_buffer ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_strdup (int /*<<< orphan*/ ,char const*) ; 

void ui_set_clipboard(const char *buf)
{
	fz_free(ctx, clipboard_buffer);
	clipboard_buffer = fz_strdup(ctx, buf);
}