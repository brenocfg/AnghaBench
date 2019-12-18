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
struct TYPE_6__ {TYPE_1__ style; } ;
typedef  TYPE_2__ cea708_window_t ;

/* Variables and functions */
#define  CEA708_WA_DIRECTION_BT 131 
#define  CEA708_WA_DIRECTION_LTR 130 
#define  CEA708_WA_DIRECTION_RTL 129 
#define  CEA708_WA_DIRECTION_TB 128 
 int /*<<< orphan*/  CEA708_Window_Forward (TYPE_2__*) ; 

__attribute__((used)) static void CEA708_Window_Backward( cea708_window_t *p_w )
{
    static const int reverse[] =
    {
        [CEA708_WA_DIRECTION_LTR] = CEA708_WA_DIRECTION_RTL,
        [CEA708_WA_DIRECTION_RTL] = CEA708_WA_DIRECTION_LTR,
        [CEA708_WA_DIRECTION_TB]  = CEA708_WA_DIRECTION_BT,
        [CEA708_WA_DIRECTION_BT]  = CEA708_WA_DIRECTION_TB,
    };
    int save = p_w->style.print_direction;
    p_w->style.print_direction = reverse[p_w->style.print_direction];
    CEA708_Window_Forward( p_w );
    p_w->style.print_direction = save;
}