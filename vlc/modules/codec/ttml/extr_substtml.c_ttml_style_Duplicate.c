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
struct TYPE_5__ {int /*<<< orphan*/  font_style; } ;
typedef  TYPE_1__ ttml_style_t ;

/* Variables and functions */
 int /*<<< orphan*/  text_style_Duplicate (int /*<<< orphan*/ ) ; 
 TYPE_1__* ttml_style_New () ; 

__attribute__((used)) static ttml_style_t * ttml_style_Duplicate( const ttml_style_t *p_src )
{
    ttml_style_t *p_dup = ttml_style_New( );
    if( p_dup )
    {
        *p_dup = *p_src;
        p_dup->font_style = text_style_Duplicate( p_src->font_style );
    }
    return p_dup;
}