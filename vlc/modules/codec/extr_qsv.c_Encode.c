#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_13__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ encoder_t ;
struct TYPE_14__ {scalar_t__ async_depth; int /*<<< orphan*/  packets; } ;
typedef  TYPE_2__ encoder_sys_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_15__ {struct TYPE_15__* syncp; } ;
typedef  TYPE_3__ async_task_t ;
struct TYPE_16__ {scalar_t__ syncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* async_task_t_fifo_Get (int /*<<< orphan*/ *) ; 
 scalar_t__ async_task_t_fifo_GetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  async_task_t_fifo_Put (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_9__* async_task_t_fifo_Show (int /*<<< orphan*/ *) ; 
 TYPE_3__* encode_frame (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qsv_synchronize_block (TYPE_1__*,TYPE_3__*) ; 

__attribute__((used)) static block_t *Encode(encoder_t *this, picture_t *pic)
{
    encoder_t     *enc = (encoder_t *)this;
    encoder_sys_t *sys = enc->p_sys;
    async_task_t     *task;
    block_t       *block = NULL;

    if (likely(pic != NULL))
    {
        task = encode_frame( enc, pic );
        if (likely(task != NULL))
            async_task_t_fifo_Put(&sys->packets, task);
    }

    if ( async_task_t_fifo_GetCount(&sys->packets) == (sys->async_depth + 1) ||
         (!pic && async_task_t_fifo_GetCount(&sys->packets)))
    {
        assert(async_task_t_fifo_Show(&sys->packets)->syncp != 0);
        task = async_task_t_fifo_Get(&sys->packets);
        block = qsv_synchronize_block( enc, task );
        free(task->syncp);
        free(task);
    }

    return block;
}