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
struct TYPE_3__ {double member_0; float i_value; int /*<<< orphan*/  unit; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ ttml_length_t ;

/* Variables and functions */
 int /*<<< orphan*/  TTML_UNIT_CELL ; 
 int /*<<< orphan*/  TTML_UNIT_PERCENT ; 
 int /*<<< orphan*/  TTML_UNIT_PIXELS ; 
 int /*<<< orphan*/  TTML_UNIT_UNKNOWN ; 
 float us_strtof (char const*,char**) ; 

__attribute__((used)) static ttml_length_t ttml_read_length( const char *psz )
{
    ttml_length_t len = { 0.0, TTML_UNIT_UNKNOWN };

    char* psz_end = NULL;
    float size = us_strtof( psz, &psz_end );
    len.i_value = size;
    if( psz_end )
    {
        if( *psz_end == 'c' || *psz_end == 'r' )
            len.unit = TTML_UNIT_CELL;
        else if( *psz_end == '%' )
            len.unit = TTML_UNIT_PERCENT;
        else if( *psz_end == 'p' && *(psz_end + 1) == 'x' )
            len.unit = TTML_UNIT_PIXELS;
    }
    return len;
}