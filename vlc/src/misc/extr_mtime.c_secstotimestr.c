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
typedef  int int32_t ;
struct TYPE_3__ {int rem; int quot; } ;
typedef  TYPE_1__ div_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSTRTIME_MAX_SIZE ; 
 TYPE_1__ div (int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 scalar_t__ unlikely (int) ; 

char *secstotimestr( char *psz_buffer, int32_t i_seconds )
{
    if( unlikely(i_seconds < 0) )
    {
        secstotimestr( psz_buffer + 1, -i_seconds );
        *psz_buffer = '-';
        return psz_buffer;
    }

    div_t d;

    d = div( i_seconds, 60 );
    i_seconds = d.rem;
    d = div( d.quot, 60 );

    if( d.quot )
        snprintf( psz_buffer, MSTRTIME_MAX_SIZE, "%u:%02u:%02u",
                 d.quot, d.rem, i_seconds );
    else
        snprintf( psz_buffer, MSTRTIME_MAX_SIZE, "%02u:%02u",
                  d.rem, i_seconds );
    return psz_buffer;
}