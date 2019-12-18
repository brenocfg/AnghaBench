#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ sout_mux_t ;
struct TYPE_17__ {int i_streams; int i_stream_video; TYPE_6__* stream; } ;
typedef  TYPE_4__ sout_mux_sys_t ;
struct TYPE_18__ {TYPE_7__* p_sys; int /*<<< orphan*/  fmt; TYPE_2__* p_fmt; } ;
typedef  TYPE_5__ sout_input_t ;
struct TYPE_19__ {int i_cat; int* fcc; int f_fps; int i_bitrate; scalar_t__ i_duration; scalar_t__ i_frames; scalar_t__ i_totalsize; int /*<<< orphan*/ * p_bih; int /*<<< orphan*/  i_bih; TYPE_7__* p_wf; } ;
typedef  TYPE_6__ avi_stream_t ;
struct TYPE_20__ {int nChannels; int nSamplesPerSec; int nBlockAlign; int nAvgBytesPerSec; int wBitsPerSample; void* wFormatTag; int /*<<< orphan*/  cbSize; } ;
typedef  TYPE_7__ WAVEFORMATEX ;
struct TYPE_14__ {int i_channels; int i_rate; int i_blockalign; } ;
struct TYPE_15__ {int i_cat; int i_bitrate; int /*<<< orphan*/  i_codec; TYPE_1__ audio; int /*<<< orphan*/  i_extra; int /*<<< orphan*/  p_extra; } ;

