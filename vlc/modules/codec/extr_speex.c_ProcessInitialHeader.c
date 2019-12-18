#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  bytes; scalar_t__ packet; } ;
typedef  TYPE_3__ ogg_packet ;
struct TYPE_17__ {size_t i_channels; int /*<<< orphan*/  i_rate; int /*<<< orphan*/  i_physical_channels; } ;
struct TYPE_18__ {TYPE_1__ audio; } ;
struct TYPE_20__ {TYPE_2__ fmt_out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_21__ {int /*<<< orphan*/  end_date; int /*<<< orphan*/  stereo; void* p_state; int /*<<< orphan*/  bits; TYPE_7__* p_header; } ;
typedef  TYPE_5__ decoder_sys_t ;
struct TYPE_24__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  func; int /*<<< orphan*/  callback_id; } ;
struct TYPE_23__ {size_t mode; int speex_version_id; scalar_t__ mode_bitstream_version; int nb_channels; int /*<<< orphan*/  rate; scalar_t__ vbr; } ;
struct TYPE_22__ {scalar_t__ bitstream_version; int /*<<< orphan*/  modeName; } ;
typedef  int /*<<< orphan*/  SpeexStereoState ;
typedef  TYPE_6__ SpeexMode ;
typedef  TYPE_7__ SpeexHeader ;
typedef  TYPE_8__ SpeexCallback ;

/* Variables and functions */
 int /*<<< orphan*/  SPEEX_INBAND_STEREO ; 
 size_t SPEEX_NB_MODES ; 
 int /*<<< orphan*/  SPEEX_SET_HANDLER ; 
 int /*<<< orphan*/  SPEEX_STEREO_STATE_INIT ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  speex_bits_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speex_decoder_ctl (void*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 void* speex_decoder_init (TYPE_6__ const*) ; 
 TYPE_6__** speex_mode_list ; 
 TYPE_7__* speex_packet_to_header (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  speex_std_stereo_request_handler ; 
 int /*<<< orphan*/ * vlc_chan_maps ; 

__attribute__((used)) static int ProcessInitialHeader( decoder_t *p_dec, ogg_packet *p_oggpacket )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    void *p_state;
    SpeexHeader *p_header;
    const SpeexMode *p_mode;
    SpeexCallback callback;

    p_sys->p_header = p_header =
        speex_packet_to_header( (char *)p_oggpacket->packet,
                                p_oggpacket->bytes );
    if( !p_header )
    {
        msg_Err( p_dec, "cannot read Speex header" );
        return VLC_EGENERIC;
    }
    if( p_header->mode >= SPEEX_NB_MODES || p_header->mode < 0 )
    {
        msg_Err( p_dec, "mode number %d does not (yet/any longer) exist in "
                 "this version of libspeex.", p_header->mode );
        return VLC_EGENERIC;
    }

    p_mode = speex_mode_list[p_header->mode];
    if( p_mode == NULL )
        return VLC_EGENERIC;

    if( p_header->speex_version_id > 1 )
    {
        msg_Err( p_dec, "this file was encoded with Speex bit-stream "
                 "version %d which is not supported by this decoder.",
                 p_header->speex_version_id );
        return VLC_EGENERIC;
    }

    if( p_mode->bitstream_version < p_header->mode_bitstream_version )
    {
        msg_Err( p_dec, "file encoded with a newer version of Speex." );
        return VLC_EGENERIC;
    }
    if( p_mode->bitstream_version > p_header->mode_bitstream_version )
    {
        msg_Err( p_dec, "file encoded with an older version of Speex." );
        return VLC_EGENERIC;
    }

    msg_Dbg( p_dec, "Speex %d Hz audio using %s mode %s%s",
             p_header->rate, p_mode->modeName,
             ( p_header->nb_channels == 1 ) ? " (mono" : " (stereo",
             p_header->vbr ? ", VBR)" : ")" );

    /* Take care of speex decoder init */
    speex_bits_init( &p_sys->bits );
    p_sys->p_state = p_state = speex_decoder_init( p_mode );
    if( !p_state )
    {
        msg_Err( p_dec, "decoder initialization failed" );
        return VLC_EGENERIC;
    }

    if( p_header->nb_channels == 2 )
    {
        SpeexStereoState stereo = SPEEX_STEREO_STATE_INIT;
        p_sys->stereo = stereo;
        callback.callback_id = SPEEX_INBAND_STEREO;
        callback.func = speex_std_stereo_request_handler;
        callback.data = &p_sys->stereo;
        speex_decoder_ctl( p_state, SPEEX_SET_HANDLER, &callback );
    }
    if( p_header->nb_channels <= 0 ||
        p_header->nb_channels > 5 )
    {
        msg_Err( p_dec, "invalid number of channels (not between 1 and 5): %i",
                 p_header->nb_channels );
        return VLC_EGENERIC;
    }

    /* Setup the format */
    p_dec->fmt_out.audio.i_physical_channels =
        vlc_chan_maps[p_header->nb_channels];
    p_dec->fmt_out.audio.i_channels = p_header->nb_channels;
    p_dec->fmt_out.audio.i_rate = p_header->rate;

    date_Init( &p_sys->end_date, p_header->rate, 1 );

    return VLC_SUCCESS;
}