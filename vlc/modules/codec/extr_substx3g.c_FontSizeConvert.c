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
struct TYPE_4__ {double i_font_size; double f_font_relsize; } ;
typedef  TYPE_1__ text_style_t ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void FontSizeConvert( const text_style_t *p_reference, text_style_t *p_style )
{
    if( unlikely(!p_style) )
    {
        return;
    }
    else if( unlikely(!p_reference) || p_reference->i_font_size == 0 )
    {
        p_style->i_font_size = 0;
        p_style->f_font_relsize = 5.0;
    }
    else
    {
        p_style->f_font_relsize = 5.0 * (float) p_style->i_font_size / p_reference->i_font_size;
        p_style->i_font_size = 0;
    }
}