/* Variables and functions */
#define  AUDIO_ES 141 
 int /*<<< orphan*/ * CreateBitmapInfoHeader (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  VIDEO_ES 140 
#define  VLC_CODEC_A52 139 
#define  VLC_CODEC_ALAW 138 
#define  VLC_CODEC_MP3 137 
#define  VLC_CODEC_MULAW 136 
#define  VLC_CODEC_S16L 135 
#define  VLC_CODEC_S24L 134 
#define  VLC_CODEC_S32L 133 
#define  VLC_CODEC_U8 132 
#define  VLC_CODEC_WMA1 131 
#define  VLC_CODEC_WMA2 130 
#define  VLC_CODEC_WMAL 129 
#define  VLC_CODEC_WMAP 128 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 void* WAVE_FORMAT_A52 ; 
 void* WAVE_FORMAT_ALAW ; 
 void* WAVE_FORMAT_MPEGLAYER3 ; 
 void* WAVE_FORMAT_MULAW ; 
 void* WAVE_FORMAT_PCM ; 
 void* WAVE_FORMAT_WMA1 ; 
 void* WAVE_FORMAT_WMA2 ; 
 void* WAVE_FORMAT_WMAL ; 
 void* WAVE_FORMAT_WMAP ; 
 int /*<<< orphan*/  free (TYPE_7__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 

__attribute__((used)) static int AddStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    sout_mux_sys_t  *p_sys = p_mux->p_sys;
    avi_stream_t    *p_stream;

    if( p_sys->i_streams >= 100 )
    {
        msg_Err( p_mux, "too many streams" );
        return VLC_EGENERIC;
    }

    msg_Dbg( p_mux, "adding input" );
    p_input->p_sys = malloc( sizeof( int ) );
    if( !p_input->p_sys )
        return VLC_ENOMEM;

    *((int*)p_input->p_sys) = p_sys->i_streams;
    p_stream = &p_sys->stream[p_sys->i_streams];

    switch( p_input->p_fmt->i_cat )
    {
        case AUDIO_ES:
            p_stream->i_cat = AUDIO_ES;
            p_stream->fcc[0] = '0' + p_sys->i_streams / 10;
            p_stream->fcc[1] = '0' + p_sys->i_streams % 10;
            p_stream->fcc[2] = 'w';
            p_stream->fcc[3] = 'b';

            p_stream->p_bih = NULL;
            p_stream->i_bih = 0;

            WAVEFORMATEX *p_wf  = malloc( sizeof( WAVEFORMATEX ) +
                                  p_input->p_fmt->i_extra );
            if( !p_wf )
            {
                free( p_input->p_sys );
                p_input->p_sys = NULL;
                return VLC_ENOMEM;
            }

            p_wf->cbSize = p_input->p_fmt->i_extra;
            if( p_wf->cbSize > 0 )
            {
                memcpy( &p_wf[1],
                        p_input->p_fmt->p_extra,
                        p_input->p_fmt->i_extra );
            }
            p_wf->nChannels      = p_input->p_fmt->audio.i_channels;
            p_wf->nSamplesPerSec = p_input->p_fmt->audio.i_rate;
            p_wf->nBlockAlign    = p_input->p_fmt->audio.i_blockalign;
            p_wf->nAvgBytesPerSec= p_input->p_fmt->i_bitrate / 8;
            p_wf->wBitsPerSample = 0;

            switch( p_input->p_fmt->i_codec )
            {
                case VLC_CODEC_A52:
                    p_wf->wFormatTag = WAVE_FORMAT_A52;
                    p_wf->nBlockAlign= 1;
                    break;
                case VLC_CODEC_MP3:
                    p_wf->wFormatTag = WAVE_FORMAT_MPEGLAYER3;
                    p_wf->nBlockAlign= 1;
                    break;
                case VLC_CODEC_WMA1:
                    p_wf->wFormatTag = WAVE_FORMAT_WMA1;
                    break;
                case VLC_CODEC_WMA2:
                    p_wf->wFormatTag = WAVE_FORMAT_WMA2;
                    break;
                case VLC_CODEC_WMAP:
                    p_wf->wFormatTag = WAVE_FORMAT_WMAP;
                    break;
                case VLC_CODEC_WMAL:
                    p_wf->wFormatTag = WAVE_FORMAT_WMAL;
                    break;
                case VLC_CODEC_ALAW:
                    p_wf->wFormatTag = WAVE_FORMAT_ALAW;
                    break;
                case VLC_CODEC_MULAW:
                    p_wf->wFormatTag = WAVE_FORMAT_MULAW;
                    break;
                    /* raw codec */
                case VLC_CODEC_U8:
                    p_wf->wFormatTag = WAVE_FORMAT_PCM;
                    p_wf->nBlockAlign= p_wf->nChannels;
                    p_wf->wBitsPerSample = 8;
                    p_wf->nAvgBytesPerSec = (p_wf->wBitsPerSample/8) *
                                      p_wf->nSamplesPerSec * p_wf->nChannels;
                    break;
                case VLC_CODEC_S16L:
                    p_wf->wFormatTag = WAVE_FORMAT_PCM;
                    p_wf->nBlockAlign= 2 * p_wf->nChannels;
                    p_wf->wBitsPerSample = 16;
                    p_wf->nAvgBytesPerSec = (p_wf->wBitsPerSample/8) *
                                      p_wf->nSamplesPerSec * p_wf->nChannels;
                    break;
                case VLC_CODEC_S24L:
                    p_wf->wFormatTag = WAVE_FORMAT_PCM;
                    p_wf->nBlockAlign= 3 * p_wf->nChannels;
                    p_wf->wBitsPerSample = 24;
                    p_wf->nAvgBytesPerSec = (p_wf->wBitsPerSample/8) *
                                      p_wf->nSamplesPerSec * p_wf->nChannels;
                    break;
                case VLC_CODEC_S32L:
                    p_wf->wFormatTag = WAVE_FORMAT_PCM;
                    p_wf->nBlockAlign= 4 * p_wf->nChannels;
                    p_wf->wBitsPerSample = 32;
                    p_wf->nAvgBytesPerSec = (p_wf->wBitsPerSample/8) *
                                      p_wf->nSamplesPerSec * p_wf->nChannels;
                    break;
                default:
                    free( p_wf );
                    free( p_input->p_sys );
                    p_input->p_sys = NULL;
                    return VLC_EGENERIC;
            }
            p_stream->p_wf = p_wf;
            break;
        case VIDEO_ES:
            p_stream->i_cat = VIDEO_ES;
            p_stream->fcc[0] = '0' + p_sys->i_streams / 10;
            p_stream->fcc[1] = '0' + p_sys->i_streams % 10;
            p_stream->fcc[2] = 'd';
            p_stream->fcc[3] = 'c';
            if( p_sys->i_stream_video < 0 )
            {
                p_sys->i_stream_video = p_sys->i_streams;
            }
            p_stream->p_wf  = NULL;
            p_stream->p_bih = CreateBitmapInfoHeader( &p_input->fmt, &p_stream->i_bih );
            if( !p_stream->p_bih )
            {
                free( p_input->p_sys );
                p_input->p_sys = NULL;
                return VLC_ENOMEM;
            }
            break;
        default:
            free( p_input->p_sys );
            p_input->p_sys = NULL;
            return( VLC_EGENERIC );
    }
    p_stream->i_totalsize = 0;
    p_stream->i_frames    = 0;
    p_stream->i_duration  = 0;

    /* fixed later */
    p_stream->f_fps = 25;
    p_stream->i_bitrate = 128 * 1024;

    p_sys->i_streams++;
    return( VLC_SUCCESS );
}