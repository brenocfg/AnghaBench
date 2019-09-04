#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wfex ;
struct TYPE_7__ {int nChannels; int nSamplesPerSec; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; int dwSize; int dwBufferBytes; struct TYPE_7__* lpwfxFormat; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  wFormatTag; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDFULLDUPLEX ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDCAPTUREBUFFER8 ;
typedef  int /*<<< orphan*/  LPDIRECTSOUNDBUFFER8 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DSCBufferDesc ;
typedef  TYPE_1__ DSCBUFFERDESC ;
typedef  int /*<<< orphan*/  DSBufferDesc ;
typedef  TYPE_1__ DSBUFFERDESC ;

/* Variables and functions */
 scalar_t__ CLASS_E_CLASSNOTAVAILABLE ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DirectSoundFullDuplex ; 
 int /*<<< orphan*/  CLSID_DirectSoundPrivate ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  DSBCAPS_GLOBALFOCUS ; 
 int /*<<< orphan*/  DSCBCAPS_WAVEMAPPED ; 
 int /*<<< orphan*/  DSDEVID_DefaultCapture ; 
 int /*<<< orphan*/  DSDEVID_DefaultPlayback ; 
 int /*<<< orphan*/  DSDEVID_DefaultVoiceCapture ; 
 int /*<<< orphan*/  DSDEVID_DefaultVoicePlayback ; 
 scalar_t__ DSERR_ALLOCATED ; 
 scalar_t__ DSERR_INVALIDCALL ; 
 scalar_t__ DSERR_NODRIVER ; 
 int /*<<< orphan*/  DSSCL_EXCLUSIVE ; 
 scalar_t__ DS_OK ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDirectSoundFullDuplex_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundFullDuplex_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirectSoundFullDuplex ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pDirectSoundFullDuplexCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void IDirectSoundFullDuplex_tests(void)
{
    HRESULT rc;
    LPDIRECTSOUNDFULLDUPLEX dsfdo = NULL;
    DSCBUFFERDESC DSCBufferDesc;
    DSBUFFERDESC DSBufferDesc;
    LPDIRECTSOUNDCAPTUREBUFFER8 pDSCBuffer8;
    LPDIRECTSOUNDBUFFER8 pDSBuffer8;
    WAVEFORMATEX wfex;

    trace("Testing IDirectSoundFullDuplex\n");

    /* try the COM class factory method of creation with no devices specified */
    rc=CoCreateInstance(&CLSID_DirectSoundFullDuplex, NULL,
                        CLSCTX_INPROC_SERVER, &IID_IDirectSoundFullDuplex,
                        (void**)&dsfdo);
    ok(rc==S_OK||rc==REGDB_E_CLASSNOTREG||rc==CLASS_E_CLASSNOTAVAILABLE,
       "CoCreateInstance(CLSID_DirectSoundFullDuplex) failed: 0x%08x\n", rc);
    if (rc==REGDB_E_CLASSNOTREG) {
        trace("  Class Not Registered\n");
        return;
    } else if (rc==CLASS_E_CLASSNOTAVAILABLE) {
        trace("  Class Not Available\n");
        return;
    }
    if (dsfdo)
        IDirectSoundFullDuplex_test(dsfdo, FALSE, NULL, NULL);

    /* try the COM class factory method of creation with default devices
     * specified */
    rc=CoCreateInstance(&CLSID_DirectSoundFullDuplex, NULL,
                        CLSCTX_INPROC_SERVER, &IID_IDirectSoundFullDuplex,
                        (void**)&dsfdo);
    ok(rc==S_OK,"CoCreateInstance(CLSID_DirectSoundFullDuplex) failed: 0x%08x\n", rc);
    if (dsfdo)
        IDirectSoundFullDuplex_test(dsfdo, FALSE, &DSDEVID_DefaultCapture,
                                    &DSDEVID_DefaultPlayback);

    /* try the COM class factory method of creation with default voice
     * devices specified */
    rc=CoCreateInstance(&CLSID_DirectSoundFullDuplex, NULL,
                        CLSCTX_INPROC_SERVER, &IID_IDirectSoundFullDuplex,
                        (void**)&dsfdo);
    ok(rc==S_OK,"CoCreateInstance(CLSID_DirectSoundFullDuplex) failed: 0x%08x\n", rc);
    if (dsfdo)
        IDirectSoundFullDuplex_test(dsfdo, FALSE, &DSDEVID_DefaultVoiceCapture,
                                    &DSDEVID_DefaultVoicePlayback);

    /* try the COM class factory method of creation with a bad
     * IID specified */
    rc=CoCreateInstance(&CLSID_DirectSoundFullDuplex, NULL,
                        CLSCTX_INPROC_SERVER, &CLSID_DirectSoundPrivate,
                        (void**)&dsfdo);
    ok(rc==E_NOINTERFACE,
       "CoCreateInstance(CLSID_DirectSoundFullDuplex,CLSID_DirectSoundPrivate) "
       "should have failed: 0x%08x\n", rc);

    ZeroMemory(&wfex, sizeof(wfex));
    wfex.wFormatTag = WAVE_FORMAT_PCM;
    wfex.nChannels = 1;
    wfex.nSamplesPerSec = 8000;
    wfex.wBitsPerSample = 16;
    wfex.nBlockAlign = (wfex.wBitsPerSample * wfex.nChannels) / 8;
    wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;

    ZeroMemory(&DSCBufferDesc, sizeof(DSCBufferDesc));
    DSCBufferDesc.dwSize = sizeof(DSCBufferDesc);
    DSCBufferDesc.dwFlags = DSCBCAPS_WAVEMAPPED;
    DSCBufferDesc.dwBufferBytes = 8192;
    DSCBufferDesc.lpwfxFormat = &wfex;

    ZeroMemory(&DSBufferDesc, sizeof(DSBufferDesc));
    DSBufferDesc.dwSize = sizeof(DSBufferDesc);
    DSBufferDesc.dwFlags = DSBCAPS_GLOBALFOCUS;
    DSBufferDesc.dwBufferBytes = 8192;
    DSBufferDesc.lpwfxFormat = &wfex;

    /* try with no device specified */
    rc=pDirectSoundFullDuplexCreate(NULL,NULL,&DSCBufferDesc,&DSBufferDesc,
                                    get_hwnd(),DSSCL_EXCLUSIVE ,&dsfdo,&pDSCBuffer8,
                                    &pDSBuffer8,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL||rc==DSERR_INVALIDCALL,
       "DirectSoundFullDuplexCreate(NULL,NULL) failed: %08x\n",rc);
    if (rc==S_OK && dsfdo)
        IDirectSoundFullDuplex_test(dsfdo, TRUE, NULL, NULL);

    /* try with default devices specified */
    rc=pDirectSoundFullDuplexCreate(&DSDEVID_DefaultCapture,
                                    &DSDEVID_DefaultPlayback,&DSCBufferDesc,
                                    &DSBufferDesc,get_hwnd(),DSSCL_EXCLUSIVE,&dsfdo,
                                    &pDSCBuffer8,&pDSBuffer8,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL||rc==DSERR_INVALIDCALL,
       "DirectSoundFullDuplexCreate(DSDEVID_DefaultCapture,"
       "DSDEVID_DefaultPlayback) failed: %08x\n", rc);
    if (rc==DS_OK && dsfdo)
        IDirectSoundFullDuplex_test(dsfdo, TRUE, NULL, NULL);

    /* try with default voice devices specified */
    rc=pDirectSoundFullDuplexCreate(&DSDEVID_DefaultVoiceCapture,
                                    &DSDEVID_DefaultVoicePlayback,
                                    &DSCBufferDesc,&DSBufferDesc,get_hwnd(),DSSCL_EXCLUSIVE,
                                    &dsfdo,&pDSCBuffer8,&pDSBuffer8,NULL);
    ok(rc==DS_OK||rc==DSERR_NODRIVER||rc==DSERR_ALLOCATED||rc==E_FAIL||rc==DSERR_INVALIDCALL,
       "DirectSoundFullDuplexCreate(DSDEVID_DefaultVoiceCapture,"
       "DSDEVID_DefaultVoicePlayback) failed: %08x\n", rc);
    if (rc==DS_OK && dsfdo)
        IDirectSoundFullDuplex_test(dsfdo, TRUE, NULL, NULL);

    /* try with bad devices specified */
    rc=pDirectSoundFullDuplexCreate(&DSDEVID_DefaultVoicePlayback,
                                    &DSDEVID_DefaultVoiceCapture,
                                    &DSCBufferDesc,&DSBufferDesc,get_hwnd(),DSSCL_EXCLUSIVE,
                                    &dsfdo,&pDSCBuffer8,&pDSBuffer8,NULL);
    ok(rc==DSERR_NODRIVER||rc==DSERR_INVALIDCALL,
       "DirectSoundFullDuplexCreate(DSDEVID_DefaultVoicePlayback,"
       "DSDEVID_DefaultVoiceCapture) should have failed: %08x\n", rc);
    if (rc==DS_OK && dsfdo)
        IDirectSoundFullDuplex_Release(dsfdo);
}