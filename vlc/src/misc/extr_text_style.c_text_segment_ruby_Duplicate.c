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
struct TYPE_5__ {struct TYPE_5__* p_next; int /*<<< orphan*/  psz_rt; int /*<<< orphan*/  psz_base; } ;
typedef  TYPE_1__ text_segment_ruby_t ;

/* Variables and functions */
 TYPE_1__* text_segment_ruby_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static text_segment_ruby_t *text_segment_ruby_Duplicate( const text_segment_ruby_t *p_src )
{
    text_segment_ruby_t *p_dup = NULL;
    text_segment_ruby_t **pp_append = &p_dup;
    for ( ; p_src ; p_src = p_src->p_next )
    {
        *pp_append = text_segment_ruby_New( p_src->psz_base, p_src->psz_rt );
        if( *pp_append )
            pp_append = &((*pp_append)->p_next);
    }
    return p_dup;
}