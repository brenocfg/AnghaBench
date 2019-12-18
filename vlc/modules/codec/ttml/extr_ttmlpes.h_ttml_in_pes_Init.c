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
struct ttml_in_pes_ctx {int i_prev_block_time; int i_prev_segment_start_time; scalar_t__ i_offset; } ;

/* Variables and functions */

__attribute__((used)) static void ttml_in_pes_Init(struct ttml_in_pes_ctx *p)
{
    p->i_offset = 0;
    p->i_prev_block_time = -1;
    p->i_prev_segment_start_time = -1;
}