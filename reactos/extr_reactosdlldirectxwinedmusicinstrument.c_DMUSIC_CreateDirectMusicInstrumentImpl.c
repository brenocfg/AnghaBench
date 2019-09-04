#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_2__ IDirectMusicInstrument_iface; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPUNKNOWN ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  TYPE_1__ IDirectMusicInstrumentImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DMUSIC_LockModule () ; 
 int /*<<< orphan*/  DirectMusicInstrument_Vtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectMusicInstrument_QueryInterface (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDirectMusicInstrument_Release (TYPE_2__*) ; 

HRESULT DMUSIC_CreateDirectMusicInstrumentImpl (LPCGUID lpcGUID, LPVOID* ppobj, LPUNKNOWN pUnkOuter) {
	IDirectMusicInstrumentImpl* dminst;
        HRESULT hr;

	dminst = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDirectMusicInstrumentImpl));
	if (NULL == dminst) {
		*ppobj = NULL;
		return E_OUTOFMEMORY;
	}
	dminst->IDirectMusicInstrument_iface.lpVtbl = &DirectMusicInstrument_Vtbl;
        dminst->ref = 1;

        DMUSIC_LockModule();
        hr = IDirectMusicInstrument_QueryInterface(&dminst->IDirectMusicInstrument_iface, lpcGUID,
                ppobj);
        IDirectMusicInstrument_Release(&dminst->IDirectMusicInstrument_iface);

        return hr;
}