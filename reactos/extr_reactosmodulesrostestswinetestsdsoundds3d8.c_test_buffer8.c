#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wfx ;
struct TYPE_24__ {int /*<<< orphan*/  wave; scalar_t__ buffer_size; scalar_t__ offset; scalar_t__ written; scalar_t__ played; TYPE_5__* wfx; int /*<<< orphan*/ * dsbo; int /*<<< orphan*/  wave_len; } ;
typedef  TYPE_3__ play_state_t ;
typedef  int /*<<< orphan*/  new_dsbcaps ;
typedef  int /*<<< orphan*/  listener_param ;
typedef  int /*<<< orphan*/  dsbcaps ;
typedef  int /*<<< orphan*/  buffer_param ;
struct TYPE_26__ {int nSamplesPerSec; scalar_t__ wBitsPerSample; scalar_t__ nChannels; int /*<<< orphan*/  nBlockAlign; int /*<<< orphan*/  nAvgBytesPerSec; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_25__ {int /*<<< orphan*/  SubFormat; TYPE_5__ Format; } ;
typedef  TYPE_4__ WAVEFORMATEXTENSIBLE ;
typedef  TYPE_5__ WAVEFORMATEX ;
struct TYPE_23__ {float x; int /*<<< orphan*/  z; int /*<<< orphan*/  y; } ;
struct TYPE_22__ {float x; } ;
struct TYPE_27__ {int dwSize; int dwFlags; int flMinDistance; TYPE_2__ vPosition; TYPE_1__ vVelocity; scalar_t__ dwBufferBytes; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDBUFFER ;
typedef  int /*<<< orphan*/  LPDIRECTSOUND8 ;
typedef  scalar_t__ LPDIRECTSOUND3DLISTENER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND3DBUFFER ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int HRESULT ;
typedef  int DWORD ;
typedef  TYPE_6__ DSBCAPS ;
typedef  TYPE_6__ DS3DLISTENER ;
typedef  TYPE_6__ DS3DBUFFER ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DS3D_IMMEDIATE ; 
 int DSBCAPS_CTRLFREQUENCY ; 
 int DSBCAPS_CTRLPAN ; 
 int DSBCAPS_CTRLVOLUME ; 
 int /*<<< orphan*/  DSBLOCK_ENTIREBUFFER ; 
 int /*<<< orphan*/  DSBLOCK_FROMWRITECURSOR ; 
 int /*<<< orphan*/  DSBPLAY_LOOPING ; 
 int DSBSTATUS_LOOPING ; 
 int DSBSTATUS_PLAYING ; 
 int DSERR_CONTROLUNAVAIL ; 
 int DSERR_INVALIDPARAM ; 
 int /*<<< orphan*/  DSSCL_NORMAL ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 int /*<<< orphan*/  DSSCL_WRITEPRIMARY ; 
 int DS_OK ; 
 int FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetTickCount () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDirectSound3DBuffer_GetAllParameters (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int IDirectSound3DBuffer_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirectSound3DBuffer_Release (int /*<<< orphan*/ *) ; 
 int IDirectSound3DBuffer_SetAllParameters (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int IDirectSound3DBuffer_SetPosition (int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDirectSound3DListener_GetAllParameters (scalar_t__,TYPE_6__*) ; 
 int IDirectSound3DListener_SetAllParameters (scalar_t__,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int IDirectSound3DListener_SetPosition (scalar_t__,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDirectSound8_SetCooperativeLevel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDirectSoundBuffer_GetCaps (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int IDirectSoundBuffer_GetFormat (int /*<<< orphan*/ *,TYPE_5__*,int,int*) ; 
 int IDirectSoundBuffer_GetFrequency (int /*<<< orphan*/ *,int*) ; 
 int IDirectSoundBuffer_GetPan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_GetStatus (int /*<<< orphan*/ *,int*) ; 
 int IDirectSoundBuffer_GetVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_Lock (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IDirectSoundBuffer_Play (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDirectSoundBuffer_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_SetFormat (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int IDirectSoundBuffer_SetPan (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IDirectSoundBuffer_SetVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDirectSound3DBuffer ; 
 int /*<<< orphan*/  IID_IDirectSoundBuffer ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 int /*<<< orphan*/  TIME_SLICE ; 
 int /*<<< orphan*/  WAVE_FORMAT_IEEE_FLOAT ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_6__*,int) ; 
 int /*<<< orphan*/  buffer_refill8 (TYPE_3__*,scalar_t__) ; 
 scalar_t__ buffer_service8 (TYPE_3__*) ; 
 int fabs (int) ; 
 int /*<<< orphan*/  format_string (TYPE_5__*) ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  init_format (TYPE_5__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 int /*<<< orphan*/  wave_generate_la (TYPE_5__*,double,int /*<<< orphan*/ *,int) ; 
 int winetest_debug ; 
 scalar_t__ winetest_interactive ; 

void test_buffer8(LPDIRECTSOUND8 dso, LPDIRECTSOUNDBUFFER * dsbo,
                  BOOL is_primary, BOOL set_volume, LONG volume,
                  BOOL set_pan, LONG pan, BOOL play, double duration,
                  BOOL buffer3d, LPDIRECTSOUND3DLISTENER listener,
                  BOOL move_listener, BOOL move_sound)
{
    HRESULT rc;
    DSBCAPS dsbcaps;
    WAVEFORMATEX wfx,wfx2;
    DWORD size,status,freq;
    BOOL ieee = FALSE;
    int ref;

    /* DSOUND: Error: Invalid caps pointer */
    rc=IDirectSoundBuffer_GetCaps(*dsbo,0);
    ok(rc==DSERR_INVALIDPARAM,"IDirectSoundBuffer_GetCaps() should have "
       "returned DSERR_INVALIDPARAM, returned: %08x\n",rc);

    ZeroMemory(&dsbcaps, sizeof(dsbcaps));

    /* DSOUND: Error: Invalid caps pointer */
    rc=IDirectSoundBuffer_GetCaps(*dsbo,&dsbcaps);
    ok(rc==DSERR_INVALIDPARAM,"IDirectSoundBuffer_GetCaps() should have "
       "returned DSERR_INVALIDPARAM, returned: %08x\n",rc);

    dsbcaps.dwSize=sizeof(dsbcaps);
    rc=IDirectSoundBuffer_GetCaps(*dsbo,&dsbcaps);
    ok(rc==DS_OK,"IDirectSoundBuffer_GetCaps() failed: %08x\n", rc);
    if (rc==DS_OK && winetest_debug > 1) {
        trace("    Caps: flags=0x%08x size=%d\n",dsbcaps.dwFlags,
              dsbcaps.dwBufferBytes);
    }

    /* Query the format size. */
    size=0;
    rc=IDirectSoundBuffer_GetFormat(*dsbo,NULL,0,&size);
    ok(rc==DS_OK && size!=0,"IDirectSoundBuffer_GetFormat() should have "
       "returned the needed size: rc=%08x size=%d\n",rc,size);

    ok(size == sizeof(WAVEFORMATEX) || size == sizeof(WAVEFORMATEXTENSIBLE),
       "Expected a correct structure size, got %d\n", size);

    if (size == sizeof(WAVEFORMATEX)) {
        rc=IDirectSoundBuffer_GetFormat(*dsbo,&wfx,size,NULL);
        ieee = (wfx.wFormatTag == WAVE_FORMAT_IEEE_FLOAT);
    } else if (size == sizeof(WAVEFORMATEXTENSIBLE)) {
        WAVEFORMATEXTENSIBLE wfxe;
        rc=IDirectSoundBuffer_GetFormat(*dsbo,(WAVEFORMATEX*)&wfxe,size,NULL);
        wfx = wfxe.Format;
        ieee = IsEqualGUID(&wfxe.SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT);
    } else
        return;

    ok(rc==DS_OK,"IDirectSoundBuffer_GetFormat() failed: %08x\n", rc);
    if (rc==DS_OK && winetest_debug > 1) {
        trace("    Format: %s tag=0x%04x %dx%dx%d avg.B/s=%d align=%d\n",
              is_primary ? "Primary" : "Secondary",
              wfx.wFormatTag,wfx.nSamplesPerSec,wfx.wBitsPerSample,
              wfx.nChannels,wfx.nAvgBytesPerSec,wfx.nBlockAlign);
    }

    /* DSOUND: Error: Invalid frequency buffer */
    rc=IDirectSoundBuffer_GetFrequency(*dsbo,0);
    ok(rc==DSERR_INVALIDPARAM,"IDirectSoundBuffer_GetFrequency() should have "
       "returned DSERR_INVALIDPARAM, returned: %08x\n",rc);

    /* DSOUND: Error: Primary buffers don't support CTRLFREQUENCY */
    rc=IDirectSoundBuffer_GetFrequency(*dsbo,&freq);
    ok((rc==DS_OK && !is_primary) || (rc==DSERR_CONTROLUNAVAIL&&is_primary) ||
       (rc==DSERR_CONTROLUNAVAIL&&!(dsbcaps.dwFlags&DSBCAPS_CTRLFREQUENCY)),
       "IDirectSoundBuffer_GetFrequency() failed: %08x\n",rc);
    if (rc==DS_OK) {
        ok(freq==wfx.nSamplesPerSec,"The frequency returned by GetFrequency "
           "%d does not match the format %d\n",freq,wfx.nSamplesPerSec);
    }

    /* DSOUND: Error: Invalid status pointer */
    rc=IDirectSoundBuffer_GetStatus(*dsbo,0);
    ok(rc==DSERR_INVALIDPARAM,"IDirectSoundBuffer_GetStatus() should have "
       "returned DSERR_INVALIDPARAM, returned: %08x\n",rc);

    rc=IDirectSoundBuffer_GetStatus(*dsbo,&status);
    ok(rc==DS_OK,"IDirectSoundBuffer_GetStatus() failed: %08x\n", rc);
    ok(status==0,"status=0x%x instead of 0\n",status);

    if (is_primary) {
        DSBCAPS new_dsbcaps;
        /* We must call SetCooperativeLevel to be allowed to call SetFormat */
        /* DSOUND: Setting DirectSound cooperative level to DSSCL_PRIORITY */
        rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),DSSCL_PRIORITY);
        ok(rc==DS_OK,"IDirectSound8_SetCooperativeLevel(DSSCL_PRIORITY) "
           "failed: %08x\n",rc);
        if (rc!=DS_OK)
            return;

        /* DSOUND: Error: Invalid format pointer */
        rc=IDirectSoundBuffer_SetFormat(*dsbo,0);
        ok(rc==DSERR_INVALIDPARAM,"IDirectSoundBuffer_SetFormat() should have "
           "returned DSERR_INVALIDPARAM, returned: %08x\n",rc);

        init_format(&wfx2,WAVE_FORMAT_PCM,11025,16,2);
        rc=IDirectSoundBuffer_SetFormat(*dsbo,&wfx2);
        ok(rc==DS_OK,"IDirectSoundBuffer_SetFormat(%s) failed: %08x\n",
           format_string(&wfx2), rc);

        /* There is no guarantee that SetFormat will actually change the
	 * format to what we asked for. It depends on what the soundcard
	 * supports. So we must re-query the format.
	 */
        rc=IDirectSoundBuffer_GetFormat(*dsbo,&wfx,sizeof(wfx),NULL);
        ok(rc==DS_OK,"IDirectSoundBuffer_GetFormat() failed: %08x\n", rc);
        if (rc==DS_OK &&
            (wfx.wFormatTag!=wfx2.wFormatTag ||
             wfx.nSamplesPerSec!=wfx2.nSamplesPerSec ||
             wfx.wBitsPerSample!=wfx2.wBitsPerSample ||
             wfx.nChannels!=wfx2.nChannels)) {
            trace("Requested format tag=0x%04x %dx%dx%d avg.B/s=%d align=%d\n",
                  wfx2.wFormatTag,wfx2.nSamplesPerSec,wfx2.wBitsPerSample,
                  wfx2.nChannels,wfx2.nAvgBytesPerSec,wfx2.nBlockAlign);
            trace("Got tag=0x%04x %dx%dx%d avg.B/s=%d align=%d\n",
                  wfx.wFormatTag,wfx.nSamplesPerSec,wfx.wBitsPerSample,
                  wfx.nChannels,wfx.nAvgBytesPerSec,wfx.nBlockAlign);
        }

        ZeroMemory(&new_dsbcaps, sizeof(new_dsbcaps));
        new_dsbcaps.dwSize = sizeof(new_dsbcaps);
        rc=IDirectSoundBuffer_GetCaps(*dsbo,&new_dsbcaps);
        ok(rc==DS_OK,"IDirectSoundBuffer_GetCaps() failed: %08x\n", rc);
        if (rc==DS_OK && winetest_debug > 1) {
            trace("    new Caps: flags=0x%08x size=%d\n",new_dsbcaps.dwFlags,
                  new_dsbcaps.dwBufferBytes);
        }

        /* Check for primary buffer size change */
        ok(new_dsbcaps.dwBufferBytes == dsbcaps.dwBufferBytes,
           "    buffer size changed after SetFormat() - "
           "previous size was %u, current size is %u\n",
           dsbcaps.dwBufferBytes, new_dsbcaps.dwBufferBytes);
        dsbcaps.dwBufferBytes = new_dsbcaps.dwBufferBytes;

        /* Check for primary buffer flags change */
        ok(new_dsbcaps.dwFlags == dsbcaps.dwFlags,
           "    flags changed after SetFormat() - "
           "previous flags were %08x, current flags are %08x\n",
           dsbcaps.dwFlags, new_dsbcaps.dwFlags);

        /* Set the CooperativeLevel back to normal */
        /* DSOUND: Setting DirectSound cooperative level to DSSCL_NORMAL */
        rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),DSSCL_NORMAL);
        ok(rc==DS_OK,"IDirectSound8_SetCooperativeLevel(DSSCL_NORMAL) "
           "failed: %08x\n",rc);
    }

    if (play) {
        play_state_t state;
        DS3DLISTENER listener_param;
        LPDIRECTSOUND3DBUFFER buffer=NULL;
        DS3DBUFFER buffer_param;
        DWORD start_time,now;
        LPVOID buffer1;
        DWORD length1;

        if (winetest_interactive) {
            trace("    Playing %g second 440Hz tone at %dx%dx%d\n", duration,
                  wfx.nSamplesPerSec, wfx.wBitsPerSample,wfx.nChannels);
        }

        if (is_primary) {
            /* We must call SetCooperativeLevel to be allowed to call Lock */
            /* DSOUND: Setting DirectSound cooperative level to
             * DSSCL_WRITEPRIMARY */
            rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),
                                                 DSSCL_WRITEPRIMARY);
            ok(rc==DS_OK,
               "IDirectSound8_SetCooperativeLevel(DSSCL_WRITEPRIMARY) failed: %08x\n",rc);
            if (rc!=DS_OK)
                return;
        }
        if (buffer3d) {
            LPDIRECTSOUNDBUFFER temp_buffer;

            rc=IDirectSoundBuffer_QueryInterface(*dsbo,&IID_IDirectSound3DBuffer,
                                                 (LPVOID *)&buffer);
            ok(rc==DS_OK,"IDirectSoundBuffer_QueryInterface() failed: %08x\n", rc);
            if (rc!=DS_OK)
                return;

            /* check the COM interface */
            rc=IDirectSoundBuffer_QueryInterface(*dsbo, &IID_IDirectSoundBuffer,
                                                 (LPVOID *)&temp_buffer);
            ok(rc==DS_OK && temp_buffer!=NULL,
               "IDirectSoundBuffer_QueryInterface() failed: %08x\n", rc);
            ok(temp_buffer==*dsbo,"COM interface broken: %p != %p\n",
               temp_buffer,*dsbo);
            ref=IDirectSoundBuffer_Release(temp_buffer);
            ok(ref==1,"IDirectSoundBuffer_Release() has %d references, "
               "should have 1\n",ref);

            temp_buffer=NULL;
            rc=IDirectSound3DBuffer_QueryInterface(*dsbo, &IID_IDirectSoundBuffer,
                                                   (LPVOID *)&temp_buffer);
            ok(rc==DS_OK && temp_buffer!=NULL,
               "IDirectSound3DBuffer_QueryInterface() failed: %08x\n", rc);
            ok(temp_buffer==*dsbo,"COM interface broken: %p != %p\n",
               temp_buffer,*dsbo);
            ref=IDirectSoundBuffer_Release(temp_buffer);
            ok(ref==1,"IDirectSoundBuffer_Release() has %d references, "
               "should have 1\n",ref);

            ref=IDirectSoundBuffer_Release(*dsbo);
            ok(ref==0,"IDirectSoundBuffer_Release() has %d references, "
               "should have 0\n",ref);

            rc=IDirectSound3DBuffer_QueryInterface(buffer,
                                                   &IID_IDirectSoundBuffer,
                                                   (LPVOID *)dsbo);
            ok(rc==DS_OK && *dsbo!=NULL,"IDirectSound3DBuffer_QueryInterface() "
               "failed: %08x\n",rc);

            /* DSOUND: Error: Invalid buffer */
            rc=IDirectSound3DBuffer_GetAllParameters(buffer,0);
            ok(rc==DSERR_INVALIDPARAM,"IDirectSound3DBuffer_GetAllParameters() "
               "failed: %08x\n",rc);

            ZeroMemory(&buffer_param, sizeof(buffer_param));

            /* DSOUND: Error: Invalid buffer */
            rc=IDirectSound3DBuffer_GetAllParameters(buffer,&buffer_param);
            ok(rc==DSERR_INVALIDPARAM,"IDirectSound3DBuffer_GetAllParameters() "
               "failed: %08x\n",rc);

            buffer_param.dwSize=sizeof(buffer_param);
            rc=IDirectSound3DBuffer_GetAllParameters(buffer,&buffer_param);
            ok(rc==DS_OK,"IDirectSound3DBuffer_GetAllParameters() failed: %08x\n", rc);
        }
        if (set_volume) {
            if (dsbcaps.dwFlags & DSBCAPS_CTRLVOLUME) {
                LONG val;
                rc=IDirectSoundBuffer_GetVolume(*dsbo,&val);
                ok(rc==DS_OK,"IDirectSoundBuffer_GetVolume() failed: %08x\n", rc);

                rc=IDirectSoundBuffer_SetVolume(*dsbo,volume);
                ok(rc==DS_OK,"IDirectSoundBuffer_SetVolume() failed: %08x\n", rc);
            } else {
                /* DSOUND: Error: Buffer does not have CTRLVOLUME */
                rc=IDirectSoundBuffer_GetVolume(*dsbo,&volume);
                ok(rc==DSERR_CONTROLUNAVAIL,"IDirectSoundBuffer_GetVolume() "
                   "should have returned DSERR_CONTROLUNAVAIL, returned: %08x\n", rc);
            }
        }

        if (set_pan) {
            if (dsbcaps.dwFlags & DSBCAPS_CTRLPAN) {
                LONG val;
                rc=IDirectSoundBuffer_GetPan(*dsbo,&val);
                ok(rc==DS_OK,"IDirectSoundBuffer_GetPan() failed: %08x\n", rc);

                rc=IDirectSoundBuffer_SetPan(*dsbo,pan);
                ok(rc==DS_OK,"IDirectSoundBuffer_SetPan() failed: %08x\n", rc);
            } else {
                /* DSOUND: Error: Buffer does not have CTRLPAN */
                rc=IDirectSoundBuffer_GetPan(*dsbo,&pan);
                ok(rc==DSERR_CONTROLUNAVAIL,"IDirectSoundBuffer_GetPan() "
                   "should have returned DSERR_CONTROLUNAVAIL, returned: %08x\n", rc);
            }
        }

        /* try an offset past the end of the buffer */
        rc = IDirectSoundBuffer_Lock(*dsbo, dsbcaps.dwBufferBytes, 0, &buffer1,
                                      &length1, NULL, NULL,
                                      DSBLOCK_ENTIREBUFFER);
        ok(rc==DSERR_INVALIDPARAM, "IDirectSoundBuffer_Lock() should have "
           "returned DSERR_INVALIDPARAM, returned %08x\n", rc);

        /* try a size larger than the buffer */
        rc = IDirectSoundBuffer_Lock(*dsbo, 0, dsbcaps.dwBufferBytes + 1,
                                     &buffer1, &length1, NULL, NULL,
                                     DSBLOCK_FROMWRITECURSOR);
        ok(rc==DSERR_INVALIDPARAM, "IDirectSoundBuffer_Lock() should have "
           "returned DSERR_INVALIDPARAM, returned %08x\n", rc);

        state.wave=wave_generate_la(&wfx,duration,&state.wave_len,ieee);

        state.dsbo=*dsbo;
        state.wfx=&wfx;
        state.buffer_size=dsbcaps.dwBufferBytes;
        state.played=state.written=state.offset=0;
        buffer_refill8(&state,state.buffer_size);

        rc=IDirectSoundBuffer_Play(*dsbo,0,0,DSBPLAY_LOOPING);
        ok(rc==DS_OK,"IDirectSoundBuffer_Play() failed: %08x\n", rc);

        rc=IDirectSoundBuffer_GetStatus(*dsbo,&status);
        ok(rc==DS_OK,"IDirectSoundBuffer_GetStatus() failed: %08x\n", rc);
        ok(status==(DSBSTATUS_PLAYING|DSBSTATUS_LOOPING),
           "GetStatus: bad status: %x\n",status);

        if (listener) {
            ZeroMemory(&listener_param,sizeof(listener_param));
            listener_param.dwSize=sizeof(listener_param);
            rc=IDirectSound3DListener_GetAllParameters(listener,&listener_param);
            ok(rc==DS_OK,"IDirectSound3dListener_GetAllParameters() "
               "failed: %08x\n",rc);
            if (move_listener) {
                listener_param.vPosition.x = -5.0f;
                listener_param.vVelocity.x = (float)(10.0/duration);
            }
            rc=IDirectSound3DListener_SetAllParameters(listener,
                                                       &listener_param,
                                                       DS3D_IMMEDIATE);
            ok(rc==DS_OK,"IDirectSound3dListener_SetPosition() failed: %08x\n", rc);
        }
        if (buffer3d) {
            if (move_sound) {
                buffer_param.vPosition.x = 100.0f;
                buffer_param.vVelocity.x = (float)(-200.0/duration);
            }
            buffer_param.flMinDistance = 10;
            rc=IDirectSound3DBuffer_SetAllParameters(buffer,&buffer_param,
                                                     DS3D_IMMEDIATE);
            ok(rc==DS_OK,"IDirectSound3dBuffer_SetPosition() failed: %08x\n", rc);
        }

        start_time=GetTickCount();
        while (buffer_service8(&state)) {
            WaitForSingleObject(GetCurrentProcess(),TIME_SLICE);
            now=GetTickCount();
            if (listener && move_listener) {
                listener_param.vPosition.x = (float)(-5.0+10.0*(now-start_time)/1000/duration);
                if (winetest_debug>2)
                    trace("listener position=%g\n",listener_param.vPosition.x);
                rc=IDirectSound3DListener_SetPosition(listener,
                    listener_param.vPosition.x,listener_param.vPosition.y,
                    listener_param.vPosition.z,DS3D_IMMEDIATE);
                ok(rc==DS_OK,"IDirectSound3dListener_SetPosition() failed: %08x\n",rc);
            }
            if (buffer3d && move_sound) {
                buffer_param.vPosition.x = (float)(100-200.0*(now-start_time)/1000/duration);
                if (winetest_debug>2)
                    trace("sound position=%g\n",buffer_param.vPosition.x);
                rc=IDirectSound3DBuffer_SetPosition(buffer,
                    buffer_param.vPosition.x,buffer_param.vPosition.y,
                    buffer_param.vPosition.z,DS3D_IMMEDIATE);
                ok(rc==DS_OK,"IDirectSound3dBuffer_SetPosition() failed: %08x\n", rc);
            }
        }
        /* Check the sound duration was within 10% of the expected value */
        now=GetTickCount();
        ok(fabs(1000*duration-now+start_time)<=100*duration,
           "The sound played for %d ms instead of %g ms\n",
           now-start_time,1000*duration);

        HeapFree(GetProcessHeap(), 0, state.wave);
        if (is_primary) {
            /* Set the CooperativeLevel back to normal */
            /* DSOUND: Setting DirectSound cooperative level to DSSCL_NORMAL */
            rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),DSSCL_NORMAL);
            ok(rc==DS_OK,"IDirectSound8_SetCooperativeLevel(DSSCL_NORMAL) "
               "failed: %08x\n",rc);
        }
        if (buffer3d) {
            ref=IDirectSound3DBuffer_Release(buffer);
            ok(ref==0,"IDirectSound3DBuffer_Release() has %d references, "
               "should have 0\n",ref);
        }
    }
}