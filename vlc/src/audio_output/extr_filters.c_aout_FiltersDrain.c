#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_9__ {int count; scalar_t__ resampling; TYPE_4__* resampler; TYPE_4__** tab; } ;
typedef  TYPE_3__ aout_filters_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_rate; } ;
struct TYPE_8__ {TYPE_1__ audio; } ;
struct TYPE_10__ {TYPE_2__ fmt_in; } ;

/* Variables and functions */
 int /*<<< orphan*/ * aout_FiltersPipelineDrain (TYPE_4__**,int) ; 
 int /*<<< orphan*/ * aout_FiltersPipelinePlay (TYPE_4__**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_ChainAppend (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * block_ChainGather (int /*<<< orphan*/ *) ; 

block_t *aout_FiltersDrain (aout_filters_t *filters)
{
    /* Drain the filters pipeline */
    block_t *block = aout_FiltersPipelineDrain (filters->tab, filters->count);

    if (filters->resampler != NULL)
    {
        block_t *chain = NULL;

        filters->resampler->fmt_in.audio.i_rate += filters->resampling;

        if (block)
        {
            /* Resample the drained block from the filters pipeline */
            block = aout_FiltersPipelinePlay (&filters->resampler, 1, block);
            if (block)
                block_ChainAppend (&chain, block);
        }

        /* Drain the resampler filter */
        block = aout_FiltersPipelineDrain (&filters->resampler, 1);
        if (block)
            block_ChainAppend (&chain, block);

        filters->resampler->fmt_in.audio.i_rate -= filters->resampling;

        return chain ? block_ChainGather (chain) : NULL;
    }
    else
        return block;
}