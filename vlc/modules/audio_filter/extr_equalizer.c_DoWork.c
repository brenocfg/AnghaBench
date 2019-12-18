#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  audio; } ;
struct TYPE_9__ {TYPE_1__ fmt_in; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_nb_samples; scalar_t__ p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  EqzFilter (TYPE_2__*,float*,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_FormatNbChannels (int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t * DoWork( filter_t * p_filter, block_t * p_in_buf )
{
    EqzFilter( p_filter, (float*)p_in_buf->p_buffer,
               (float*)p_in_buf->p_buffer, p_in_buf->i_nb_samples,
               aout_FormatNbChannels( &p_filter->fmt_in.audio ) );
    return p_in_buf;
}