#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bufdesc ;
struct TYPE_6__ {int nAvgBytesPerSec; int /*<<< orphan*/  nBlockAlign; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
struct TYPE_7__ {int dwSize; int dwFlags; TYPE_1__* lpwfxFormat; int /*<<< orphan*/  dwBufferBytes; } ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDBUFFER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND3DBUFFER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND ;
typedef  int HRESULT ;
typedef  TYPE_2__ DSBUFFERDESC ;

/* Variables and functions */
 int BUFFER_LEN ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DirectSound ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int DSBCAPS_CTRL3D ; 
 int DSBCAPS_GETCURRENTPOSITION2 ; 
 int DSERR_ALLOCATED ; 
 int DSERR_CONTROLUNAVAIL ; 
 int DSERR_GENERIC ; 
 int DSERR_INVALIDPARAM ; 
 int DSERR_NODRIVER ; 
 int DS_OK ; 
 int E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int IDirectSound3DBuffer_AddRef (int /*<<< orphan*/ *) ; 
 int IDirectSoundBuffer_AddRef (int /*<<< orphan*/ *) ; 
 int IDirectSound_CreateSoundBuffer (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int IDirectSound_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IDirectSound_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDirectSound ; 
 int /*<<< orphan*/  IID_IDirectSound3DBuffer ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  align (int,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  init_format (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pDirectSoundCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT test_dsound(LPGUID lpGuid)
{
    HRESULT rc;
    LPDIRECTSOUND dso=NULL;
    int ref;

    /* DSOUND: Error: Invalid interface buffer */
    rc=pDirectSoundCreate(lpGuid,0,NULL);
    ok(rc==DSERR_INVALIDPARAM,"DirectSoundCreate() should have returned "
       "DSERR_INVALIDPARAM, returned: %08x\n",rc);

    /* Create the DirectSound object */
    rc=pDirectSoundCreate(lpGuid,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL,
       "DirectSoundCreate() failed: %08x\n",rc);
    if (rc!=DS_OK)
        return rc;

    /* Try the enumerated device */
    IDirectSound_test(dso, TRUE, lpGuid);

    /* Try the COM class factory method of creation with enumerated device */
    rc=CoCreateInstance(&CLSID_DirectSound, NULL, CLSCTX_INPROC_SERVER,
                        &IID_IDirectSound, (void**)&dso);
    ok(rc==S_OK,"CoCreateInstance(CLSID_DirectSound) failed: %08x\n", rc);
    if (dso)
        IDirectSound_test(dso, FALSE, lpGuid);

    /* Create a DirectSound object */
    rc=pDirectSoundCreate(lpGuid,&dso,NULL);
    ok(rc==DS_OK,"DirectSoundCreate() failed: %08x\n",rc);
    if (rc==DS_OK) {
        LPDIRECTSOUND dso1=NULL;

        /* Create a second DirectSound object */
        rc=pDirectSoundCreate(lpGuid,&dso1,NULL);
        ok(rc==DS_OK,"DirectSoundCreate() failed: %08x\n",rc);
        if (rc==DS_OK) {
            /* Release the second DirectSound object */
            ref=IDirectSound_Release(dso1);
            ok(ref==0,"IDirectSound_Release() has %d references, should have "
               "0\n",ref);
            ok(dso!=dso1,"DirectSound objects should be unique: dso=%p,dso1=%p\n",dso,dso1);
        }

        /* Release the first DirectSound object */
        ref=IDirectSound_Release(dso);
        ok(ref==0,"IDirectSound_Release() has %d references, should have 0\n",
           ref);
        if (ref!=0)
            return DSERR_GENERIC;
    } else
        return rc;

    /* Create a DirectSound object */
    rc=pDirectSoundCreate(lpGuid,&dso,NULL);
    ok(rc==DS_OK,"DirectSoundCreate() failed: %08x\n",rc);
    if (rc==DS_OK) {
        LPDIRECTSOUNDBUFFER secondary;
        DSBUFFERDESC bufdesc;
        WAVEFORMATEX wfx;

        init_format(&wfx,WAVE_FORMAT_PCM,11025,8,1);
        ZeroMemory(&bufdesc, sizeof(bufdesc));
        bufdesc.dwSize=sizeof(bufdesc);
        bufdesc.dwFlags=DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRL3D;
        bufdesc.dwBufferBytes=align(wfx.nAvgBytesPerSec*BUFFER_LEN/1000,
                                    wfx.nBlockAlign);
        bufdesc.lpwfxFormat=&wfx;
        rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&secondary,NULL);
        ok((rc==DS_OK && secondary!=NULL) || broken(rc == DSERR_CONTROLUNAVAIL), /* vmware drivers on w2k */
           "IDirectSound_CreateSoundBuffer() failed to create a secondary "
           "buffer %08x\n",rc);
        if (rc==DS_OK && secondary!=NULL) {
            LPDIRECTSOUND3DBUFFER buffer3d;
            rc=IDirectSound_QueryInterface(secondary, &IID_IDirectSound3DBuffer,
                                           (void **)&buffer3d);
            ok(rc==DS_OK && buffer3d!=NULL,"IDirectSound_QueryInterface() "
               "failed: %08x\n",rc);
            if (rc==DS_OK && buffer3d!=NULL) {
                ref=IDirectSound3DBuffer_AddRef(buffer3d);
                ok(ref==2,"IDirectSound3DBuffer_AddRef() has %d references, "
                   "should have 2\n",ref);
            }
            ref=IDirectSoundBuffer_AddRef(secondary);
            ok(ref==2,"IDirectSoundBuffer_AddRef() has %d references, "
               "should have 2\n",ref);
        }
        /* release with buffer */
        ref=IDirectSound_Release(dso);
        ok(ref==0,"IDirectSound_Release() has %d references, should have 0\n",
           ref);
        if (ref!=0)
            return DSERR_GENERIC;
    } else
        return rc;

    return DS_OK;
}