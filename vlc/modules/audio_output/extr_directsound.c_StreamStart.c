#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  audio_sample_format_t ;
struct TYPE_15__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  flush; int /*<<< orphan*/  pause; int /*<<< orphan*/  play; int /*<<< orphan*/  time_get; TYPE_3__* sys; } ;
typedef  TYPE_2__ aout_stream_t ;
struct TYPE_16__ {void* p_dsobject; } ;
typedef  TYPE_3__ aout_stream_sys_t ;
struct TYPE_18__ {int cbDirectXAudioActivationParams; int /*<<< orphan*/  dwAudioStreamFlags; int /*<<< orphan*/  const guidAudioSession; } ;
struct TYPE_14__ {int cbSize; int /*<<< orphan*/ * pBlobData; } ;
struct TYPE_17__ {TYPE_1__ blob; int /*<<< orphan*/  vt; } ;
typedef  TYPE_4__ PROPVARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  TYPE_5__ DIRECTX_AUDIO_ACTIVATION_PARAMS ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDirectSound ; 
 int /*<<< orphan*/  PropVariantInit (TYPE_4__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  Start (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StreamFlush ; 
 int /*<<< orphan*/  StreamPause ; 
 int /*<<< orphan*/  StreamPlay ; 
 int /*<<< orphan*/  StreamStop ; 
 int /*<<< orphan*/  StreamTimeGet ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  VT_BLOB ; 
 int /*<<< orphan*/  aout_stream_Activate (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*,void**) ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT StreamStart( aout_stream_t *s,
                            audio_sample_format_t *restrict fmt,
                            const GUID *sid )
{
    aout_stream_sys_t *sys = calloc( 1, sizeof( *sys ) );
    if( unlikely(sys == NULL) )
        return E_OUTOFMEMORY;

    void *pv;
    HRESULT hr;
    if( sid )
    {
        DIRECTX_AUDIO_ACTIVATION_PARAMS params = {
            .cbDirectXAudioActivationParams = sizeof( params ),
            .guidAudioSession = *sid,
            .dwAudioStreamFlags = 0,
        };
        PROPVARIANT prop;

        PropVariantInit( &prop );
        prop.vt = VT_BLOB;
        prop.blob.cbSize = sizeof( params );
        prop.blob.pBlobData = (BYTE *)&params;

        hr = aout_stream_Activate( s, &IID_IDirectSound, &prop, &pv );
    }
    else
        hr = aout_stream_Activate( s, &IID_IDirectSound, NULL, &pv );
    if( FAILED(hr) )
        goto error;

    sys->p_dsobject = pv;

    hr = Start( VLC_OBJECT(s), sys, fmt );
    if( FAILED(hr) )
        goto error;

    s->sys = sys;
    s->time_get = StreamTimeGet;
    s->play = StreamPlay;
    s->pause = StreamPause;
    s->flush = StreamFlush;
    s->stop = StreamStop;
    return S_OK;
error:
    free( sys );
    return hr;
}