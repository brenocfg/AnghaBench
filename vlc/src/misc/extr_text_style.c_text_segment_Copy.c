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
struct TYPE_5__ {struct TYPE_5__* p_next; int /*<<< orphan*/  p_ruby; int /*<<< orphan*/  style; int /*<<< orphan*/  psz_text; } ;
typedef  TYPE_1__ text_segment_t ;

/* Variables and functions */
 TYPE_1__* text_segment_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_segment_ruby_Duplicate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_style_Duplicate (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

text_segment_t *text_segment_Copy( text_segment_t *p_src )
{
    text_segment_t *p_dst = NULL, *p_dst0 = NULL;

    while( p_src ) {
        text_segment_t *p_new = text_segment_New( p_src->psz_text );

        if( unlikely( !p_new ) )
            break;

        p_new->style = text_style_Duplicate( p_src->style );
        p_new->p_ruby = text_segment_ruby_Duplicate( p_src->p_ruby );

        if( p_dst == NULL )
        {
            p_dst = p_dst0 = p_new;
        }
        else
        {
            p_dst->p_next = p_new;
            p_dst = p_dst->p_next;
        }

        p_src = p_src->p_next;
    }

    return p_dst0;
}