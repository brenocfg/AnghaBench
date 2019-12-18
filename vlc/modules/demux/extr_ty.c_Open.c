#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {void* i_group; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_13__ {int /*<<< orphan*/  force; } ;
struct TYPE_15__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_4__* p_sys; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; TYPE_1__ obj; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_16__ {int b_first_chunk; int b_have_master; scalar_t__ audio_type; int /*<<< orphan*/  xds; int /*<<< orphan*/  cc; int /*<<< orphan*/ ** p_cc; void* p_video; void* p_audio; int /*<<< orphan*/  b_seekable; scalar_t__ l_ac3_pkt_size; scalar_t__ i_Pts_Offset; scalar_t__ i_Pes_Length; int /*<<< orphan*/  tivo_series; int /*<<< orphan*/  tivo_type; int /*<<< orphan*/  i_stream_size; void* lastVideoPTS; void* lastAudioPTS; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int CHUNK_SIZE ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 int /*<<< orphan*/  STREAM_CAN_SEEK ; 
 scalar_t__ TIVO_AUDIO_MPEG ; 
 scalar_t__ TIVO_AUDIO_UNKNOWN ; 
 int TIVO_PES_FILEID ; 
 int /*<<< orphan*/  TIVO_SERIES_UNKNOWN ; 
 int /*<<< orphan*/  TIVO_TYPE_UNKNOWN ; 
 void* TY_ES_GROUP ; 
 int U32_AT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_A52 ; 
 int /*<<< orphan*/  VLC_CODEC_MPGA ; 
 int /*<<< orphan*/  VLC_CODEC_MPGV ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 scalar_t__ VLC_SUCCESS ; 
 void* VLC_TICK_INVALID ; 
 int /*<<< orphan*/  XdsInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  demux_IsPathExtension (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* es_out_Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 scalar_t__ probe_stream (TYPE_3__*) ; 
 int /*<<< orphan*/  stream_Size (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static int Open(vlc_object_t *p_this)
{
    demux_t *p_demux = (demux_t *)p_this;
    demux_sys_t *p_sys;
    es_format_t fmt;
    const uint8_t *p_peek;
    int i;

    /* peek at the first 12 bytes. */
    /* for TY streams, they're always the same */
    if( vlc_stream_Peek( p_demux->s, &p_peek, 12 ) < 12 )
        return VLC_EGENERIC;

    if ( U32_AT(p_peek) != TIVO_PES_FILEID ||
         U32_AT(&p_peek[4]) != 0x02 ||
         U32_AT(&p_peek[8]) != CHUNK_SIZE )
    {
        if( !p_demux->obj.force &&
            !demux_IsPathExtension( p_demux, ".ty" ) &&
            !demux_IsPathExtension( p_demux, ".ty+" ) )
            return VLC_EGENERIC;
        msg_Warn( p_demux, "this does not look like a TY file, "
                           "continuing anyway..." );
    }

    /* at this point, we assume we have a valid TY stream */
    msg_Dbg( p_demux, "valid TY stream detected" );

    p_sys = malloc(sizeof(demux_sys_t));
    if( unlikely(p_sys == NULL) )
        return VLC_ENOMEM;

    /* Set exported functions */
    p_demux->pf_demux = Demux;
    p_demux->pf_control = Control;

    /* create our structure that will hold all data */
    p_demux->p_sys = p_sys;
    memset(p_sys, 0, sizeof(demux_sys_t));

    /* set up our struct (most were zero'd out with the memset above) */
    p_sys->b_first_chunk = true;
    p_sys->b_have_master = (U32_AT(p_peek) == TIVO_PES_FILEID);
    p_sys->lastAudioPTS  = VLC_TICK_INVALID;
    p_sys->lastVideoPTS  = VLC_TICK_INVALID;
    p_sys->i_stream_size = stream_Size(p_demux->s);
    p_sys->tivo_type = TIVO_TYPE_UNKNOWN;
    p_sys->audio_type = TIVO_AUDIO_UNKNOWN;
    p_sys->tivo_series = TIVO_SERIES_UNKNOWN;
    p_sys->i_Pes_Length = 0;
    p_sys->i_Pts_Offset = 0;
    p_sys->l_ac3_pkt_size = 0;

    /* see if this stream is seekable */
    vlc_stream_Control( p_demux->s, STREAM_CAN_SEEK, &p_sys->b_seekable );

    if (probe_stream(p_demux) != VLC_SUCCESS) {
        //TyClose(p_demux);
        return VLC_EGENERIC;
    }

    if (!p_sys->b_have_master)
      msg_Warn(p_demux, "No master chunk found; seeking will be limited.");

    /* register the proper audio codec */
    if (p_sys->audio_type == TIVO_AUDIO_MPEG) {
        es_format_Init( &fmt, AUDIO_ES, VLC_CODEC_MPGA );
    } else {
        es_format_Init( &fmt, AUDIO_ES, VLC_CODEC_A52 );
    }
    fmt.i_group = TY_ES_GROUP;
    p_sys->p_audio = es_out_Add( p_demux->out, &fmt );

    /* register the video stream */
    es_format_Init( &fmt, VIDEO_ES, VLC_CODEC_MPGV );
    fmt.i_group = TY_ES_GROUP;
    p_sys->p_video = es_out_Add( p_demux->out, &fmt );

    /* */
    for( i = 0; i < 4; i++ )
        p_sys->p_cc[i] = NULL;
    cc_Init( &p_sys->cc );

    XdsInit( &p_sys->xds );

    return VLC_SUCCESS;
}