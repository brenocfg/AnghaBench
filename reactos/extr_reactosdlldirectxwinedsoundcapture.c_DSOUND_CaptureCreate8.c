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
typedef  int /*<<< orphan*/  REFIID ;
typedef  scalar_t__ LPDIRECTSOUNDCAPTURE8 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DS_OK ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ IDirectSoundCaptureImpl_Create (scalar_t__*) ; 
 int /*<<< orphan*/  IDirectSoundCapture_AddRef (scalar_t__) ; 
 int /*<<< orphan*/  IID_IDirectSoundCapture8 ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_dsound_options () ; 

HRESULT DSOUND_CaptureCreate8(
    REFIID riid,
    LPDIRECTSOUNDCAPTURE8 *ppDSC8)
{
    LPDIRECTSOUNDCAPTURE8 pDSC8;
    HRESULT hr;
    TRACE("(%s, %p)\n", debugstr_guid(riid), ppDSC8);

    if (!IsEqualIID(riid, &IID_IUnknown) &&
        !IsEqualIID(riid, &IID_IDirectSoundCapture8)) {
        *ppDSC8 = 0;
        return E_NOINTERFACE;
    }

    /* Get dsound configuration */
    setup_dsound_options();

    hr = IDirectSoundCaptureImpl_Create(&pDSC8);
    if (hr == DS_OK) {
        IDirectSoundCapture_AddRef(pDSC8);
        *ppDSC8 = pDSC8;
    } else {
        WARN("IDirectSoundCaptureImpl_Create failed\n");
        *ppDSC8 = 0;
    }

    return hr;
}