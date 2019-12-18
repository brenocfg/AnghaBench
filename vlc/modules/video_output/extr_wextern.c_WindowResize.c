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
typedef  int /*<<< orphan*/  vout_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  vout_window_ReportSize (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static void WindowResize(void *opaque, unsigned width, unsigned height)
{
    vout_window_t *window = opaque;
    vout_window_ReportSize(window, width, height);
}