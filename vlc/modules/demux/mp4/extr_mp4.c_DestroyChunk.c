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
struct TYPE_3__ {int /*<<< orphan*/  p_sample_size; int /*<<< orphan*/  p_sample_offset_pts; int /*<<< orphan*/  p_sample_count_pts; int /*<<< orphan*/  p_sample_delta_dts; int /*<<< orphan*/  p_sample_count_dts; } ;
typedef  TYPE_1__ mp4_chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DestroyChunk( mp4_chunk_t *ck )
{
    free( ck->p_sample_count_dts );
    free( ck->p_sample_delta_dts );
    free( ck->p_sample_count_pts );
    free( ck->p_sample_offset_pts );
    free( ck->p_sample_size );
}