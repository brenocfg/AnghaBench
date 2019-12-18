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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  es_out_id_t ;
struct TYPE_10__ {int i_bitspersample; int i_channels; int i_rate; int /*<<< orphan*/  i_format; } ;
struct TYPE_8__ {int i_bitrate; TYPE_3__ audio; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_1__ es_format_t ;
struct TYPE_9__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_2__ demux_t ;
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  int REFERENCE_TIME ;
typedef  int /*<<< orphan*/  IAudioClient ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AUDCLNT_SHAREMODE_SHARED ; 
 int /*<<< orphan*/  AUDCLNT_STREAMFLAGS_EVENTCALLBACK ; 
 int /*<<< orphan*/  AUDCLNT_STREAMFLAGS_LOOPBACK ; 
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAudioClient_GetMixFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IAudioClient_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MSFTIME_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * es_out_Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 scalar_t__ vlc_FromWave (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static es_out_id_t *CreateES(demux_t *demux, IAudioClient *client, bool loop,
                             vlc_tick_t caching, size_t *restrict frame_size)
{
    es_format_t fmt;
    WAVEFORMATEX *pwf;
    HRESULT hr;

    hr = IAudioClient_GetMixFormat(client, &pwf);
    if (FAILED(hr))
    {
        msg_Err(demux, "cannot get mix format (error 0x%lX)", hr);
        return NULL;
    }

    es_format_Init(&fmt, AUDIO_ES, 0);
    if (vlc_FromWave(pwf, &fmt.audio))
    {
        msg_Err(demux, "unsupported mix format");
        CoTaskMemFree(pwf);
        return NULL;
    }

    fmt.i_codec = fmt.audio.i_format;
    fmt.i_bitrate = fmt.audio.i_bitspersample * fmt.audio.i_channels
                                              * fmt.audio.i_rate;
    *frame_size = fmt.audio.i_bitspersample * fmt.audio.i_channels / 8;

    DWORD flags = AUDCLNT_STREAMFLAGS_EVENTCALLBACK;
    if (loop)
        flags |= AUDCLNT_STREAMFLAGS_LOOPBACK;

    /* Request at least thrice the PTS delay */
    REFERENCE_TIME bufsize = MSFTIME_FROM_VLC_TICK( caching ) * 3;

    hr = IAudioClient_Initialize(client, AUDCLNT_SHAREMODE_SHARED, flags,
                                 bufsize, 0, pwf, NULL);
    CoTaskMemFree(pwf);
    if (FAILED(hr))
    {
        msg_Err(demux, "cannot initialize audio client (error 0x%lX)", hr);
        return NULL;
    }
    return es_out_Add(demux->out, &fmt);
}