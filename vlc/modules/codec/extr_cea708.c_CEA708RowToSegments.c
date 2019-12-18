#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_7__ {struct TYPE_7__* p_next; } ;
typedef  TYPE_1__ text_segment_t ;
struct TYPE_8__ {size_t firstcol; size_t lastcol; int /*<<< orphan*/ * styles; } ;
typedef  TYPE_2__ cea708_text_row_t ;
typedef  int /*<<< orphan*/  cea708_pen_style_t ;

/* Variables and functions */
 TYPE_1__* CEA708CharsToSegment (TYPE_2__ const*,size_t,size_t,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static text_segment_t * CEA708RowToSegments( const cea708_text_row_t *p_row,
                                             bool b_addnewline )
{
    text_segment_t *p_segments = NULL;
    text_segment_t **pp_last = &p_segments;

    uint8_t i_start = p_row->firstcol;
    for( uint8_t i=i_start; i<=p_row->lastcol; i++ )
    {
        if( i == p_row->lastcol ||
            memcmp( &p_row->styles[i], &p_row->styles[i+1], sizeof(cea708_pen_style_t) ) )
        {
            *pp_last = CEA708CharsToSegment( p_row, i_start, i,
                                             b_addnewline && (i == p_row->lastcol) );
            if( *pp_last )
                pp_last  = &((*pp_last)->p_next);
            i_start = i+1;
        }
    }

    return p_segments;
}