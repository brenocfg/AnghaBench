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
struct TYPE_5__ {scalar_t__ unit; double i_value; } ;
typedef  TYPE_1__ ttml_length_t ;

/* Variables and functions */
 scalar_t__ TTML_UNIT_CELL ; 
 scalar_t__ TTML_UNIT_PERCENT ; 

__attribute__((used)) static ttml_length_t ttml_rebase_length( unsigned i_cell_resolution,
                                         ttml_length_t value,
                                         ttml_length_t reference )
{
    if( value.unit == TTML_UNIT_PERCENT )
    {
        value.i_value *= reference.i_value / 100.0;
        value.unit = reference.unit;
    }
    else if( value.unit == TTML_UNIT_CELL )
    {
        value.i_value *= reference.i_value / i_cell_resolution;
        value.unit = reference.unit;
    }
    // pixels as-is
    return value;
}