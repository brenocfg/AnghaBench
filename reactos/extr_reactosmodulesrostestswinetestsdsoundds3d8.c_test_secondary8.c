#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wfx1 ;
typedef  int /*<<< orphan*/  listener_param ;
typedef  int /*<<< orphan*/  bufdesc ;
struct TYPE_9__ {int nAvgBytesPerSec; int /*<<< orphan*/  nChannels; int /*<<< orphan*/  wBitsPerSample; int /*<<< orphan*/  nSamplesPerSec; int /*<<< orphan*/  nBlockAlign; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
struct TYPE_10__ {int dwSize; int dwFlags; TYPE_1__* lpwfxFormat; int /*<<< orphan*/  dwBufferBytes; } ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDBUFFER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND8 ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND3DLISTENER ;
typedef  int LONG ;
typedef  int HRESULT ;
typedef  TYPE_2__ DSBUFFERDESC ;
typedef  TYPE_2__ DS3DLISTENER ;

/* Variables and functions */
 int BUFFER_LEN ; 
 int DSBCAPS_CTRL3D ; 
 int DSBCAPS_CTRLFREQUENCY ; 
 int DSBCAPS_CTRLPAN ; 
 int DSBCAPS_CTRLVOLUME ; 
 int DSBCAPS_GETCURRENTPOSITION2 ; 
 int DSBCAPS_PRIMARYBUFFER ; 
 int DSERR_CONTROLUNAVAIL ; 
 int DSERR_GENERIC ; 
 int DSERR_INVALIDPARAM ; 
 int DSERR_NODRIVER ; 
 int /*<<< orphan*/  DSSCL_NORMAL ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 int DS_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int IDirectSound3DListener_GetAllParameters (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int IDirectSound3DListener_Release (int /*<<< orphan*/ *) ; 
 int IDirectSound8_CreateSoundBuffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int IDirectSound8_DuplicateSoundBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IDirectSound8_Release (int /*<<< orphan*/ *) ; 
 int IDirectSound8_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IDirectSoundBuffer_GetFormat (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_GetPan (int /*<<< orphan*/ *,int*) ; 
 int IDirectSoundBuffer_GetVolume (int /*<<< orphan*/ *,int*) ; 
 int IDirectSoundBuffer_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_SetPan (int /*<<< orphan*/ *,int) ; 
 int IDirectSoundBuffer_SetVolume (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IID_IDirectSound3DListener ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  align (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getDSBCAPS (int) ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  init_format (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pDirectSoundCreate8 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_buffer8 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,double,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static HRESULT test_secondary8(LPGUID lpGuid, int play,
                               int has_3d, int has_3dbuffer,
                               int has_listener, int has_duplicate,
                               int move_listener, int move_sound)
{
    HRESULT rc;
    LPDIRECTSOUND8 dso=NULL;
    LPDIRECTSOUNDBUFFER primary=NULL,secondary=NULL;
    LPDIRECTSOUND3DLISTENER listener=NULL;
    DSBUFFERDESC bufdesc;
    WAVEFORMATEX wfx, wfx1;
    int ref;

    /* Create the DirectSound object */
    rc=pDirectSoundCreate8(lpGuid,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER,"DirectSoundCreate8() failed: %08x\n", rc);
    if (rc!=DS_OK)
        return rc;

    /* We must call SetCooperativeLevel before creating primary buffer */
    /* DSOUND: Setting DirectSound cooperative level to DSSCL_PRIORITY */
    rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),DSSCL_PRIORITY);
    ok(rc==DS_OK,"IDirectSound8_SetCooperativeLevel(DSSCL_PRIORITY) failed: %08x\n",rc);
    if (rc!=DS_OK)
        goto EXIT;

    ZeroMemory(&bufdesc, sizeof(bufdesc));
    bufdesc.dwSize=sizeof(bufdesc);
    bufdesc.dwFlags=DSBCAPS_PRIMARYBUFFER;
    if (has_3d)
        bufdesc.dwFlags|=DSBCAPS_CTRL3D;
    else
        bufdesc.dwFlags|=(DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLPAN);
    rc=IDirectSound8_CreateSoundBuffer(dso,&bufdesc,&primary,NULL);
    ok((rc==DS_OK && primary!=NULL) || (rc == DSERR_CONTROLUNAVAIL),
       "IDirectSound8_CreateSoundBuffer() failed to create a %sprimary buffer: %08x\n",has_3d?"3D ":"", rc);
    if (rc == DSERR_CONTROLUNAVAIL)
        trace("  No Primary\n");
    else if (rc==DS_OK && primary!=NULL) {
        rc=IDirectSoundBuffer_GetFormat(primary,&wfx1,sizeof(wfx1),NULL);
        ok(rc==DS_OK,"IDirectSoundBuffer8_Getformat() failed: %08x\n", rc);
        if (rc!=DS_OK)
            goto EXIT1;

        if (has_listener) {
            rc=IDirectSoundBuffer_QueryInterface(primary,
                                                 &IID_IDirectSound3DListener,
                                                 (void **)&listener);
            ok(rc==DS_OK && listener!=NULL,
               "IDirectSoundBuffer_QueryInterface() failed to get a 3D "
               "listener %08x\n",rc);
            ref=IDirectSoundBuffer_Release(primary);
            ok(ref==0,"IDirectSoundBuffer_Release() primary has %d references, "
               "should have 0\n",ref);
            if (rc==DS_OK && listener!=NULL) {
                DS3DLISTENER listener_param;
                ZeroMemory(&listener_param,sizeof(listener_param));
                /* DSOUND: Error: Invalid buffer */
                rc=IDirectSound3DListener_GetAllParameters(listener,0);
                ok(rc==DSERR_INVALIDPARAM,
                   "IDirectSound3dListener_GetAllParameters() should have "
                   "returned DSERR_INVALIDPARAM, returned: %08x\n", rc);

                /* DSOUND: Error: Invalid buffer */
                rc=IDirectSound3DListener_GetAllParameters(listener,
                                                           &listener_param);
                ok(rc==DSERR_INVALIDPARAM,
                   "IDirectSound3dListener_GetAllParameters() should have "
                   "returned DSERR_INVALIDPARAM, returned: %08x\n", rc);

                listener_param.dwSize=sizeof(listener_param);
                rc=IDirectSound3DListener_GetAllParameters(listener,
                                                           &listener_param);
                ok(rc==DS_OK,"IDirectSound3dListener_GetAllParameters() "
                   "failed: %08x\n",rc);
            } else {
                ok(listener==NULL, "IDirectSoundBuffer_QueryInterface() "
                   "failed but returned a listener anyway\n");
                ok(rc!=DS_OK, "IDirectSoundBuffer_QueryInterface() succeeded "
                   "but returned a NULL listener\n");
                if (listener) {
                    ref=IDirectSound3DListener_Release(listener);
                    ok(ref==0,"IDirectSound3dListener_Release() listener has "
                       "%d references, should have 0\n",ref);
                }
                goto EXIT2;
            }
        }

        init_format(&wfx,WAVE_FORMAT_PCM,22050,16,2);
        secondary=NULL;
        ZeroMemory(&bufdesc, sizeof(bufdesc));
        bufdesc.dwSize=sizeof(bufdesc);
        bufdesc.dwFlags=DSBCAPS_GETCURRENTPOSITION2;
        if (has_3d)
            bufdesc.dwFlags|=DSBCAPS_CTRL3D;
        else
            bufdesc.dwFlags|=
                (DSBCAPS_CTRLFREQUENCY|DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLPAN);
        bufdesc.dwBufferBytes=align(wfx.nAvgBytesPerSec*BUFFER_LEN/1000,
                                    wfx.nBlockAlign);
        bufdesc.lpwfxFormat=&wfx;
        if (has_3d) {
            /* a stereo 3D buffer should fail */
            rc=IDirectSound8_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
            ok(rc==DSERR_INVALIDPARAM,
               "IDirectSound8_CreateSoundBuffer(secondary) should have "
               "returned DSERR_INVALIDPARAM, returned %08x\n", rc);
            if (secondary)
            {
                ref=IDirectSoundBuffer_Release(secondary);
                ok(ref==0,"IDirectSoundBuffer_Release() primary has %d references, should have 0\n",ref);
            }
            init_format(&wfx,WAVE_FORMAT_PCM,22050,16,1);
        }

        if (winetest_interactive) {
            trace("  Testing a %s%ssecondary buffer %s%s%s%sat %dx%dx%d "
                  "with a primary buffer at %dx%dx%d\n",
                  has_3dbuffer?"3D ":"",
                  has_duplicate?"duplicated ":"",
                  listener!=NULL||move_sound?"with ":"",
                  move_listener?"moving ":"",
                  listener!=NULL?"listener ":"",
                  listener&&move_sound?"and moving sound ":move_sound?
                  "moving sound ":"",
                  wfx.nSamplesPerSec,wfx.wBitsPerSample,wfx.nChannels,
                  wfx1.nSamplesPerSec,wfx1.wBitsPerSample,wfx1.nChannels);
        }
        rc=IDirectSound8_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
        ok(rc==DS_OK && secondary!=NULL,"IDirectSound8_CreateSoundBuffer() "
           "failed to create a %s%ssecondary buffer %s%s%s%sat %dx%dx%d (%s): %08x\n",
           has_3dbuffer?"3D ":"", has_duplicate?"duplicated ":"",
           listener!=NULL||move_sound?"with ":"", move_listener?"moving ":"",
           listener!=NULL?"listener ":"",
           listener&&move_sound?"and moving sound ":move_sound?
           "moving sound ":"",
           wfx.nSamplesPerSec,wfx.wBitsPerSample,wfx.nChannels,
           getDSBCAPS(bufdesc.dwFlags),rc);
        if (rc==DS_OK && secondary!=NULL) {
            if (!has_3d) {
                LONG refvol,vol,refpan,pan;

                /* Check the initial secondary buffer's volume and pan */
                rc=IDirectSoundBuffer_GetVolume(secondary,&vol);
                ok(rc==DS_OK,"IDirectSoundBuffer_GetVolume(secondary) failed: %08x\n",rc);
                ok(vol==0,"wrong volume for a new secondary buffer: %d\n",vol);
                rc=IDirectSoundBuffer_GetPan(secondary,&pan);
                ok(rc==DS_OK,"IDirectSoundBuffer_GetPan(secondary) failed: %08x\n",rc);
                ok(pan==0,"wrong pan for a new secondary buffer: %d\n",pan);

                /* Check that changing the secondary buffer's volume and pan
                 * does not impact the primary buffer's volume and pan
                 */
                rc=IDirectSoundBuffer_GetVolume(primary,&refvol);
                ok(rc==DS_OK,"IDirectSoundBuffer_GetVolume(primary) failed: %08x\n",rc);
                rc=IDirectSoundBuffer_GetPan(primary,&refpan);
                ok(rc==DS_OK,"IDirectSoundBuffer_GetPan(primary) failed: %08x\n",rc);

                rc=IDirectSoundBuffer_SetVolume(secondary,-1000);
                ok(rc==DS_OK,"IDirectSoundBuffer_SetVolume(secondary) failed: %08x\n",rc);
                rc=IDirectSoundBuffer_GetVolume(secondary,&vol);
                ok(rc==DS_OK,"IDirectSoundBuffer_SetVolume(secondary) failed: %08x\n",rc);
                ok(vol==-1000,"secondary: wrong volume %d instead of -1000\n",
                   vol);
                rc=IDirectSoundBuffer_SetPan(secondary,-1000);
                ok(rc==DS_OK,"IDirectSoundBuffer_SetPan(secondary) failed: %08x\n",rc);
                rc=IDirectSoundBuffer_GetPan(secondary,&pan);
                ok(rc==DS_OK,"IDirectSoundBuffer_GetPan(secondary) failed: %08x\n",rc);
                ok(pan==-1000,"secondary: wrong pan %d instead of -1000\n",
                   pan);

                rc=IDirectSoundBuffer_GetVolume(primary,&vol);
                ok(rc==DS_OK,"IDirectSoundBuffer_`GetVolume(primary) failed: i%08x\n",rc);
                ok(vol==refvol,"The primary volume changed from %d to %d\n",
                   refvol,vol);
                rc=IDirectSoundBuffer_GetPan(primary,&pan);
                ok(rc==DS_OK,"IDirectSoundBuffer_GetPan(primary) failed: %08x\n",rc);
                ok(pan==refpan,"The primary pan changed from %d to %d\n",
                   refpan,pan);

                rc=IDirectSoundBuffer_SetVolume(secondary,0);
                ok(rc==DS_OK,"IDirectSoundBuffer_SetVolume(secondary) failed: %08x\n",rc);
                rc=IDirectSoundBuffer_SetPan(secondary,0);
                ok(rc==DS_OK,"IDirectSoundBuffer_SetPan(secondary) failed: %08x\n",rc);
            }
            if (has_duplicate) {
                LPDIRECTSOUNDBUFFER duplicated=NULL;

                /* DSOUND: Error: Invalid source buffer */
                rc=IDirectSound8_DuplicateSoundBuffer(dso,0,0);
                ok(rc==DSERR_INVALIDPARAM,
                   "IDirectSound8_DuplicateSoundBuffer() should have returned "
                   "DSERR_INVALIDPARAM, returned: %08x\n",rc);

                /* DSOUND: Error: Invalid dest buffer */
                rc=IDirectSound8_DuplicateSoundBuffer(dso,secondary,0);
                ok(rc==DSERR_INVALIDPARAM,
                   "IDirectSound8_DuplicateSoundBuffer() should have returned "
                   "DSERR_INVALIDPARAM, returned: %08x\n",rc);

                /* DSOUND: Error: Invalid source buffer */
                rc=IDirectSound8_DuplicateSoundBuffer(dso,0,&duplicated);
                ok(rc==DSERR_INVALIDPARAM,
                   "IDirectSound8_DuplicateSoundBuffer() should have returned "
                   "DSERR_INVALIDPARAM, returned: %08x\n",rc);

                duplicated=NULL;
                rc=IDirectSound8_DuplicateSoundBuffer(dso,secondary,
                                                      &duplicated);
                ok(rc==DS_OK && duplicated!=NULL,
                   "IDirectSound8_DuplicateSoundBuffer() failed to duplicate "
                   "a secondary buffer: %08x\n",rc);

                if (rc==DS_OK && duplicated!=NULL) {
                    ref=IDirectSoundBuffer_Release(secondary);
                    ok(ref==0,"IDirectSoundBuffer_Release() secondary has %d "
                       "references, should have 0\n",ref);
                    secondary=duplicated;
                }
            }

            if (rc==DS_OK && secondary!=NULL) {
                double duration;
                duration=(move_listener || move_sound?4.0:1.0);
                test_buffer8(dso,&secondary,0,FALSE,0,FALSE,0,
                             winetest_interactive,duration,has_3dbuffer,
                             listener,move_listener,move_sound);
                ref=IDirectSoundBuffer_Release(secondary);
                ok(ref==0,"IDirectSoundBuffer_Release() %s has %d references, "
                   "should have 0\n",has_duplicate?"duplicated":"secondary",
                   ref);
            }
        }
EXIT1:
        if (has_listener) {
            if (listener) {
                ref=IDirectSound3DListener_Release(listener);
                ok(ref==0,"IDirectSound3dListener_Release() listener has %d "
                   "references, should have 0\n",ref);
            }
        } else {
            ref=IDirectSoundBuffer_Release(primary);
            ok(ref==0,"IDirectSoundBuffer_Release() primary has %d references, "
               "should have 0\n",ref);
        }
    } else {
        ok(primary==NULL,"IDirectSound8_CreateSoundBuffer(primary) failed "
           "but primary created anyway\n");
        ok(rc!=DS_OK,"IDirectSound8_CreateSoundBuffer(primary) succeeded "
           "but primary not created\n");
        if (primary) {
            ref=IDirectSoundBuffer_Release(primary);
            ok(ref==0,"IDirectSoundBuffer_Release() primary has %d references, "
               "should have 0\n",ref);
        }
    }
EXIT2:
    /* Set the CooperativeLevel back to normal */
    /* DSOUND: Setting DirectSound cooperative level to DSSCL_NORMAL */
    rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),DSSCL_NORMAL);
    ok(rc==DS_OK,"IDirectSound8_SetCooperativeLevel(DSSCL_NORMAL) failed: %08x\n",rc);

EXIT:
    ref=IDirectSound8_Release(dso);
    ok(ref==0,"IDirectSound8_Release() has %d references, should have 0\n",ref);
    if (ref!=0)
        return DSERR_GENERIC;

    return rc;
}