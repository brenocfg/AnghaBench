#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {scalar_t__ i_last_read; scalar_t__ i_data; int i_bytes_per_sample; int /*<<< orphan*/  i_rate; int /*<<< orphan*/  p_dsbuffer; } ;
typedef  TYPE_1__ aout_stream_sys_t ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int DSBSTATUS_PLAYING ; 
 scalar_t__ DSERR_GENERIC ; 
 scalar_t__ DSERR_INVALIDCALL ; 
 scalar_t__ DS_BUF_SIZE ; 
 scalar_t__ DS_OK ; 
 int /*<<< orphan*/  Flush (TYPE_1__*) ; 
 scalar_t__ IDirectSoundBuffer_GetCurrentPosition (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSoundBuffer_GetStatus (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vlc_tick_from_samples (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT TimeGet( aout_stream_sys_t *sys, vlc_tick_t *delay )
{
    DWORD read, status;
    HRESULT hr;
    ssize_t size;

    hr = IDirectSoundBuffer_GetStatus( sys->p_dsbuffer, &status );
    if( hr != DS_OK )
        return hr;
    if( !(status & DSBSTATUS_PLAYING) )
        return DSERR_INVALIDCALL ;

    hr = IDirectSoundBuffer_GetCurrentPosition( sys->p_dsbuffer, &read, NULL );
    if( hr != DS_OK )
        return hr;

    size = (ssize_t)read - sys->i_last_read;

    /* GetCurrentPosition cannot be trusted if the return doesn't change
     * Just return an error */
    if( size ==  0 )
        return DSERR_GENERIC ;
    else if( size < 0 )
      size += DS_BUF_SIZE;

    sys->i_data -= size;
    sys->i_last_read = read;

    if( sys->i_data < 0 )
        /* underrun */
        Flush(sys);

    *delay = vlc_tick_from_samples( sys->i_data / sys->i_bytes_per_sample, sys->i_rate );

    return DS_OK;
}