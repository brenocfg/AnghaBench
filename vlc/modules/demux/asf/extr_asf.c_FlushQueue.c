#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * p_first; int /*<<< orphan*/ ** pp_last; } ;
struct TYPE_5__ {int /*<<< orphan*/ * p_frame; } ;
struct TYPE_7__ {TYPE_2__ queue; TYPE_1__ info; } ;
typedef  TYPE_3__ asf_track_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FlushQueue( asf_track_t *tk )
{
    if( tk->info.p_frame )
    {
        block_ChainRelease( tk->info.p_frame );
        tk->info.p_frame = NULL;
    }
    if( tk->queue.p_first )
    {
        block_ChainRelease( tk->queue.p_first );
        tk->queue.p_first = NULL;
        tk->queue.pp_last = &tk->queue.p_first;
    }
}