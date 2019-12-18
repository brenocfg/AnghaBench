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
struct TYPE_3__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last_ptr; } ;
typedef  TYPE_1__ picture_fifo_t ;

/* Variables and functions */

__attribute__((used)) static void PictureFifoReset(picture_fifo_t *fifo)
{
    fifo->first    = NULL;
    fifo->last_ptr = &fifo->first;
}