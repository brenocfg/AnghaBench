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
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * aout_FiltersPipelinePlay (int /*<<< orphan*/ * const*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_ChainAppend (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * block_ChainGather (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filter_DrainAudio (int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t *aout_FiltersPipelineDrain(filter_t *const *filters,
                                          unsigned count)
{
    block_t *chain = NULL;

    for (unsigned i = 0; i < count; i++)
    {
        filter_t *filter = filters[i];

        block_t *block = filter_DrainAudio (filter);
        if (block)
        {
            /* If there is a drained block, filter it through the following
             * chain of filters  */
            if (i + 1 < count)
                block = aout_FiltersPipelinePlay (&filters[i + 1],
                                                  count - i - 1, block);
            if (block)
                block_ChainAppend (&chain, block);
        }
    }

    if (chain)
        return block_ChainGather(chain);
    else
        return NULL;
}