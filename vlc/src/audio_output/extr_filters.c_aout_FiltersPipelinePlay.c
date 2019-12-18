#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * (* pf_audio_filter ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ filter_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t *aout_FiltersPipelinePlay(filter_t *const *filters,
                                         unsigned count, block_t *block)
{
    /* TODO: use filter chain */
    for (unsigned i = 0; (i < count) && (block != NULL); i++)
    {
        filter_t *filter = filters[i];

        /* Please note that p_block->i_nb_samples & i_buffer
         * shall be set by the filter plug-in. */
        block = filter->pf_audio_filter (filter, block);
    }
    return block;
}