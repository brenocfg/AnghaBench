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
struct TYPE_4__ {int /*<<< orphan*/  entry; scalar_t__ i_entry_max; scalar_t__ i_entry_count; } ;
struct TYPE_5__ {TYPE_1__ idx1; } ;
typedef  TYPE_2__ avi_chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AVI_ChunkFree_idx1( avi_chunk_t *p_chk )
{
    p_chk->idx1.i_entry_count = 0;
    p_chk->idx1.i_entry_max   = 0;
    FREENULL( p_chk->idx1.entry );
}