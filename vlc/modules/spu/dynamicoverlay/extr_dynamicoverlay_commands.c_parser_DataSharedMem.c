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
struct TYPE_3__ {int /*<<< orphan*/  i_shmid; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_1__ commandparams_t ;

/* Variables and functions */
 scalar_t__ VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ parse_char (char**,char**,int,char*) ; 
 scalar_t__ parse_digit (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_space (char**) ; 

__attribute__((used)) static int parser_DataSharedMem( char *psz_command,
                                 char *psz_end,
                                 commandparams_t *p_params )
{
    /* Parse: 0 128 128 RGBA 9404459 */
    skip_space( &psz_command );
    if( isdigit( (unsigned char)*psz_command ) )
    {
        if( parse_digit( &psz_command, &p_params->i_id ) == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    skip_space( &psz_command );
    if( isdigit( (unsigned char)*psz_command ) )
    {
        if( parse_digit( &psz_command, &p_params->i_width ) == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    skip_space( &psz_command );
    if( isdigit( (unsigned char)*psz_command ) )
    {
        if( parse_digit( &psz_command, &p_params->i_height ) == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    skip_space( &psz_command );
    if( isascii( (unsigned char)*psz_command ) )
    {
        if( parse_char( &psz_command, &psz_end, 4, (char*)&p_params->fourcc )
            == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    skip_space( &psz_command );
    if( isdigit( (unsigned char)*psz_command ) )
    {
        if( parse_digit( &psz_command, &p_params->i_shmid ) == VLC_EGENERIC )
            return VLC_EGENERIC;
    }
    return VLC_SUCCESS;
}