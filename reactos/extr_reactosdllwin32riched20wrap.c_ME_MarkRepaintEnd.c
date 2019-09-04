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
typedef  int /*<<< orphan*/  ME_DisplayItem ;

/* Variables and functions */

__attribute__((used)) static void ME_MarkRepaintEnd(ME_DisplayItem *para,
                              ME_DisplayItem **repaint_start,
                              ME_DisplayItem **repaint_end)
{
    if (!*repaint_start)
      *repaint_start = para;
    *repaint_end = para;
}