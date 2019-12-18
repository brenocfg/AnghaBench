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
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_4__ {int i_nb_samples; scalar_t__ p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DoWork_6_1_to_5_x( filter_t * p_filter,  block_t * p_in_buf, block_t * p_out_buf ) {
    VLC_UNUSED(p_filter);
    float *p_dest = (float *)p_out_buf->p_buffer;
    const float *p_src = (const float *)p_in_buf->p_buffer;
    for( int i = p_in_buf->i_nb_samples; i--; )
    {
        *p_dest++ = p_src[0];
        *p_dest++ = p_src[1];
        *p_dest++ = (p_src[2] + p_src[4]) * 0.5f;
        *p_dest++ = (p_src[3] + p_src[4]) * 0.5f;
        *p_dest++ = p_src[5];

        p_src += 6;

        /* We always have LFE here */
        *p_dest++ = *p_src++;
    }
}