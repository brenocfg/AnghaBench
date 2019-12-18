#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int i_font_size; int f_font_relsize; } ;
typedef  TYPE_3__ text_style_t ;
struct TYPE_9__ {scalar_t__ i_height; } ;
struct TYPE_8__ {TYPE_2__ video; } ;
struct TYPE_11__ {TYPE_1__ fmt_out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_12__ {int i_scale; } ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 int STYLE_DEFAULT_FONT_SIZE ; 

int ConvertToLiveSize( filter_t *p_filter, const text_style_t *p_style )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    int i_font_size = STYLE_DEFAULT_FONT_SIZE;
    if( p_style->i_font_size )
    {
        i_font_size = p_style->i_font_size;
    }
    else if ( p_style->f_font_relsize )
    {
        i_font_size = (int) p_filter->fmt_out.video.i_height * p_style->f_font_relsize / 100;
    }

    if( p_sys->i_scale != 100 )
        i_font_size = i_font_size * p_sys->i_scale / 100;

    return i_font_size;
}