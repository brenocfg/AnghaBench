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
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {float* table_blend; float* buf_overlap; unsigned int buf_queue; unsigned int samples_overlap; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */

__attribute__((used)) static void output_overlap_float( filter_t        *p_filter,
                                  void            *buf_out,
                                  unsigned         bytes_off )
{
    filter_sys_t *p = p_filter->p_sys;
    float *pout = buf_out;
    float *pb   = p->table_blend;
    float *po   = p->buf_overlap;
    float *pin  = (float *)( p->buf_queue + bytes_off );
    unsigned i;
    for( i = 0; i < p->samples_overlap; i++ ) {
        *pout++ = *po - *pb++ * ( *po - *pin++ ); po++;
    }
}