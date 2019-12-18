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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {char* psz_ports; char** pp_jack_port_table; int i_match_ports; int /*<<< orphan*/  p_jack_client; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  JackPortIsOutput ; 
 int /*<<< orphan*/  free (char const**) ; 
 char** jack_get_ports (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 char* vlc_uri_decode_duplicate (char*) ; 
 char** xrealloc (char**,int) ; 

__attribute__((used)) static void Port_finder( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    char *psz_expr = p_sys->psz_ports;
    char *token = NULL;
    char *state = NULL;
    char *psz_uri = NULL;
    const char **pp_jack_port_output = NULL;
    int i_out_ports = 0;
    int i_total_out_ports =0;
    p_sys->pp_jack_port_table = NULL;

    /* parse the ports part of the MRL */
    for( token = strtok_r( psz_expr, ",", &state ); token;
            token = strtok_r( NULL, ",", &state ) )
    {
        psz_uri = vlc_uri_decode_duplicate( token );
        /* get the ports which match the regexp */
        pp_jack_port_output = jack_get_ports( p_sys->p_jack_client,
           psz_uri, NULL, JackPortIsOutput );
        if( pp_jack_port_output == NULL )
            msg_Err( p_demux, "port(s) asked not found:%s", psz_uri );
        else
        {
            while( pp_jack_port_output[i_out_ports] )
                i_out_ports++;
            /* alloc an array to store all the matched ports */
            p_sys->pp_jack_port_table = xrealloc( p_sys->pp_jack_port_table,
                (i_out_ports * sizeof( char * ) + i_total_out_ports * sizeof( char * ) ) );

            for(int i=0; i<i_out_ports;i++)
                p_sys->pp_jack_port_table[i_total_out_ports+i] = ( char * ) pp_jack_port_output[i];

            i_total_out_ports += i_out_ports;

            free( pp_jack_port_output );
        }
    }

    p_sys->i_match_ports = i_total_out_ports;
}