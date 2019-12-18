#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_10__ {int i_size; TYPE_2__* s; struct TYPE_10__* p_next3g; } ;
typedef  TYPE_1__ tx3g_segment_t ;
typedef  int /*<<< orphan*/  text_style_t ;
struct TYPE_11__ {scalar_t__ style; } ;

/* Variables and functions */
 int /*<<< orphan*/  SegmentDoSplit (TYPE_1__*,int const,int const,TYPE_1__**,TYPE_1__**,TYPE_1__**) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  text_segment_Delete (TYPE_2__*) ; 
 scalar_t__ text_style_Duplicate (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  text_style_Merge (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool SegmentSplit( tx3g_segment_t *p_prev, tx3g_segment_t **pp_segment,
                          const uint16_t i_start, const uint16_t i_end,
                          const text_style_t *p_styles )
{
    tx3g_segment_t *p_segment_left = NULL, *p_segment_middle = NULL, *p_segment_right = NULL;

    if ( (*pp_segment)->i_size == 0 ) return false;
    if ( i_start > i_end ) return false;
    if ( (size_t)(i_end - i_start) > (*pp_segment)->i_size - 1 ) return false;
    if ( i_end > (*pp_segment)->i_size - 1 ) return false;

    SegmentDoSplit( *pp_segment, i_start, i_end, &p_segment_left, &p_segment_middle, &p_segment_right );
    if ( !p_segment_middle )
    {
        /* Failed */
        text_segment_Delete( p_segment_left->s );
        free( p_segment_left );
        text_segment_Delete( p_segment_right->s );
        free( p_segment_right );
        return false;
    }

    tx3g_segment_t *p_next3g = (*pp_segment)->p_next3g;
    text_segment_Delete( (*pp_segment)->s );
    free( *pp_segment );
    *pp_segment = ( p_segment_left ) ? p_segment_left : p_segment_middle ;
    if ( p_prev ) p_prev->p_next3g = *pp_segment;

    if ( p_segment_right )
        p_segment_right->p_next3g = p_next3g;
    else
        p_segment_middle->p_next3g = p_next3g;

    if( p_segment_middle->s->style )
        text_style_Merge( p_segment_middle->s->style, p_styles, true );
    else
        p_segment_middle->s->style = text_style_Duplicate( p_styles );

    return true;
}