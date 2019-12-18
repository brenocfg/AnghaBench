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
struct TYPE_5__ {float* table_window; float* buf_overlap; unsigned int samples_per_frame; float* buf_pre_corr; unsigned int samples_overlap; unsigned int frames_search; unsigned int bytes_per_frame; scalar_t__ buf_queue; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 float INT_MIN ; 

__attribute__((used)) static unsigned best_overlap_offset_float( filter_t *p_filter )
{
    filter_sys_t *p = p_filter->p_sys;
    float *pw, *po, *ppc, *search_start;
    float best_corr = INT_MIN;
    unsigned best_off = 0;
    unsigned i, off;

    pw  = p->table_window;
    po  = p->buf_overlap;
    po += p->samples_per_frame;
    ppc = p->buf_pre_corr;
    for( i = p->samples_per_frame; i < p->samples_overlap; i++ ) {
      *ppc++ = *pw++ * *po++;
    }

    search_start = (float *)p->buf_queue + p->samples_per_frame;
    for( off = 0; off < p->frames_search; off++ ) {
      float corr = 0;
      float *ps = search_start;
      ppc = p->buf_pre_corr;
      for( i = p->samples_per_frame; i < p->samples_overlap; i++ ) {
        corr += *ppc++ * *ps++;
      }
      if( corr > best_corr ) {
        best_corr = corr;
        best_off  = off;
      }
      search_start += p->samples_per_frame;
    }

    return best_off * p->bytes_per_frame;
}