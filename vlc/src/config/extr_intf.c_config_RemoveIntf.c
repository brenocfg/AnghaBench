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
 int asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 char* config_GetPsz (char*) ; 
 int /*<<< orphan*/  config_PutPsz (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 

void config_RemoveIntf( const char *psz_intf )
{
    assert( psz_intf );

    char *psz_config, *psz_parser;
    size_t i_len = strlen( psz_intf );

    psz_config = psz_parser = config_GetPsz( "extraintf" );
    while( psz_parser )
    {
        if( !strncmp( psz_intf, psz_parser, i_len ) )
        {
            char *psz_newconfig;
            char *psz_end = psz_parser + i_len;
            if( *psz_end == ':' ) psz_end++;
            *psz_parser = '\0';
            if( asprintf( &psz_newconfig, "%s%s", psz_config, psz_end ) != -1 )
            {
                config_PutPsz( "extraintf", psz_newconfig );
                free( psz_newconfig );
            }
            break;
        }
        psz_parser = strchr( psz_parser, ':' );
        if( psz_parser ) psz_parser++; /* skip the ':' */
    }
    free( psz_config );

    psz_config = psz_parser = config_GetPsz( "control" );
    while( psz_parser )
    {
        if( !strncmp( psz_intf, psz_parser, i_len ) )
        {
            char *psz_newconfig;
            char *psz_end = psz_parser + i_len;
            if( *psz_end == ':' ) psz_end++;
            *psz_parser = '\0';
            if( asprintf( &psz_newconfig, "%s%s", psz_config, psz_end ) != -1 )
            {
                config_PutPsz( "control", psz_newconfig );
                free( psz_newconfig );
            }
            break;
        }
        psz_parser = strchr( psz_parser, ':' );
        if( psz_parser ) psz_parser++; /* skip the ':' */
    }
    free( psz_config );
}