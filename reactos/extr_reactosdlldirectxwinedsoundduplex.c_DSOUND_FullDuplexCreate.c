#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ref; int /*<<< orphan*/ * renderer_device; int /*<<< orphan*/ * capture_device; int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDFULLDUPLEX ;
typedef  TYPE_1__ IDirectSoundFullDuplexImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_INVALIDPARAM ; 
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IID_IDirectSoundFullDuplex ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsfdvt ; 
 int /*<<< orphan*/  setup_dsound_options () ; 

HRESULT DSOUND_FullDuplexCreate(
    REFIID riid,
    LPDIRECTSOUNDFULLDUPLEX* ppDSFD)
{
    IDirectSoundFullDuplexImpl *This = NULL;
    TRACE("(%s, %p)\n", debugstr_guid(riid), ppDSFD);

    if (ppDSFD == NULL) {
        WARN("invalid parameter: ppDSFD == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (!IsEqualIID(riid, &IID_IUnknown) &&
        !IsEqualIID(riid, &IID_IDirectSoundFullDuplex)) {
        *ppDSFD = 0;
        return E_NOINTERFACE;
    }

    /* Get dsound configuration */
    setup_dsound_options();

    This = HeapAlloc(GetProcessHeap(),
        HEAP_ZERO_MEMORY, sizeof(IDirectSoundFullDuplexImpl));

    if (This == NULL) {
        WARN("out of memory\n");
        *ppDSFD = NULL;
        return DSERR_OUTOFMEMORY;
    }

    This->lpVtbl = &dsfdvt;
    This->ref = 1;
    This->capture_device = NULL;
    This->renderer_device = NULL;

    *ppDSFD = (LPDIRECTSOUNDFULLDUPLEX)This;

    return DS_OK;
}