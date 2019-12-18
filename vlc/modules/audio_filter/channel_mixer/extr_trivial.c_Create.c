#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_13__ {scalar_t__ i_physical_channels; scalar_t__ i_channels; scalar_t__ i_format; scalar_t__ i_rate; scalar_t__ i_chan_mode; } ;
struct TYPE_10__ {TYPE_5__ audio; } ;
struct TYPE_9__ {TYPE_5__ audio; } ;
struct TYPE_11__ {void* pf_audio_filter; TYPE_4__* p_sys; TYPE_2__ fmt_out; TYPE_1__ fmt_in; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_12__ {int /*<<< orphan*/  channel_map; } ;
typedef  TYPE_4__ filter_sys_t ;
typedef  int /*<<< orphan*/  channel_map ;
typedef  TYPE_5__ audio_format_t ;

/* Variables and functions */
 int const AOUT_CHANS_FRONT ; 
 int const AOUT_CHANS_MIDDLE ; 
 int AOUT_CHANS_REAR ; 
 int AOUT_CHAN_MAX ; 
 void* Downmix ; 
 void* Equals ; 
 void* Extract ; 
 void* Upmix ; 
 scalar_t__ VLC_CODEC_FL32 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 unsigned int aout_FormatNbChannels (TYPE_5__ const*) ; 
 int /*<<< orphan*/  assert (int const) ; 
 TYPE_4__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  msg_Info (TYPE_3__*,char*,int) ; 
 int* pi_vlc_chan_order_wg4 ; 

__attribute__((used)) static int Create( vlc_object_t *p_this )
{
    filter_t *p_filter = (filter_t *)p_this;
    const audio_format_t *infmt = &p_filter->fmt_in.audio;
    const audio_format_t *outfmt = &p_filter->fmt_out.audio;

    if( infmt->i_physical_channels == 0 )
    {
        assert( infmt->i_channels > 0 );
        if( outfmt->i_physical_channels == 0 )
            return VLC_EGENERIC;
        if( aout_FormatNbChannels( outfmt ) == infmt->i_channels )
        {
            p_filter->pf_audio_filter = Equals;
            return VLC_SUCCESS;
        }
        else
        {
            if( infmt->i_channels > AOUT_CHAN_MAX )
                msg_Info(p_filter, "%d channels will be dropped.",
                         infmt->i_channels - AOUT_CHAN_MAX);
            p_filter->pf_audio_filter = Extract;
            return VLC_SUCCESS;
        }
    }

    if( infmt->i_format != outfmt->i_format
     || infmt->i_rate != outfmt->i_rate
     || infmt->i_format != VLC_CODEC_FL32 )
        return VLC_EGENERIC;

    /* trivial is the lowest priority converter: if chan_mode are different
     * here, this filter will still need to convert channels (and ignore
     * chan_mode). */
    if( infmt->i_physical_channels == outfmt->i_physical_channels
     && infmt->i_chan_mode == outfmt->i_chan_mode )
        return VLC_EGENERIC;

    p_filter->p_sys = NULL;

    if ( aout_FormatNbChannels( outfmt ) == 1
      && aout_FormatNbChannels( infmt ) == 1 )
    {
        p_filter->pf_audio_filter = Equals;
        return VLC_SUCCESS;
    }

    /* Setup channel order */
    uint16_t i_in_physical_channels = infmt->i_physical_channels;
    uint16_t i_out_physical_channels = outfmt->i_physical_channels;

    /* Fill src_chans: contains a sorted index of all presents in channels */
    int i_src_idx = 0;
    int src_chans[AOUT_CHAN_MAX];
    for( unsigned i = 0; i < AOUT_CHAN_MAX; ++i )
        src_chans[i] = pi_vlc_chan_order_wg4[i] & i_in_physical_channels ?
                       i_src_idx++ : -1;

    unsigned i_dst_idx = 0;
    int channel_map[AOUT_CHAN_MAX];
    for( unsigned i = 0; i < AOUT_CHAN_MAX; ++i )
    {
        const uint32_t i_chan = pi_vlc_chan_order_wg4[i];
        if( !( i_chan & i_out_physical_channels ) )
            continue; /* Output channel not present */

        if( aout_FormatNbChannels( infmt ) == 1 )
        {
            /* Input is mono, copy the mono channel to Left,Right */
            if( i_chan & AOUT_CHANS_FRONT )
                channel_map[i_dst_idx] = 0;
            else
                channel_map[i_dst_idx] = -1;
        }
        else if( src_chans[i] != -1 )
        {
            /* Input and output have the same channel */
            assert( i_chan & i_in_physical_channels );
            channel_map[i_dst_idx] = src_chans[i];
        }
        else
        {
            if( ( i_chan & AOUT_CHANS_MIDDLE )
             && !( i_out_physical_channels & AOUT_CHANS_REAR ) )
            {
                /* Use Rear chans as Middle chans if Rear chans are not used */
                assert( i + 2 < AOUT_CHAN_MAX );
                assert( pi_vlc_chan_order_wg4[i + 2] & AOUT_CHANS_REAR );
                channel_map[i_dst_idx] = src_chans[i + 2];
            }
            else if( ( i_chan & AOUT_CHANS_REAR )
                  && !( i_out_physical_channels & AOUT_CHANS_MIDDLE ) )
            {
                /* Use Middle chans as Rear chans if Middle chans are not used */
                assert( (int) i - 2 >= 0 );
                assert( pi_vlc_chan_order_wg4[i - 2] & AOUT_CHANS_MIDDLE );
                channel_map[i_dst_idx] = src_chans[i - 2];
            }
            else
                channel_map[i_dst_idx] = -1;
        }
        i_dst_idx++;
    }
#ifndef NDEBUG
    for( unsigned i = 0; i < aout_FormatNbChannels( outfmt ); ++i )
    {
        assert( channel_map[i] == -1
             || (unsigned) channel_map[i] < aout_FormatNbChannels( infmt ) );
    }
#endif

    if( aout_FormatNbChannels( outfmt ) == aout_FormatNbChannels( infmt ) )
    {
        /* Channel layouts can be different but the channel order can be the
         * same. This is the case for AOUT_CHANS_5_1 <-> AOUT_CHANS_5_1_MIDDLE
         * for example. */
        bool b_equals = true;
        for( unsigned i = 0; i < aout_FormatNbChannels( outfmt ); ++i )
            if( channel_map[i] == -1 || (unsigned) channel_map[i] != i )
            {
                b_equals = false;
                break;
            }
        if( b_equals )
        {
            p_filter->pf_audio_filter = Equals;
            return VLC_SUCCESS;
        }
    }

    filter_sys_t *p_sys = malloc( sizeof(*p_sys) );
    if( !p_sys )
        return VLC_ENOMEM;
    p_filter->p_sys = p_sys;
    memcpy( p_sys->channel_map, channel_map, sizeof(channel_map) );

    if( aout_FormatNbChannels( outfmt ) > aout_FormatNbChannels( infmt ) )
        p_filter->pf_audio_filter = Upmix;
    else
        p_filter->pf_audio_filter = Downmix;

    return VLC_SUCCESS;
}