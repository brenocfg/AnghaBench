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
struct TYPE_3__ {char* psz_text; } ;
typedef  TYPE_1__ text_segment_t ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static bool AppendString( text_segment_t* p_segment, const char* psz_str )
{
    char* tmp;
    if ( asprintf( &tmp, "%s%s", p_segment->psz_text ? p_segment->psz_text : "", psz_str ) < 0 )
        return false;
    free( p_segment->psz_text );
    p_segment->psz_text = tmp;
    return true;
}