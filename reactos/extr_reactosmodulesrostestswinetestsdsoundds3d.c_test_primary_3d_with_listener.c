#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dscaps ;
typedef  int /*<<< orphan*/  bufdesc ;
struct TYPE_6__ {int dwSize; int dwFlags; } ;
typedef  void* LPVOID ;
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDBUFFER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND3DLISTENER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ DSCAPS ;
typedef  TYPE_1__ DSBUFFERDESC ;

/* Variables and functions */
 int DSBCAPS_CTRL3D ; 
 int DSBCAPS_PRIMARYBUFFER ; 
 int DSCAPS_EMULDRIVER ; 
 scalar_t__ DSERR_GENERIC ; 
 scalar_t__ DSERR_NODRIVER ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 scalar_t__ DS_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDirectSound3DListener_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IDirectSound3DListener_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSoundBuffer_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound_CreateSoundBuffer (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound_GetCaps (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int IDirectSound_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IDirectSound3DListener ; 
 int /*<<< orphan*/  IID_IDirectSoundBuffer ; 
 int /*<<< orphan*/  IID_IKsPropertySet ; 
 int /*<<< orphan*/  IKsPropertySet_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 scalar_t__ pDirectSoundCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static HRESULT test_primary_3d_with_listener(LPGUID lpGuid)
{
    HRESULT rc;
    LPDIRECTSOUND dso=NULL;
    LPDIRECTSOUNDBUFFER primary=NULL;
    DSBUFFERDESC bufdesc;
    DSCAPS dscaps;
    int ref;

    /* Create the DirectSound object */
    rc=pDirectSoundCreate(lpGuid,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER,"DirectSoundCreate() failed: %08x\n", rc);
    if (rc!=DS_OK)
        return rc;

    /* Get the device capabilities */
    ZeroMemory(&dscaps, sizeof(dscaps));
    dscaps.dwSize=sizeof(dscaps);
    rc=IDirectSound_GetCaps(dso,&dscaps);
    ok(rc==DS_OK,"IDirectSound_GetCaps() failed: %08x\n",rc);
    if (rc!=DS_OK)
        goto EXIT;

    /* We must call SetCooperativeLevel before calling CreateSoundBuffer */
    /* DSOUND: Setting DirectSound cooperative level to DSSCL_PRIORITY */
    rc=IDirectSound_SetCooperativeLevel(dso,get_hwnd(),DSSCL_PRIORITY);
    ok(rc==DS_OK,"IDirectSound_SetCooperativeLevel(DSSCL_PRIORITY) failed: %08x\n",rc);
    if (rc!=DS_OK)
        goto EXIT;
    primary=NULL;
    ZeroMemory(&bufdesc, sizeof(bufdesc));
    bufdesc.dwSize=sizeof(bufdesc);
    bufdesc.dwFlags=DSBCAPS_PRIMARYBUFFER|DSBCAPS_CTRL3D;
    rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&primary,NULL);
    ok(rc==DS_OK && primary!=NULL,"IDirectSound_CreateSoundBuffer() failed "
       "to create a 3D primary buffer: %08x\n",rc);
    if (rc==DS_OK && primary!=NULL) {
        LPDIRECTSOUND3DLISTENER listener=NULL;
        LPDIRECTSOUNDBUFFER temp_buffer=NULL;
        rc=IDirectSoundBuffer_QueryInterface(primary,
            &IID_IDirectSound3DListener,(void **)&listener);
        ok(rc==DS_OK && listener!=NULL,"IDirectSoundBuffer_QueryInterface() "
           "failed to get a 3D listener: %08x\n",rc);
        if (rc==DS_OK && listener!=NULL) {
            /* Checking the COM interface */
            rc=IDirectSoundBuffer_QueryInterface(primary,
                &IID_IDirectSoundBuffer,(LPVOID *)&temp_buffer);
            ok(rc==DS_OK && temp_buffer!=NULL,
               "IDirectSoundBuffer_QueryInterface() failed: %08x\n", rc);
            ok(temp_buffer==primary,
               "COM interface broken: %p != %p\n",
               temp_buffer,primary);
            if (rc==DS_OK && temp_buffer!=NULL) {
                ref=IDirectSoundBuffer_Release(temp_buffer);
                ok(ref==1,"IDirectSoundBuffer_Release() has %d references, "
                   "should have 1\n",ref);

                temp_buffer=NULL;
                rc=IDirectSound3DListener_QueryInterface(listener,
                    &IID_IDirectSoundBuffer,(LPVOID *)&temp_buffer);
                ok(rc==DS_OK && temp_buffer!=NULL,
                   "IDirectSoundBuffer_QueryInterface() failed: %08x\n", rc);
                ok(temp_buffer==primary,
                   "COM interface broken: %p != %p\n",
                   temp_buffer,primary);
                ref=IDirectSoundBuffer_Release(temp_buffer);
                ok(ref==1,"IDirectSoundBuffer_Release() has %d references, "
                   "should have 1\n",ref);

                /* Testing the buffer */
                test_buffer(dso,&primary,1,FALSE,0,FALSE,0,
                            winetest_interactive &&
                            !(dscaps.dwFlags & DSCAPS_EMULDRIVER),1.0,0,
                            listener,0,0,FALSE,0);

                temp_buffer = NULL;
                rc = IDirectSound3DListener_QueryInterface(listener, &IID_IKsPropertySet,
                        (void **)&temp_buffer);
                ok(rc==DS_OK && temp_buffer!=NULL,
                        "IDirectSound3DListener_QueryInterface didn't handle IKsPropertySet: ret = %08x\n", rc);
                if(temp_buffer)
                    IKsPropertySet_Release(temp_buffer);
            }

            /* Testing the reference counting */
            ref=IDirectSound3DListener_Release(listener);
            ok(ref==0,"IDirectSound3DListener_Release() listener has %d "
               "references, should have 0\n",ref);
        }

        temp_buffer = NULL;
        rc = IDirectSoundBuffer_QueryInterface(primary, &IID_IKsPropertySet, (void **)&temp_buffer);
        ok(rc==DS_OK && temp_buffer!=NULL,
                "IDirectSoundBuffer_QueryInterface didn't handle IKsPropertySet on primary buffer: ret = %08x\n", rc);
        if(temp_buffer)
            IKsPropertySet_Release(temp_buffer);

        /* Testing the reference counting */
        ref=IDirectSoundBuffer_Release(primary);
        ok(ref==0,"IDirectSoundBuffer_Release() primary has %d references, "
           "should have 0\n",ref);
    }

EXIT:
    ref=IDirectSound_Release(dso);
    ok(ref==0,"IDirectSound_Release() has %d references, should have 0\n",ref);
    if (ref!=0)
return DSERR_GENERIC;

    return rc;
}