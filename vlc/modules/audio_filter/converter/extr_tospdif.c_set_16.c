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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {scalar_t__ i_format; } ;
struct TYPE_6__ {TYPE_1__ audio; } ;
struct TYPE_7__ {TYPE_2__ fmt_out; } ;
typedef  TYPE_3__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetWBE (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWLE (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_CODEC_SPDIFB ; 

__attribute__((used)) static void set_16( filter_t *p_filter, void *p_buf, uint16_t i_val )
{
    if( p_filter->fmt_out.audio.i_format == VLC_CODEC_SPDIFB )
        SetWBE( p_buf, i_val );
    else
        SetWLE( p_buf, i_val );
}