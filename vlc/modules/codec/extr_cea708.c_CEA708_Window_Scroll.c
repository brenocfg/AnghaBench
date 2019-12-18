#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int scroll_direction; } ;
struct TYPE_10__ {int i_firstrow; int i_lastrow; TYPE_3__** rows; TYPE_1__ style; } ;
typedef  TYPE_2__ cea708_window_t ;
struct TYPE_11__ {size_t lastcol; size_t firstcol; int /*<<< orphan*/ * styles; int /*<<< orphan*/ * characters; } ;
typedef  TYPE_3__ cea708_text_row_t ;
typedef  int /*<<< orphan*/  cea708_pen_style_t ;

/* Variables and functions */
#define  CEA708_WA_DIRECTION_BT 131 
#define  CEA708_WA_DIRECTION_LTR 130 
#define  CEA708_WA_DIRECTION_RTL 129 
#define  CEA708_WA_DIRECTION_TB 128 
 int /*<<< orphan*/  CEA708_WINDOW_MAX_ROWS ; 
 int /*<<< orphan*/  CEA708_Window_MaxCol (TYPE_2__*) ; 
 int /*<<< orphan*/  CEA708_Window_MinCol (TYPE_2__*) ; 
 scalar_t__ CEA708_Window_RowCount (TYPE_2__*) ; 
 int /*<<< orphan*/  CEA708_Window_Truncate (TYPE_2__*,int const) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void CEA708_Window_Scroll( cea708_window_t *p_w )
{
    if( CEA708_Window_RowCount( p_w ) == 0 )
        return;

    switch( p_w->style.scroll_direction )
    {
        case CEA708_WA_DIRECTION_LTR:
            /* Move RIGHT */
            if( CEA708_Window_MaxCol( p_w ) == CEA708_WINDOW_MAX_ROWS - 1 )
                CEA708_Window_Truncate( p_w, CEA708_WA_DIRECTION_LTR );
            for( int i=p_w->i_firstrow; i <= p_w->i_lastrow; i++ )
            {
                cea708_text_row_t *row = p_w->rows[i];
                if( row->lastcol < row->firstcol ) /* should not happen */
                    continue;
                memmove( &row->characters[row->firstcol + 1], &row->characters[row->firstcol],
                         (row->lastcol - row->firstcol + 1) * 4U );
                memmove( &row->styles[row->firstcol + 1], &row->styles[row->firstcol],
                         (row->lastcol - row->firstcol + 1) * sizeof(cea708_pen_style_t) );
                row->firstcol++;
                row->lastcol++;
            }
            break;
        case CEA708_WA_DIRECTION_RTL:
            /* Move LEFT */
            if( CEA708_Window_MinCol( p_w ) == 0 )
                CEA708_Window_Truncate( p_w, CEA708_WA_DIRECTION_RTL );
            for( int i=p_w->i_firstrow; i <= p_w->i_lastrow; i++ )
            {
                cea708_text_row_t *row = p_w->rows[i];
                if( row->lastcol < row->firstcol ) /* should not happen */
                    continue;
                memmove( &row->characters[row->firstcol - 1], &row->characters[row->firstcol],
                         (row->lastcol - row->firstcol + 1) * 4U );
                memmove( &row->styles[row->firstcol - 1], &row->styles[row->firstcol],
                         (row->lastcol - row->firstcol + 1) * sizeof(cea708_pen_style_t) );
                row->firstcol--;
                row->lastcol--;
            }
            break;
        case CEA708_WA_DIRECTION_TB:
            /* Move DOWN */
            if( p_w->i_lastrow == CEA708_WINDOW_MAX_ROWS - 1 )
                CEA708_Window_Truncate( p_w, CEA708_WA_DIRECTION_TB );
            for( int i=p_w->i_lastrow; i >= p_w->i_firstrow; i-- )
                p_w->rows[i+1] = p_w->rows[i];
            p_w->rows[p_w->i_firstrow] = NULL;
            p_w->i_firstrow++;
            p_w->i_lastrow++;
            break;
        case CEA708_WA_DIRECTION_BT:
            /* Move UP */
            if( p_w->i_firstrow == 0 )
                CEA708_Window_Truncate( p_w, CEA708_WA_DIRECTION_BT );
            for( int i=p_w->i_firstrow; i <= p_w->i_lastrow; i++ )
                p_w->rows[i-1] = p_w->rows[i];
            p_w->rows[p_w->i_lastrow] = NULL;
            p_w->i_firstrow--;
            p_w->i_lastrow--;
            break;
    }
}