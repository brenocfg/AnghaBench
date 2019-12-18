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
struct TYPE_3__ {size_t i_depth; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_fifo_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_assert (int /*<<< orphan*/ *) ; 

size_t vlc_fifo_GetCount(const vlc_fifo_t *fifo)
{
    vlc_mutex_assert(&fifo->lock);
    return fifo->i_depth;
}