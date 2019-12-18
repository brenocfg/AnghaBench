#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_font_color; } ;
struct TYPE_5__ {int i_id; TYPE_1__ fontstyle; } ;
typedef  TYPE_2__ commandparams_t ;

/* Variables and functions */
 scalar_t__ VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ parse_digit (char**,int*) ; 
 int /*<<< orphan*/  skip_space (char**) ; 

__attribute__((used)) static int parser_SetTextColor( char *psz_command, char *psz_end,
                                commandparams_t *p_params )
{
    int r = 0, g = 0, b = 0;
    VLC_UNUSED(psz_end);

    skip_space( &psz_command );
    if( isdigit( (unsigned char)*psz_command ) )
    {
        if( parse_digit( &psz_command, &p_params->i_id ) == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    skip_space( &psz_command );
    if( isdigit( (unsigned char)*psz_command ) )
    {
        if( parse_digit( &psz_command, &r ) == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    skip_space( &psz_command );
    if( isdigit( (unsigned char)*psz_command ) )
    {
        if( parse_digit( &psz_command, &g ) == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    skip_space( &psz_command );
    if( isdigit( (unsigned char)*psz_command ) )
    {
        if( parse_digit( &psz_command, &b ) == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    p_params->fontstyle.i_font_color = (r<<16) | (g<<8) | (b<<0);
    return VLC_SUCCESS;
}