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
typedef  int /*<<< orphan*/  dscaps ;
struct TYPE_4__ {int dwSize; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUND8 ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDirectSound8 ;
typedef  int /*<<< orphan*/  IDirectSound ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ DSCAPS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DSERR_ALLOCATED ; 
 scalar_t__ DSERR_ALREADYINITIALIZED ; 
 scalar_t__ DSERR_INVALIDPARAM ; 
 scalar_t__ DSERR_NODRIVER ; 
 scalar_t__ DSERR_PRIOLEVELNEEDED ; 
 scalar_t__ DSERR_UNINITIALIZED ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 scalar_t__ DSSPEAKER_COMBINED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSSPEAKER_GEOMETRY_NARROW ; 
 int /*<<< orphan*/  DSSPEAKER_GEOMETRY_WIDE ; 
 int /*<<< orphan*/  DSSPEAKER_STEREO ; 
 scalar_t__ DS_OK ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ FALSE ; 
 scalar_t__ IDirectSound8_Compact (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound8_GetCaps (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ IDirectSound8_GetSpeakerConfig (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IDirectSound8_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSound8_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IDirectSound8_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDirectSound8_SetCooperativeLevel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSound8_SetSpeakerConfig (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ IDirectSound8_VerifyCertification (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IDirectSound_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirectSound ; 
 int /*<<< orphan*/  IID_IDirectSound8 ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void IDirectSound8_test(LPDIRECTSOUND8 dso, BOOL initialized,
                               LPCGUID lpGuid)
{
    HRESULT rc;
    DSCAPS dscaps;
    int ref;
    IUnknown * unknown;
    IDirectSound * ds;
    IDirectSound8 * ds8;
    DWORD speaker_config, new_speaker_config, ref_speaker_config;
    DWORD certified;

    /* Try to Query for objects */
    rc=IDirectSound8_QueryInterface(dso,&IID_IUnknown,(LPVOID*)&unknown);
    ok(rc==DS_OK,"IDirectSound8_QueryInterface(IID_IUnknown) failed: %08x\n", rc);
    if (rc==DS_OK)
        IDirectSound8_Release(unknown);

    rc=IDirectSound8_QueryInterface(dso,&IID_IDirectSound,(LPVOID*)&ds);
    ok(rc==DS_OK,"IDirectSound8_QueryInterface(IID_IDirectSound) failed: %08x\n", rc);
    if (rc==DS_OK)
        IDirectSound_Release(ds);

    rc=IDirectSound8_QueryInterface(dso,&IID_IDirectSound8,(LPVOID*)&ds8);
    ok(rc==DS_OK,"IDirectSound8_QueryInterface(IID_IDirectSound8) "
       "should have returned DSERR_INVALIDPARAM, returned: %08x\n", rc);
    if (rc==DS_OK)
        IDirectSound8_Release(ds8);

    if (initialized == FALSE) {
        /* try uninitialized object */
        rc=IDirectSound8_GetCaps(dso,0);
        ok(rc==DSERR_UNINITIALIZED,"IDirectSound8_GetCaps(NULL) "
           "should have returned DSERR_UNINITIALIZED, returned: %08x\n", rc);

        rc=IDirectSound8_GetCaps(dso,&dscaps);
        ok(rc==DSERR_UNINITIALIZED,"IDirectSound8_GetCaps() "
           "should have returned DSERR_UNINITIALIZED, returned: %08x\n", rc);

        rc=IDirectSound8_Compact(dso);
        ok(rc==DSERR_UNINITIALIZED,"IDirectSound8_Compact() "
           "should have returned DSERR_UNINITIALIZED, returned: %08x\n", rc);

        rc=IDirectSound8_GetSpeakerConfig(dso,&speaker_config);
        ok(rc==DSERR_UNINITIALIZED,"IDirectSound8_GetSpeakerConfig() "
           "should have returned DSERR_UNINITIALIZED, returned: %08x\n", rc);

        rc=IDirectSound8_VerifyCertification(dso, &certified);
        ok(rc==DSERR_UNINITIALIZED,"IDirectSound8_VerifyCertification() "
           "should have returned DSERR_UNINITIALIZED, returned: %08x\n", rc);

        rc=IDirectSound8_Initialize(dso,lpGuid);
        ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL,
           "IDirectSound8_Initialize() failed: %08x\n",rc);
        if (rc==DSERR_NODRIVER) {
            trace("  No Driver\n");
            goto EXIT;
        } else if (rc==E_FAIL) {
            trace("  No Device\n");
            goto EXIT;
        } else if (rc==DSERR_ALLOCATED) {
            trace("  Already In Use\n");
            goto EXIT;
        }
    }

    rc=IDirectSound8_Initialize(dso,lpGuid);
    ok(rc==DSERR_ALREADYINITIALIZED, "IDirectSound8_Initialize() "
       "should have returned DSERR_ALREADYINITIALIZED: %08x\n", rc);

    /* DSOUND: Error: Invalid caps buffer */
    rc=IDirectSound8_GetCaps(dso,0);
    ok(rc==DSERR_INVALIDPARAM,"IDirectSound8_GetCaps() "
       "should have returned DSERR_INVALIDPARAM, returned: %08x\n", rc);

    ZeroMemory(&dscaps, sizeof(dscaps));

    /* DSOUND: Error: Invalid caps buffer */
    rc=IDirectSound8_GetCaps(dso,&dscaps);
    ok(rc==DSERR_INVALIDPARAM,"IDirectSound8_GetCaps() "
       "should have returned DSERR_INVALIDPARAM, returned: %08x\n", rc);

    dscaps.dwSize=sizeof(dscaps);

    /* DSOUND: Running on a certified driver */
    rc=IDirectSound8_GetCaps(dso,&dscaps);
    ok(rc==DS_OK,"IDirectSound8_GetCaps() failed: %08x\n",rc);

    rc=IDirectSound8_Compact(dso);
    ok(rc==DSERR_PRIOLEVELNEEDED,"IDirectSound8_Compact() failed: %08x\n", rc);

    rc=IDirectSound8_SetCooperativeLevel(dso,get_hwnd(),DSSCL_PRIORITY);
    ok(rc==DS_OK,"IDirectSound8_SetCooperativeLevel() failed: %08x\n", rc);

    rc=IDirectSound8_Compact(dso);
    ok(rc==DS_OK,"IDirectSound8_Compact() failed: %08x\n",rc);

    rc=IDirectSound8_GetSpeakerConfig(dso,0);
    ok(rc==DSERR_INVALIDPARAM,"IDirectSound8_GetSpeakerConfig(NULL) "
       "should have returned DSERR_INVALIDPARAM, returned: %08x\n", rc);

    rc=IDirectSound8_GetSpeakerConfig(dso,&speaker_config);
    ok(rc==DS_OK,"IDirectSound8_GetSpeakerConfig() failed: %08x\n", rc);
    ref_speaker_config = speaker_config;

    speaker_config = DSSPEAKER_COMBINED(DSSPEAKER_STEREO,
                                        DSSPEAKER_GEOMETRY_WIDE);
    if (speaker_config == ref_speaker_config)
        speaker_config = DSSPEAKER_COMBINED(DSSPEAKER_STEREO,
                                            DSSPEAKER_GEOMETRY_NARROW);
    if(rc==DS_OK) {
        rc=IDirectSound8_SetSpeakerConfig(dso,speaker_config);
        ok(rc==DS_OK,"IDirectSound8_SetSpeakerConfig() failed: %08x\n", rc);
    }
    if (rc==DS_OK) {
        rc=IDirectSound8_GetSpeakerConfig(dso,&new_speaker_config);
        ok(rc==DS_OK,"IDirectSound8_GetSpeakerConfig() failed: %08x\n", rc);
        if (rc==DS_OK && speaker_config!=new_speaker_config)
               trace("IDirectSound8_GetSpeakerConfig() failed to set speaker "
               "config: expected 0x%08x, got 0x%08x\n",
               speaker_config,new_speaker_config);
        IDirectSound8_SetSpeakerConfig(dso,ref_speaker_config);
    }

    rc=IDirectSound8_VerifyCertification(dso, &certified);
    ok(rc==DS_OK||rc==E_NOTIMPL,"IDirectSound8_VerifyCertification() failed: %08x\n", rc);

EXIT:
    ref=IDirectSound8_Release(dso);
    ok(ref==0,"IDirectSound8_Release() has %d references, should have 0\n",ref);
}