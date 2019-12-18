#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  psz_location; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {void* psz_ports; void* i_channels; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 void* abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 void* strndup (char*,int) ; 
 int /*<<< orphan*/  strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Parse( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    char *psz_dup = strdup( p_demux->psz_location );
    char *psz_parser = psz_dup;

    if( !strncmp( psz_parser, "channels=", strlen( "channels=" ) ) )
    {
        p_sys->i_channels = abs( strtol( psz_parser + strlen( "channels=" ),
            &psz_parser, 0 ) );
    }
    else if( !strncmp( psz_parser, "ports=", strlen( "ports=" ) ) )
    {
        int i_len;
        psz_parser += strlen( "ports=" );
        if( strchr( psz_parser, ':' ) )
        {
            i_len = strchr( psz_parser, ':' ) - psz_parser;
        }
        else
        {
            i_len = strlen( psz_parser );
        }
        p_sys->psz_ports = strndup( psz_parser, i_len );
        psz_parser += i_len;
    }
    else
    {
        msg_Warn( p_demux, "unknown option" );
    }

    while( *psz_parser && *psz_parser != ':' )
    {
        psz_parser++;
    }

    if( *psz_parser == ':' )
    {
        for( ;; )
        {
            *psz_parser++ = '\0';
            if( !strncmp( psz_parser, "channels=", strlen( "channels=" ) ) )
            {
                p_sys->i_channels = abs( strtol(
                    psz_parser + strlen( "channels=" ), &psz_parser, 0 ) );
            }
            else if( !strncmp( psz_parser, "ports=", strlen( "ports=" ) ) )
            {
                int i_len;
                psz_parser += strlen( "ports=" );
                if( strchr( psz_parser, ':' ) )
                {
                    i_len = strchr( psz_parser, ':' ) - psz_parser;
                }
                else
                {
                    i_len = strlen( psz_parser );
                }
                p_sys->psz_ports = strndup( psz_parser, i_len );
                psz_parser += i_len;
            }
            else
            {
                msg_Warn( p_demux, "unknown option" );
            }
            while( *psz_parser && *psz_parser != ':' )
            {
                psz_parser++;
            }

            if( *psz_parser == '\0' )
            {
                break;
            }
        }
    }

    free( psz_dup );
}