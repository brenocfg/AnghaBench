#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ i_firstrow; scalar_t__ i_lastrow; } ;
typedef  TYPE_1__ cea708_window_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t CEA708_Window_RowCount( const cea708_window_t *p_w )
{
    if( p_w->i_firstrow > p_w->i_lastrow )
        return 0;
    return 1 + p_w->i_lastrow - p_w->i_firstrow;
}