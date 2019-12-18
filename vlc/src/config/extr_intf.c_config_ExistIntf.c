#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 char* config_GetPsz (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,size_t) ; 

bool config_ExistIntf( const char *psz_intf )
{
    assert( psz_intf );

    char *psz_config, *psz_parser;
    size_t i_len = strlen( psz_intf );

    psz_config = psz_parser = config_GetPsz( "extraintf" );
    while( psz_parser )
    {
        if( !strncmp( psz_parser, psz_intf, i_len ) )
        {
            free( psz_config );
            return true;
        }
        psz_parser = strchr( psz_parser, ':' );
        if( psz_parser ) psz_parser++; /* skip the ':' */
    }
    free( psz_config );

    psz_config = psz_parser = config_GetPsz( "control" );
    while( psz_parser )
    {
        if( !strncmp( psz_parser, psz_intf, i_len ) )
        {
            free( psz_config );
            return true;
        }
        psz_parser = strchr( psz_parser, ':' );
        if( psz_parser ) psz_parser++; /* skip the ':' */
    }
    free( psz_config );

    return false;
}