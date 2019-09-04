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
typedef  int /*<<< orphan*/  LPGUID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDBUFFER ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND ;
typedef  int LONG ;
typedef  int HRESULT ;
typedef  TYPE_1__ DSCAPS ;
typedef  TYPE_1__ DSBUFFERDESC ;

/* Variables and functions */
 int DSBCAPS_CTRLPAN ; 
 int DSBCAPS_CTRLVOLUME ; 
 int DSBCAPS_PRIMARYBUFFER ; 
 int DSBPAN_LEFT ; 
 int DSBPAN_RIGHT ; 
 int DSBVOLUME_MAX ; 
 int DSBVOLUME_MIN ; 
 int DSCAPS_EMULDRIVER ; 
 int DSERR_CONTROLUNAVAIL ; 
 int DSERR_GENERIC ; 
 int DSERR_NODRIVER ; 
 int /*<<< orphan*/  DSSCL_NORMAL ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 int DS_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 int IDirectSound_CreateSoundBuffer (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int IDirectSound_GetCaps (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int IDirectSound_Release (int /*<<< orphan*/ *) ; 
 int IDirectSound_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pDirectSoundCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static HRESULT test_primary(LPGUID lpGuid)
{
    HRESULT rc;
    LPDIRECTSOUND dso=NULL;
    LPDIRECTSOUNDBUFFER primary=NULL;
    DSBUFFERDESC bufdesc;
    DSCAPS dscaps;
    int ref, i;

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

    /* Testing the primary buffer */
    primary=NULL;
    ZeroMemory(&bufdesc, sizeof(bufdesc));
    bufdesc.dwSize=sizeof(bufdesc);
    bufdesc.dwFlags=DSBCAPS_PRIMARYBUFFER|DSBCAPS_CTRLVOLUME|DSBCAPS_CTRLPAN;
    rc=IDirectSound_CreateSoundBuffer(dso,&bufdesc,&primary,NULL);
    ok((rc==DS_OK && primary!=NULL) || (rc==DSERR_CONTROLUNAVAIL),
       "IDirectSound_CreateSoundBuffer() failed to create a primary buffer: %08x\n",rc);
    if (rc==DSERR_CONTROLUNAVAIL)
        trace("  No Primary\n");
    else if (rc==DS_OK && primary!=NULL) {
        test_buffer(dso,&primary,1,TRUE,0,TRUE,0,winetest_interactive &&
                    !(dscaps.dwFlags & DSCAPS_EMULDRIVER),1.0,0,NULL,0,0,
                    FALSE,0);
        if (winetest_interactive) {
            LONG volume,pan;

            volume = DSBVOLUME_MAX;
            for (i = 0; i < 6; i++) {
                test_buffer(dso,&primary,1,TRUE,volume,TRUE,0,
                            winetest_interactive &&
                            !(dscaps.dwFlags & DSCAPS_EMULDRIVER),
                            1.0,0,NULL,0,0,FALSE,0);
                volume -= ((DSBVOLUME_MAX-DSBVOLUME_MIN) / 40);
            }

            pan = DSBPAN_LEFT;
            for (i = 0; i < 7; i++) {
                test_buffer(dso,&primary,1,TRUE,0,TRUE,pan,
                            winetest_interactive &&
                            !(dscaps.dwFlags & DSCAPS_EMULDRIVER),1.0,0,0,0,0,FALSE,0);
                pan += ((DSBPAN_RIGHT-DSBPAN_LEFT) / 6);
            }
        }
        ref=IDirectSoundBuffer_Release(primary);
        ok(ref==0,"IDirectSoundBuffer_Release() primary has %d references, "
           "should have 0\n",ref);
    }

    /* Set the CooperativeLevel back to normal */
    /* DSOUND: Setting DirectSound cooperative level to DSSCL_NORMAL */
    rc=IDirectSound_SetCooperativeLevel(dso,get_hwnd(),DSSCL_NORMAL);
    ok(rc==DS_OK,"IDirectSound_SetCooperativeLevel(DSSCL_NORMAL) failed: %08x\n", rc);

EXIT:
    ref=IDirectSound_Release(dso);
    ok(ref==0,"IDirectSound_Release() has %d references, should have 0\n",ref);
    if (ref!=0)
        return DSERR_GENERIC;

    return rc;
}