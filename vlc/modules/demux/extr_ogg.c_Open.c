#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  force; } ;
struct TYPE_9__ {scalar_t__ (* pf_demux ) (TYPE_2__*) ;scalar_t__ b_preparsing; int /*<<< orphan*/  pf_control; TYPE_3__* p_sys; int /*<<< orphan*/  s; TYPE_1__ obj; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_10__ {int i_length; int b_preparsing_done; int /*<<< orphan*/  pp_seekpoints; int /*<<< orphan*/  i_seekpoints; int /*<<< orphan*/  oy; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 scalar_t__ Demux (TYPE_2__*) ; 
 int /*<<< orphan*/  Ogg_CreateES (TYPE_2__*) ; 
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  ogg_sync_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* stream_ContentType (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static int Open( vlc_object_t * p_this )
{
    demux_t *p_demux = (demux_t *)p_this;
    demux_sys_t    *p_sys;
    const uint8_t  *p_peek;

    /* Check if we are dealing with an ogg stream */
    if( vlc_stream_Peek( p_demux->s, &p_peek, 4 ) < 4 ) return VLC_EGENERIC;
    if( !p_demux->obj.force && memcmp( p_peek, "OggS", 4 ) )
    {
        char *psz_mime = stream_ContentType( p_demux->s );
        if( !psz_mime )
        {
            return VLC_EGENERIC;
        }
        else if ( strcmp( psz_mime, "application/ogg" ) &&
                  strcmp( psz_mime, "video/ogg" ) &&
                  strcmp( psz_mime, "audio/ogg" ) )
        {
            free( psz_mime );
            return VLC_EGENERIC;
        }
        free( psz_mime );
    }

    /* */
    p_demux->p_sys = p_sys = calloc( 1, sizeof( demux_sys_t ) );
    if( !p_sys )
        return VLC_ENOMEM;

    p_sys->i_length = -1;
    p_sys->b_preparsing_done = false;

    /* Set exported functions */
    p_demux->pf_demux = Demux;
    p_demux->pf_control = Control;

    /* Initialize the Ogg physical bitstream parser */
    ogg_sync_init( &p_sys->oy );

    /* */
    TAB_INIT( p_sys->i_seekpoints, p_sys->pp_seekpoints );


    while ( !p_sys->b_preparsing_done && p_demux->pf_demux( p_demux ) > 0 )
    {}
    if ( p_sys->b_preparsing_done && p_demux->b_preparsing )
        Ogg_CreateES( p_demux );

    return VLC_SUCCESS;
}