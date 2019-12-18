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
struct TYPE_3__ {int i_id; int b_visible; } ;
typedef  TYPE_1__ commandparams_t ;

/* Variables and functions */
 scalar_t__ VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ parse_digit (char**,int*) ; 
 int /*<<< orphan*/  skip_space (char**) ; 

__attribute__((used)) static int parser_SetVisibility( char *psz_command, char *psz_end,
                                 commandparams_t *p_params )
{
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
        int32_t i_vis = 0;
        if( parse_digit( &psz_command, &i_vis ) == VLC_EGENERIC )
            return VLC_EGENERIC;
        p_params->b_visible = (i_vis == 1) ? true : false;
    }
    return VLC_SUCCESS;
}