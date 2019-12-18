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
struct TYPE_3__ {struct TYPE_3__* p_next; scalar_t__* psz_text; } ;
typedef  TYPE_1__ text_segment_t ;

/* Variables and functions */
 scalar_t__ strlen (scalar_t__*) ; 
 size_t strspn (scalar_t__*,char*) ; 

__attribute__((used)) static bool SubsdelayIsTextEmpty( const text_segment_t *p_segment )
{
    while ( p_segment )
    {
        if ( strlen( p_segment->psz_text ) > 0 )
        {
            size_t offset = strspn( p_segment->psz_text, " " );
            if ( p_segment->psz_text[offset] )
                return false;
        }
        p_segment = p_segment->p_next;
    }

    return true;
}