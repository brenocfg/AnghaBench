#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsbcaps ;
typedef  int /*<<< orphan*/  bufdesc ;
struct TYPE_8__ {scalar_t__ nAvgBytesPerSec; int nBlockAlign; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
struct TYPE_9__ {int dwSize; scalar_t__ dwBufferBytes; TYPE_1__* lpwfxFormat; int /*<<< orphan*/  dwFlags; } ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDBUFFER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_2__ DSBUFFERDESC ;
typedef  TYPE_2__ DSBCAPS ;

/* Variables and functions */
 int /*<<< orphan*/  DSBCAPS_GETCURRENTPOSITION2 ; 
 scalar_t__ DSERR_ALLOCATED ; 
 scalar_t__ DSERR_CONTROLUNAVAIL ; 
 scalar_t__ DSERR_GENERIC ; 
 scalar_t__ DSERR_NODRIVER ; 
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer_GetCaps (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ IDirectSoundBuffer_GetCurrentPosition (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSoundBuffer_SetCurrentPosition (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IDirectSound_CreateSoundBuffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int IDirectSound_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  init_format (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 scalar_t__ pDirectSoundCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT test_block_align(LPGUID lpGuid)
{
    HRESULT rc;
    LPDIRECTSOUND dso=NULL;
    LPDIRECTSOUNDBUFFER secondary=NULL;
    DSBUFFERDESC bufdesc;
    DSBCAPS dsbcaps;
    WAVEFORMATEX wfx;
    DWORD pos, pos2;
    int ref;

    /* Create the DirectSound object */
    rc=pDirectSoundCreate(lpGuid,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED,
       "DirectSoundCreate() failed: %08x\n",rc);
    if (rc!=DS_OK)
        return rc;

    init_format(&wfx,WAVE_FORMAT_PCM,11025,16,2);
    ZeroMemory(&bufdesc, sizeof(bufdesc));
    bufdesc.dwSize=sizeof(bufdesc);
    bufdesc.dwFlags=DSBCAPS_GETCURRENTPOSITION2;
    bufdesc.dwBufferBytes=wfx.nAvgBytesPerSec + 1;
    bufdesc.lpwfxFormat=&wfx;
    rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
    ok(rc == DS_OK || broken(rc == DSERR_CONTROLUNAVAIL), /* vmware drivers on w2k */
       "IDirectSound_CreateSoundBuffer() should have returned DS_OK, returned: %08x\n", rc);

    if (rc==DS_OK && secondary!=NULL) {
        ZeroMemory(&dsbcaps, sizeof(dsbcaps));
        dsbcaps.dwSize = sizeof(dsbcaps);
        rc=IDirectSoundBuffer_GetCaps(secondary,&dsbcaps);
        ok(rc==DS_OK,"IDirectSoundBuffer_GetCaps() should have returned DS_OK, "
           "returned: %08x\n", rc);
        if (rc==DS_OK && wfx.nBlockAlign > 1)
        {
            ok(dsbcaps.dwBufferBytes==(wfx.nAvgBytesPerSec + wfx.nBlockAlign),
               "Buffer size not a multiple of nBlockAlign: requested %d, "
               "got %d, should be %d\n", bufdesc.dwBufferBytes,
               dsbcaps.dwBufferBytes, wfx.nAvgBytesPerSec + wfx.nBlockAlign);

            rc = IDirectSoundBuffer_SetCurrentPosition(secondary, 0);
            ok(rc == DS_OK, "Could not set position to 0: %08x\n", rc);
            rc = IDirectSoundBuffer_GetCurrentPosition(secondary, &pos, NULL);
            ok(rc == DS_OK, "Could not get position: %08x\n", rc);
            rc = IDirectSoundBuffer_SetCurrentPosition(secondary, 1);
            ok(rc == DS_OK, "Could not set position to 1: %08x\n", rc);
            rc = IDirectSoundBuffer_GetCurrentPosition(secondary, &pos2, NULL);
            ok(rc == DS_OK, "Could not get new position: %08x\n", rc);
            ok(pos == pos2, "Positions not the same! Old position: %d, new position: %d\n", pos, pos2);
        }
        ref=IDirectSoundBuffer_Release(secondary);
        ok(ref==0,"IDirectSoundBuffer_Release() secondary has %d references, "
           "should have 0\n",ref);
    }

    ref=IDirectSound_Release(dso);
    ok(ref==0,"IDirectSound_Release() has %d references, should have 0\n",ref);
    if (ref!=0)
        return DSERR_GENERIC;

    return rc;
}