#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/ * psz_uri; int /*<<< orphan*/  i_media_type; } ;
typedef  TYPE_1__ sdp_t ;
struct TYPE_13__ {int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  pf_control; TYPE_3__* p_sys; int /*<<< orphan*/  s; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_14__ {TYPE_1__* p_sdp; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 int /*<<< orphan*/  FREENULL (char*) ; 
 int /*<<< orphan*/  FreeSDP (TYPE_1__*) ; 
 int /*<<< orphan*/  IsWellKnownPayload (int /*<<< orphan*/ ) ; 
 scalar_t__ ParseConnection (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ParseSDP (int /*<<< orphan*/ ,char*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_CreateGetBool (TYPE_2__*,char*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 size_t vlc_stream_Read (int /*<<< orphan*/ ,char*,int const) ; 

__attribute__((used)) static int OpenDemux( vlc_object_t *p_this )
{
    demux_t *p_demux = (demux_t *)p_this;
    const uint8_t *p_peek;
    char *psz_sdp = NULL;
    sdp_t *p_sdp = NULL;
    int errval = VLC_EGENERIC;
    size_t i_len;

    if( !var_CreateGetBool( p_demux, "sap-parse" ) )
    {
        /* We want livedotcom module to parse this SDP file */
        return VLC_EGENERIC;
    }

    assert( p_demux->s ); /* this is NOT an access_demux */

    /* Probe for SDP */
    if( vlc_stream_Peek( p_demux->s, &p_peek, 7 ) < 7 )
        return VLC_EGENERIC;

    if( memcmp( p_peek, "v=0\r\no=", 7 ) && memcmp( p_peek, "v=0\no=", 6 ) )
        return VLC_EGENERIC;

    /* Gather the complete sdp file */
    for( i_len = 0, psz_sdp = NULL; i_len < 65536; )
    {
        const int i_read_max = 1024;
        char *psz_sdp_new = realloc( psz_sdp, i_len + i_read_max + 1 );
        size_t i_read;
        if( psz_sdp_new == NULL )
        {
            errval = VLC_ENOMEM;
            goto error;
        }
        psz_sdp = psz_sdp_new;

        i_read = vlc_stream_Read( p_demux->s, &psz_sdp[i_len], i_read_max );
        if( (int)i_read < 0 )
        {
            msg_Err( p_demux, "cannot read SDP" );
            goto error;
        }
        i_len += i_read;

        psz_sdp[i_len] = '\0';

        if( (int)i_read < i_read_max )
            break; // EOF
    }

    p_sdp = ParseSDP( VLC_OBJECT(p_demux), psz_sdp );

    if( !p_sdp )
    {
        msg_Warn( p_demux, "invalid SDP");
        goto error;
    }

    if( ParseConnection( VLC_OBJECT( p_demux ), p_sdp ) )
    {
        p_sdp->psz_uri = NULL;
    }
    if (!IsWellKnownPayload (p_sdp->i_media_type))
        goto error;
    if( p_sdp->psz_uri == NULL ) goto error;

    demux_sys_t *p_sys = malloc( sizeof(*p_sys) );
    if( unlikely(p_sys == NULL) )
        goto error;
    p_sys->p_sdp = p_sdp;
    p_demux->p_sys = p_sys;
    p_demux->pf_control = Control;
    p_demux->pf_demux = Demux;

    FREENULL( psz_sdp );
    return VLC_SUCCESS;

error:
    FREENULL( psz_sdp );
    if( p_sdp ) FreeSDP( p_sdp );
    return errval;
}