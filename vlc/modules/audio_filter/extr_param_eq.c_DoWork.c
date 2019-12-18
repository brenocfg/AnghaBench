#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  i_channels; } ;
struct TYPE_10__ {TYPE_1__ audio; } ;
struct TYPE_11__ {TYPE_2__ fmt_in; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_12__ {int /*<<< orphan*/  coeffs; int /*<<< orphan*/  p_state; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_nb_samples; scalar_t__ p_buffer; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  ProcessEQ (float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static block_t *DoWork( filter_t * p_filter, block_t * p_in_buf )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    ProcessEQ( (float*)p_in_buf->p_buffer, (float*)p_in_buf->p_buffer,
               p_sys->p_state,
               p_filter->fmt_in.audio.i_channels, p_in_buf->i_nb_samples,
               p_sys->coeffs, 5 );
    return p_in_buf;
}