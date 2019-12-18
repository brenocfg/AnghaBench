#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {TYPE_3__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/ * out; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_11__ {unsigned int i_forced_aspect; unsigned int i_aspect; void* psz_telx_lang; void* psz_telx; TYPE_1__* p_audios; int /*<<< orphan*/  i_id_video; int /*<<< orphan*/  i_last_state_change; int /*<<< orphan*/  i_state; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_9__ {int i_group; int i_pair; int i_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DemuxControl ; 
 int /*<<< orphan*/  DemuxDemux ; 
 int /*<<< orphan*/  STATE_NOSYNC ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 unsigned int VOUT_ASPECT_FACTOR ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,char*) ; 
 int sscanf (char*,char*,int*,int*) ; 
 char* strchr (char*,char) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  var_InheritInteger (TYPE_2__*,char*) ; 
 void* var_InheritString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  var_InheritURational (TYPE_2__*,unsigned int*,unsigned int*,char*) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

__attribute__((used)) static int DemuxOpen( vlc_object_t *p_this )
{
    demux_t     *p_demux = (demux_t *)p_this;
    demux_sys_t *p_sys;
    char        *psz_parser;

    if (p_demux->out == NULL)
        return VLC_EGENERIC;

    /* Fill p_demux field */
    p_demux->pf_demux = DemuxDemux;
    p_demux->pf_control = DemuxControl;
    p_demux->p_sys = p_sys = calloc( 1, sizeof( demux_sys_t ) );
    if( unlikely(!p_sys ) )
        return VLC_ENOMEM;

    p_sys->i_state = STATE_NOSYNC;
    p_sys->i_last_state_change = vlc_tick_now();

    /* SDI AR */
    unsigned int i_num, i_den;
    if ( !var_InheritURational( p_demux, &i_num, &i_den,
                               "linsys-hdsdi-aspect-ratio" ) && i_den != 0 )
        p_sys->i_forced_aspect = p_sys->i_aspect =
                i_num * VOUT_ASPECT_FACTOR / i_den;
    else
        p_sys->i_forced_aspect = 0;

    /* */
    p_sys->i_id_video = var_InheritInteger( p_demux, "linsys-sdi-id-video" );

    /* Audio ES */
    char *psz_string = psz_parser = var_InheritString( p_demux,
                                                       "linsys-sdi-audio" );
    int i = 0;

    while ( psz_parser != NULL && *psz_parser )
    {
        int i_id, i_group, i_pair;
        char *psz_next = strchr( psz_parser, '=' );
        if ( psz_next != NULL )
        {
            *psz_next = '\0';
            i_id = strtol( psz_parser, NULL, 0 );
            psz_parser = psz_next + 1;
        }
        else
            i_id = 0;

        psz_next = strchr( psz_parser, ':' );
        if ( psz_next != NULL )
        {
            *psz_next = '\0';
            psz_next++;
        }

        if ( sscanf( psz_parser, "%d,%d", &i_group, &i_pair ) == 2 )
        {
            p_sys->p_audios[i].i_group = i_group;
            p_sys->p_audios[i].i_pair = i_pair;
            p_sys->p_audios[i].i_id = i_id;
            i++;
        }
        else
            msg_Warn( p_demux, "malformed audio configuration (%s)",
                      psz_parser );

        psz_parser = psz_next;
    }
    free( psz_string );

    /* Teletext ES */
    p_sys->psz_telx = var_InheritString( p_demux, "linsys-sdi-telx" );

    p_sys->psz_telx_lang = var_InheritString( p_demux, "linsys-sdi-telx-lang" );

    return VLC_SUCCESS;
}