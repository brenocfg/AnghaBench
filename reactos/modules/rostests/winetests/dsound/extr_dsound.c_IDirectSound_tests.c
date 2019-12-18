#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * LPCLASSFACTORY ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDirectSound ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DirectSound ; 
 int /*<<< orphan*/  CLSID_DirectSoundPrivate ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CoGetClassObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  DSDEVID_DefaultPlayback ; 
 int /*<<< orphan*/  DSDEVID_DefaultVoiceCapture ; 
 int /*<<< orphan*/  DSDEVID_DefaultVoicePlayback ; 
 scalar_t__ DSERR_ALLOCATED ; 
 scalar_t__ DSERR_INVALIDPARAM ; 
 scalar_t__ DSERR_NODRIVER ; 
 scalar_t__ DS_OK ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirectSound_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IClassFactory ; 
 int /*<<< orphan*/  IID_IDirectSound ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pDirectSoundCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void IDirectSound_tests(void)
{
    HRESULT rc;
    IDirectSound *dso=(IDirectSound*)0xdeadbeef;
    LPCLASSFACTORY cf=NULL;

    trace("Testing IDirectSound\n");

    rc=CoGetClassObject(&CLSID_DirectSound, CLSCTX_INPROC_SERVER, NULL,
                        &IID_IClassFactory, (void**)&cf);
    ok(rc==S_OK,"CoGetClassObject(CLSID_DirectSound, IID_IClassFactory) "
       "failed: %08x\n", rc);

    rc=CoGetClassObject(&CLSID_DirectSound, CLSCTX_INPROC_SERVER, NULL,
                        &IID_IUnknown, (void**)&cf);
    ok(rc==S_OK,"CoGetClassObject(CLSID_DirectSound, IID_IUnknown) "
       "failed: %08x\n", rc);

    /* COM aggregation */
    rc=CoCreateInstance(&CLSID_DirectSound, (IUnknown*)&dso, CLSCTX_INPROC_SERVER,
                        &IID_IDirectSound, (void**)&dso);
    ok(rc==CLASS_E_NOAGGREGATION || broken(rc==DSERR_INVALIDPARAM),
       "DirectMusicPerformance create failed: %08x, expected CLASS_E_NOAGGREGATION\n", rc);

    /* try the COM class factory method of creation with no device specified */
    rc=CoCreateInstance(&CLSID_DirectSound, NULL, CLSCTX_INPROC_SERVER,
                        &IID_IDirectSound, (void**)&dso);
    ok(rc==S_OK,"CoCreateInstance(CLSID_DirectSound) failed: %08x\n", rc);
    if (dso)
        IDirectSound_test(dso, FALSE, NULL);

    /* try the COM class factory method of creation with default playback
     * device specified */
    rc=CoCreateInstance(&CLSID_DirectSound, NULL, CLSCTX_INPROC_SERVER,
                        &IID_IDirectSound, (void**)&dso);
    ok(rc==S_OK,"CoCreateInstance(CLSID_DirectSound) failed: %08x\n", rc);
    if (dso)
        IDirectSound_test(dso, FALSE, &DSDEVID_DefaultPlayback);

    /* try the COM class factory method of creation with default voice
     * playback device specified */
    rc=CoCreateInstance(&CLSID_DirectSound, NULL, CLSCTX_INPROC_SERVER,
                        &IID_IDirectSound, (void**)&dso);
    ok(rc==S_OK,"CoCreateInstance(CLSID_DirectSound) failed: %08x\n", rc);
    if (dso)
        IDirectSound_test(dso, FALSE, &DSDEVID_DefaultVoicePlayback);

    /* try the COM class factory method of creation with a bad
     * IID specified */
    rc=CoCreateInstance(&CLSID_DirectSound, NULL, CLSCTX_INPROC_SERVER,
                        &CLSID_DirectSoundPrivate, (void**)&dso);
    ok(rc==E_NOINTERFACE,
       "CoCreateInstance(CLSID_DirectSound,CLSID_DirectSoundPrivate) "
       "should have failed: %08x\n",rc);

    /* try the COM class factory method of creation with a bad
     * GUID and IID specified */
    rc=CoCreateInstance(&CLSID_DirectSoundPrivate, NULL, CLSCTX_INPROC_SERVER,
                        &IID_IDirectSound, (void**)&dso);
    ok(rc==REGDB_E_CLASSNOTREG,
       "CoCreateInstance(CLSID_DirectSoundPrivate,IID_IDirectSound) "
       "should have failed: %08x\n",rc);

    /* try with no device specified */
    rc=pDirectSoundCreate(NULL,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL,
       "DirectSoundCreate(NULL) failed: %08x\n",rc);
    if (rc==S_OK && dso)
        IDirectSound_test(dso, TRUE, NULL);

    /* try with default playback device specified */
    rc=pDirectSoundCreate(&DSDEVID_DefaultPlayback,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL,
       "DirectSoundCreate(DSDEVID_DefaultPlayback) failed: %08x\n", rc);
    if (rc==DS_OK && dso)
        IDirectSound_test(dso, TRUE, NULL);

    /* try with default voice playback device specified */
    rc=pDirectSoundCreate(&DSDEVID_DefaultVoicePlayback,&dso,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL,
       "DirectSoundCreate(DSDEVID_DefaultVoicePlayback) failed: %08x\n", rc);
    if (rc==DS_OK && dso)
        IDirectSound_test(dso, TRUE, NULL);

    /* try with a bad device specified */
    rc=pDirectSoundCreate(&DSDEVID_DefaultVoiceCapture,&dso,NULL);
    ok(rc==DSERR_NODRIVER,"DirectSoundCreate(DSDEVID_DefaultVoiceCapture) "
       "should have failed: %08x\n",rc);
    if (rc==DS_OK && dso)
        IDirectSound_Release(dso);
}