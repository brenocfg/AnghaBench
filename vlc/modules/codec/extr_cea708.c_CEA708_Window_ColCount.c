#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {size_t row; TYPE_2__** rows; } ;
typedef  TYPE_1__ cea708_window_t ;
struct TYPE_5__ {scalar_t__ firstcol; scalar_t__ lastcol; } ;
typedef  TYPE_2__ cea708_text_row_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t CEA708_Window_ColCount( const cea708_window_t *p_w )
{
    const cea708_text_row_t *p_row = p_w->rows[p_w->row];
    if( !p_row || p_row->firstcol > p_row->lastcol )
        return 0;
    return 1 + p_row->lastcol - p_row->firstcol;
}