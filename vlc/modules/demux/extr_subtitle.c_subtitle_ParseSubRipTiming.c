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
struct TYPE_3__ {int /*<<< orphan*/  i_stop; int /*<<< orphan*/  i_start; } ;
typedef  TYPE_1__ subtitle_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int sscanf (char const*,char*,char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int subtitle_ParseSubRipTimingValue (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int subtitle_ParseSubRipTiming( subtitle_t *p_subtitle,
                                       const char *s )
{
    int i_result = VLC_EGENERIC;
    char *psz_start, *psz_stop;
    psz_start = malloc( strlen(s) + 1 );
    psz_stop = malloc( strlen(s) + 1 );

    if( sscanf( s, "%s --> %s", psz_start, psz_stop) == 2 &&
        subtitle_ParseSubRipTimingValue( &p_subtitle->i_start, psz_start ) == VLC_SUCCESS &&
        subtitle_ParseSubRipTimingValue( &p_subtitle->i_stop,  psz_stop ) == VLC_SUCCESS )
    {
        i_result = VLC_SUCCESS;
    }

    free(psz_start);
    free(psz_stop);

    return i_result;
}