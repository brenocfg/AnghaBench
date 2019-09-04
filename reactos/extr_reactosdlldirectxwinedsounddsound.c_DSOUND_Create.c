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
typedef  int /*<<< orphan*/  LPDIRECTSOUND8 ;
typedef  scalar_t__ LPDIRECTSOUND ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DS_OK ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IDirectSound8_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ IDirectSoundImpl_Create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound_IDirectSound_AddRef (scalar_t__) ; 
 scalar_t__ IDirectSound_IDirectSound_Create (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IID_IDirectSound ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_dsound_options () ; 

HRESULT DSOUND_Create(
    REFIID riid,
    LPDIRECTSOUND *ppDS)
{
    LPDIRECTSOUND8 pDS;
    HRESULT hr;
    TRACE("(%s, %p)\n", debugstr_guid(riid), ppDS);

    if (!IsEqualIID(riid, &IID_IUnknown) &&
        !IsEqualIID(riid, &IID_IDirectSound)) {
        *ppDS = 0;
        return E_NOINTERFACE;
    }

    /* Get dsound configuration */
    setup_dsound_options();

    hr = IDirectSoundImpl_Create(&pDS);
    if (hr == DS_OK) {
        hr = IDirectSound_IDirectSound_Create(pDS, ppDS);
        if (*ppDS)
            IDirectSound_IDirectSound_AddRef(*ppDS);
        else {
            WARN("IDirectSound_IDirectSound_Create failed\n");
            IDirectSound8_Release(pDS);
        }
    } else {
        WARN("IDirectSoundImpl_Create failed\n");
        *ppDS = 0;
    }

    return hr;
}