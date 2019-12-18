#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int print_direction; } ;
struct TYPE_6__ {int /*<<< orphan*/  row; int /*<<< orphan*/  col; TYPE_1__ style; } ;
typedef  TYPE_2__ cea708_window_t ;

/* Variables and functions */
#define  CEA708_WA_DIRECTION_BT 131 
#define  CEA708_WA_DIRECTION_LTR 130 
#define  CEA708_WA_DIRECTION_RTL 129 
#define  CEA708_WA_DIRECTION_TB 128 
 int /*<<< orphan*/  CEA708_WINDOW_MAX_COLS ; 
 int /*<<< orphan*/  CEA708_WINDOW_MAX_ROWS ; 
 int /*<<< orphan*/  CEA708_Window_CarriageReturn (TYPE_2__*) ; 

__attribute__((used)) static void CEA708_Window_Forward( cea708_window_t *p_w )
{
    switch( p_w->style.print_direction )
    {
        case CEA708_WA_DIRECTION_LTR:
            if( p_w->col + 1 < CEA708_WINDOW_MAX_COLS )
                p_w->col++;
            else
                CEA708_Window_CarriageReturn( p_w );
            break;
        case CEA708_WA_DIRECTION_RTL:
            if( p_w->col > 0 )
                p_w->col--;
            else
                CEA708_Window_CarriageReturn( p_w );
            break;
        case CEA708_WA_DIRECTION_TB:
            if( p_w->row + 1 < CEA708_WINDOW_MAX_ROWS )
                p_w->row++;
            else
                CEA708_Window_CarriageReturn( p_w );
            break;
        case CEA708_WA_DIRECTION_BT:
            if( p_w->row > 0 )
                p_w->row--;
            else
                CEA708_Window_CarriageReturn( p_w );
            break;
    }
}