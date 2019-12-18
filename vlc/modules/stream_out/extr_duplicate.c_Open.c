#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_11__ {TYPE_2__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_send; int /*<<< orphan*/  pf_del; int /*<<< orphan*/  pf_add; int /*<<< orphan*/  p_next; int /*<<< orphan*/  p_sout; TYPE_3__* p_cfg; } ;
typedef  TYPE_1__ sout_stream_t ;
struct TYPE_12__ {int i_nb_streams; char** pp_streams; int i_nb_last_streams; char** pp_last_streams; int i_nb_select; char** ppsz_select; } ;
typedef  TYPE_2__ sout_stream_sys_t ;
struct TYPE_13__ {char* psz_value; int /*<<< orphan*/  psz_name; struct TYPE_13__* p_next; } ;
typedef  TYPE_3__ config_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  Add ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Del ; 
 int /*<<< orphan*/  Send ; 
 int /*<<< orphan*/  TAB_APPEND (int,char**,TYPE_1__*) ; 
 int /*<<< orphan*/  TAB_INIT (int,char**) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 TYPE_1__* sout_StreamChainNew (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    sout_stream_t     *p_stream = (sout_stream_t*)p_this;
    sout_stream_sys_t *p_sys;
    config_chain_t        *p_cfg;

    msg_Dbg( p_stream, "creating 'duplicate'" );

    p_sys = malloc( sizeof( sout_stream_sys_t ) );
    if( !p_sys )
        return VLC_ENOMEM;

    TAB_INIT( p_sys->i_nb_streams, p_sys->pp_streams );
    TAB_INIT( p_sys->i_nb_last_streams, p_sys->pp_last_streams );
    TAB_INIT( p_sys->i_nb_select, p_sys->ppsz_select );

    for( p_cfg = p_stream->p_cfg; p_cfg != NULL; p_cfg = p_cfg->p_next )
    {
        if( !strncmp( p_cfg->psz_name, "dst", strlen( "dst" ) ) )
        {
            sout_stream_t *s, *p_last;

            msg_Dbg( p_stream, " * adding `%s'", p_cfg->psz_value );
            s = sout_StreamChainNew( p_stream->p_sout, p_cfg->psz_value,
                p_stream->p_next, &p_last );

            if( s )
            {
                TAB_APPEND( p_sys->i_nb_streams, p_sys->pp_streams, s );
                TAB_APPEND( p_sys->i_nb_last_streams, p_sys->pp_last_streams,
                    p_last );
                TAB_APPEND( p_sys->i_nb_select,  p_sys->ppsz_select, NULL );
            }
        }
        else if( !strncmp( p_cfg->psz_name, "select", strlen( "select" ) ) )
        {
            char *psz = p_cfg->psz_value;
            if( p_sys->i_nb_select > 0 && psz && *psz )
            {
                char **ppsz_select = &p_sys->ppsz_select[p_sys->i_nb_select - 1];

                if( *ppsz_select )
                {
                    msg_Err( p_stream, " * ignore selection `%s' (it already has `%s')",
                             psz, *ppsz_select );
                }
                else
                {
                    msg_Dbg( p_stream, " * apply selection `%s'", psz );
                    *ppsz_select = strdup( psz );
                }
            }
        }
        else
        {
            msg_Err( p_stream, " * ignore unknown option `%s'", p_cfg->psz_name );
        }
    }

    if( p_sys->i_nb_streams == 0 )
    {
        msg_Err( p_stream, "no destination given" );
        free( p_sys );

        return VLC_EGENERIC;
    }

    p_stream->pf_add    = Add;
    p_stream->pf_del    = Del;
    p_stream->pf_send   = Send;
    p_stream->pf_control = Control;

    p_stream->p_sys     = p_sys;

    return VLC_SUCCESS;
}