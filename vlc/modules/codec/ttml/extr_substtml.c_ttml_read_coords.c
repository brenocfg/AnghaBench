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
struct TYPE_5__ {double member_0; scalar_t__ member_1; scalar_t__ unit; } ;
typedef  TYPE_1__ ttml_length_t ;

/* Variables and functions */
 scalar_t__ TTML_UNIT_UNKNOWN ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 
 TYPE_1__ ttml_read_length (char*) ; 

__attribute__((used)) static bool ttml_read_coords( const char *value, ttml_length_t *h, ttml_length_t *v )
{
    ttml_length_t vals[2] = { { 0.0, TTML_UNIT_UNKNOWN },
                              { 0.0, TTML_UNIT_UNKNOWN } };
    char *dup = strdup( value );
    char* psz_saveptr = NULL;
    char* token = (dup) ? strtok_r( dup, " ", &psz_saveptr ) : NULL;
    for(int i=0; i<2 && token != NULL; i++)
    {
        vals[i] = ttml_read_length( token );
        token = strtok_r( NULL, " ", &psz_saveptr );
    }
    free( dup );

    if( vals[0].unit != TTML_UNIT_UNKNOWN &&
        vals[1].unit != TTML_UNIT_UNKNOWN )
    {
        *h = vals[0];
        *v = vals[1];
        return true;
    }
    return false;
}