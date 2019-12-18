#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ i_saved; int /*<<< orphan*/ * p_data; int /*<<< orphan*/ ** pp_last; scalar_t__ i_data_size; scalar_t__ i_gathered; } ;
struct TYPE_5__ {scalar_t__ p_proc; TYPE_1__ gather; } ;
typedef  TYPE_2__ ts_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_stream_processor_Reset (scalar_t__) ; 

__attribute__((used)) static inline void FlushESBuffer( ts_stream_t *p_pes )
{
    if( p_pes->gather.p_data )
    {
        p_pes->gather.i_gathered = p_pes->gather.i_data_size = 0;
        block_ChainRelease( p_pes->gather.p_data );
        p_pes->gather.p_data = NULL;
        p_pes->gather.pp_last = &p_pes->gather.p_data;
        p_pes->gather.i_saved = 0;
    }
    if( p_pes->p_proc )
        ts_stream_processor_Reset( p_pes->p_proc );
}