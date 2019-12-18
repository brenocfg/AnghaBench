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
struct TYPE_4__ {int b_row_lock; int b_column_lock; int /*<<< orphan*/  i_firstrow; int /*<<< orphan*/  pen; int /*<<< orphan*/  style; } ;
typedef  TYPE_1__ cea708_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  CEA708_WINDOW_MAX_ROWS ; 
 int /*<<< orphan*/ * cea708_default_pen_styles ; 
 int /*<<< orphan*/ * cea708_default_window_styles ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void CEA708_Window_Init( cea708_window_t *p_w )
{
    memset( p_w, 0, sizeof(*p_w) );
    p_w->style = cea708_default_window_styles[0];
    p_w->pen = cea708_default_pen_styles[0];
    p_w->i_firstrow = CEA708_WINDOW_MAX_ROWS;
    p_w->b_row_lock = true;
    p_w->b_column_lock = true;
}