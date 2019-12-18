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
struct TYPE_3__ {size_t i_line_count; char** line; scalar_t__ i_line; } ;
typedef  TYPE_1__ text_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int INT_MAX ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 char** realloc (char**,size_t) ; 
 char* vlc_stream_ReadLine (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int TextLoad( text_t *txt, stream_t *s )
{
    char **lines = NULL;
    size_t n = 0;

    /* load the complete file */
    for( ;; )
    {
        char *psz = vlc_stream_ReadLine( s );
        char **ppsz_new;

        if( psz == NULL || (n >= INT_MAX/sizeof(char *)) )
        {
            free( psz );
            break;
        }

        ppsz_new = realloc( lines, (n + 1) * sizeof (char *) );
        if( ppsz_new == NULL )
        {
            free( psz );
            break;
        }
        lines = ppsz_new;
        lines[n++] = psz;
    }

    txt->i_line_count = n;
    txt->i_line       = 0;
    txt->line         = lines;

    return VLC_SUCCESS;
}