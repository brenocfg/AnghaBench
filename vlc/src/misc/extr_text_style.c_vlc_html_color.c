#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int i_value; int /*<<< orphan*/ * psz_name; } ;

/* Variables and functions */
 scalar_t__ isspace (char) ; 
 TYPE_1__* p_html_colors ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,...) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  strtoul (char const*,char**,int) ; 

unsigned int vlc_html_color( const char *psz_value, bool* ok )
{
    unsigned int color = 0;
    char* psz_end;
    bool b_ret = false;

    const char *psz_hex = (*psz_value == '#') ? psz_value + 1 : psz_value;

    if( psz_hex != psz_value ||
        (*psz_hex >= '0' && *psz_hex <= '9') ||
        (*psz_hex >= 'A' && *psz_hex <= 'F') )
    {
        uint32_t i_value = (uint32_t)strtoul( psz_hex, &psz_end, 16 );
        if( *psz_end == 0 || isspace( *psz_end ) )
        {
            switch( psz_end - psz_hex )
            {
                case 8:
                    color = (i_value << 24) | (i_value >> 8);
                    b_ret = true;
                    break;
                case 6:
                    color = i_value | 0xFF000000;
                    b_ret = true;
                    break;
                default:
                    break;
            }
        }
    }

    if( !b_ret && psz_hex == psz_value &&
        !strncmp( "rgb", psz_value, 3 ) )
    {
        unsigned r,g,b,a = 0xFF;
        if( psz_value[3] == 'a' )
            b_ret = (sscanf( psz_value, "rgba(%3u,%3u,%3u,%3u)", &r, &g, &b, &a ) == 4);
        else
            b_ret = (sscanf( psz_value, "rgb(%3u,%3u,%3u)", &r, &g, &b ) == 3);
        color = (a << 24) | (r << 16) | (g << 8) | b;
    }

    if( !b_ret && psz_hex == psz_value )
    {
        for( int i = 0; p_html_colors[i].psz_name != NULL; i++ )
        {
            if( !strcasecmp( psz_value, p_html_colors[i].psz_name ) )
            {
                // Assume opaque color since the table doesn't specify an alpha
                color = p_html_colors[i].i_value | 0xFF000000;
                b_ret = true;
                break;
            }
        }
    }

    if ( ok != NULL )
        *ok = b_ret;

    return color;
}