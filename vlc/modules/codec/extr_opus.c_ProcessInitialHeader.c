#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  bytes; scalar_t__ packet; } ;
typedef  TYPE_3__ ogg_packet ;
struct TYPE_12__ {int i_channels; int i_rate; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  i_physical_channels; } ;
struct TYPE_13__ {TYPE_1__ audio; } ;
struct TYPE_15__ {TYPE_2__ fmt_out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_17__ {int channels; int channel_mapping; unsigned char* stream_map; int /*<<< orphan*/  gain; int /*<<< orphan*/  nb_coupled; int /*<<< orphan*/  nb_streams; } ;
struct TYPE_16__ {int /*<<< orphan*/  end_date; int /*<<< orphan*/  p_st; TYPE_6__ header; } ;
typedef  TYPE_5__ decoder_sys_t ;
typedef  TYPE_6__ OpusHeader ;

/* Variables and functions */
 int AOUT_CHAN_MAX ; 
 int /*<<< orphan*/  AUDIO_CHANNEL_TYPE_AMBISONICS ; 
 int OPUS_OK ; 
 int /*<<< orphan*/  OPUS_SET_GAIN (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_CheckChannelReorder (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 int floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  opus_header_parse (unsigned char*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  opus_multistream_decoder_create (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int*) ; 
 int opus_multistream_decoder_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opus_multistream_decoder_destroy (int /*<<< orphan*/ ) ; 
#define  pi_3channels_in 133 
#define  pi_4channels_in 132 
#define  pi_5channels_in 131 
#define  pi_6channels_in 130 
#define  pi_7channels_in 129 
#define  pi_8channels_in 128 
 int /*<<< orphan*/ * pi_channels_maps ; 
 int /*<<< orphan*/  sqrt (int) ; 

__attribute__((used)) static int ProcessInitialHeader( decoder_t *p_dec, ogg_packet *p_oggpacket )
{
    int err;
    unsigned char* p_stream_map;
    unsigned char new_stream_map[8];
    decoder_sys_t *p_sys = p_dec->p_sys;

    OpusHeader *p_header = &p_sys->header;

    if( !opus_header_parse((unsigned char *)p_oggpacket->packet,p_oggpacket->bytes,p_header) )
    {
        msg_Err( p_dec, "cannot read Opus header" );
        return VLC_EGENERIC;
    }
    msg_Dbg( p_dec, "Opus audio with %d channels", p_header->channels);

    if((p_header->channels>2 && p_header->channel_mapping==0) ||
        (p_header->channels>8 && p_header->channel_mapping==1) ||
        (p_header->channels>18 && p_header->channel_mapping==2) ||
        p_header->channel_mapping>2)
    {
        msg_Err( p_dec, "Unsupported channel mapping" );
        return VLC_EGENERIC;
    }
    if (p_header->channel_mapping == 2)
    {
        int i_order = floor(sqrt(p_header->channels));
        int i_nondiegetic = p_header->channels - i_order * i_order;
        if (i_nondiegetic != 0 && i_nondiegetic != 2)
        {
            msg_Err( p_dec, "Unsupported ambisonic channel mapping" );
            return VLC_EGENERIC;
        }
    }

    /* Setup the format */
    p_dec->fmt_out.audio.i_channels = p_header->channels;
    p_dec->fmt_out.audio.i_rate = 48000;

    if (p_header->channel_mapping <= 1)
    {
        p_dec->fmt_out.audio.i_physical_channels =
            pi_channels_maps[p_header->channels];

        if( p_header->channels>2 )
        {
            static const uint32_t *pi_ch[6] = { pi_3channels_in, pi_4channels_in,
                                                pi_5channels_in, pi_6channels_in,
                                                pi_7channels_in, pi_8channels_in };
            uint8_t pi_chan_table[AOUT_CHAN_MAX];

            aout_CheckChannelReorder( pi_ch[p_header->channels-3], NULL,
                                      p_dec->fmt_out.audio.i_physical_channels,
                                      pi_chan_table );
            for(int i=0;i<p_header->channels;i++)
                new_stream_map[pi_chan_table[i]]=p_header->stream_map[i];

            p_stream_map = new_stream_map;
        }
        else
            p_stream_map = p_header->stream_map;
    }
    else //p_header->channel_mapping == 2
    {
        p_dec->fmt_out.audio.channel_type = AUDIO_CHANNEL_TYPE_AMBISONICS;
        p_stream_map = p_header->stream_map;
    }

    /* Opus decoder init */
    p_sys->p_st = opus_multistream_decoder_create( 48000, p_header->channels,
                    p_header->nb_streams, p_header->nb_coupled,
                    p_stream_map,
                    &err );
    if( !p_sys->p_st || err!=OPUS_OK )
    {
        msg_Err( p_dec, "decoder initialization failed" );
        return VLC_EGENERIC;
    }

#ifdef OPUS_SET_GAIN
    if( opus_multistream_decoder_ctl( p_sys->p_st,OPUS_SET_GAIN(p_header->gain) ) != OPUS_OK )
    {
        msg_Err( p_dec, "OPUS_SET_GAIN failed" );
        opus_multistream_decoder_destroy( p_sys->p_st );
        return VLC_EGENERIC;
    }
#endif

    date_Init( &p_sys->end_date, 48000, 1 );

    return VLC_SUCCESS;
}