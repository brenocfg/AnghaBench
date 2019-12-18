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
struct TYPE_3__ {scalar_t__ i_depth; int /*<<< orphan*/ * p_first; int /*<<< orphan*/ ** pp_last; } ;
typedef  TYPE_1__ fifo_t ;

/* Variables and functions */

__attribute__((used)) static inline void fifo_Init(fifo_t *p_fifo)
{
    p_fifo->p_first = NULL;
    p_fifo->pp_last = &p_fifo->p_first;
    p_fifo->i_depth = 0;
}