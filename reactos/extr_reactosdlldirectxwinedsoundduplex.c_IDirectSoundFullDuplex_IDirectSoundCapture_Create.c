#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * capture_device; } ;
struct TYPE_4__ {TYPE_2__* pdsfd; scalar_t__ ref; int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDFULLDUPLEX ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDCAPTURE8 ;
typedef  int /*<<< orphan*/ * LPDIRECTSOUNDCAPTURE ;
typedef  TYPE_1__ IDirectSoundFullDuplex_IDirectSoundCapture ;
typedef  TYPE_2__ IDirectSoundFullDuplexImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DSERR_INVALIDPARAM ; 
 int /*<<< orphan*/  DSERR_OUTOFMEMORY ; 
 int /*<<< orphan*/  DSERR_UNINITIALIZED ; 
 int /*<<< orphan*/  DS_OK ; 
 int /*<<< orphan*/  DirectSoundFullDuplex_DirectSoundCapture_Vtbl ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static HRESULT IDirectSoundFullDuplex_IDirectSoundCapture_Create(
    LPDIRECTSOUNDFULLDUPLEX pdsfd,
    LPDIRECTSOUNDCAPTURE8 * ppdsc8)
{
    IDirectSoundFullDuplex_IDirectSoundCapture * pdsfddsc;
    TRACE("(%p,%p)\n",pdsfd,ppdsc8);

    if (pdsfd == NULL) {
        ERR("invalid parameter: pdsfd == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (ppdsc8 == NULL) {
        ERR("invalid parameter: ppdsc8 == NULL\n");
        return DSERR_INVALIDPARAM;
    }

    if (((IDirectSoundFullDuplexImpl*)pdsfd)->capture_device == NULL) {
        WARN("not initialized\n");
        *ppdsc8 = NULL;
        return DSERR_UNINITIALIZED;
    }

    pdsfddsc = HeapAlloc(GetProcessHeap(),0,sizeof(*pdsfddsc));
    if (pdsfddsc == NULL) {
        WARN("out of memory\n");
        *ppdsc8 = NULL;
        return DSERR_OUTOFMEMORY;
    }

    pdsfddsc->lpVtbl = &DirectSoundFullDuplex_DirectSoundCapture_Vtbl;
    pdsfddsc->ref = 0;
    pdsfddsc->pdsfd = (IDirectSoundFullDuplexImpl *)pdsfd;

    *ppdsc8 = (LPDIRECTSOUNDCAPTURE)pdsfddsc;

    return DS_OK;
}