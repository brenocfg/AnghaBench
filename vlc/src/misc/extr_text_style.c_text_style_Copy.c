#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* psz_monofontname; void* psz_fontname; } ;
typedef  TYPE_1__ text_style_t ;

/* Variables and functions */
 void* strdup (void*) ; 

text_style_t *text_style_Copy( text_style_t *p_dst, const text_style_t *p_src )
{
    if( !p_src )
        return p_dst;

    /* */
    *p_dst = *p_src;

    if( p_src->psz_fontname )
        p_dst->psz_fontname = strdup( p_src->psz_fontname );

    if( p_src->psz_monofontname )
        p_dst->psz_monofontname = strdup( p_src->psz_monofontname );

    return p_dst;
}