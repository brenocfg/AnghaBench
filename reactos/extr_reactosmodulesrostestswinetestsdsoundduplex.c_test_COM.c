#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cbufdesc ;
typedef  int /*<<< orphan*/  bufdesc ;
struct TYPE_8__ {int /*<<< orphan*/  nAvgBytesPerSec; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  int ULONG ;
struct TYPE_9__ {int dwSize; TYPE_1__* lpwfxFormat; int /*<<< orphan*/  dwBufferBytes; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDirectSoundFullDuplex ;
typedef  int /*<<< orphan*/  IDirectSoundCaptureBuffer8 ;
typedef  int /*<<< orphan*/  IDirectSoundCapture ;
typedef  int /*<<< orphan*/  IDirectSoundBuffer8 ;
typedef  int /*<<< orphan*/  IDirectSound8 ;
typedef  int /*<<< orphan*/  IDirectSound ;
typedef  int HRESULT ;
typedef  TYPE_2__ DSCBUFFERDESC ;
typedef  TYPE_2__ DSBUFFERDESC ;

/* Variables and functions */
 int CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_DirectSoundFullDuplex ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int DSERR_INVALIDCALL ; 
 int DSERR_NODRIVER ; 
 int /*<<< orphan*/  DSSCL_EXCLUSIVE ; 
 int E_INVALIDARG ; 
 int E_NOINTERFACE ; 
 int IDirectSound8_AddRef (int /*<<< orphan*/ *) ; 
 int IDirectSound8_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IDirectSound8_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundBuffer8_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundCaptureBuffer8_Release (int /*<<< orphan*/ *) ; 
 int IDirectSoundCapture_AddRef (int /*<<< orphan*/ *) ; 
 int IDirectSoundCapture_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IDirectSoundCapture_Release (int /*<<< orphan*/ *) ; 
 int IDirectSoundFullDuplex_AddRef (int /*<<< orphan*/ *) ; 
 int IDirectSoundFullDuplex_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int IDirectSoundFullDuplex_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IDirectSoundFullDuplex_Release (int /*<<< orphan*/ *) ; 
 int IDirectSound_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDirectSound ; 
 int /*<<< orphan*/  IID_IDirectSound3DBuffer ; 
 int /*<<< orphan*/  IID_IDirectSound8 ; 
 int /*<<< orphan*/  IID_IDirectSoundCapture ; 
 int /*<<< orphan*/  IID_IDirectSoundFullDuplex ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  get_hwnd () ; 
 int /*<<< orphan*/  init_format (TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_COM(void)
{
    IDirectSoundFullDuplex *dsfd = (IDirectSoundFullDuplex*)0xdeadbeef;
    IDirectSound *ds;
    IDirectSound8 *ds8;
    IDirectSoundCapture *dsc;
    IUnknown *unk, *unk8;
    IDirectSoundBuffer8 *dsb8;
    IDirectSoundCaptureBuffer8 *dscb8;
    DSBUFFERDESC bufdesc;
    DSCBUFFERDESC cbufdesc;
    WAVEFORMATEX wfx;
    ULONG refcount;
    HRESULT hr;

    /* COM aggregation */
    hr = CoCreateInstance(&CLSID_DirectSoundFullDuplex, (IUnknown*)&dsfd, CLSCTX_INPROC_SERVER,
            &IID_IUnknown, (void**)&dsfd);
    ok(hr == CLASS_E_NOAGGREGATION,
            "DirectSoundFullDuplex create failed: %08x, expected CLASS_E_NOAGGREGATION\n", hr);
    ok(!dsfd, "dsfd = %p\n", dsfd);

    /* Invalid RIID */
    hr = CoCreateInstance(&CLSID_DirectSoundFullDuplex, NULL, CLSCTX_INPROC_SERVER,
            &IID_IDirectSound3DBuffer, (void**)&dsfd);
    ok(hr == E_NOINTERFACE,
            "DirectSoundFullDuplex create failed: %08x, expected E_NOINTERFACE\n", hr);

    /* Different refcount for IDirectSoundFullDuplex and for IUnknown */
    hr = CoCreateInstance(&CLSID_DirectSoundFullDuplex, NULL, CLSCTX_INPROC_SERVER,
            &IID_IDirectSoundFullDuplex, (void**)&dsfd);
    ok(hr == S_OK, "DirectSoundFullDuplex create failed: %08x, expected S_OK\n", hr);
    refcount = IDirectSoundFullDuplex_AddRef(dsfd);
    ok(refcount == 2, "refcount == %u, expected 2\n", refcount);
    hr = IDirectSoundFullDuplex_QueryInterface(dsfd, &IID_IUnknown, (void**)&unk);
    ok(hr == S_OK, "QueryInterface for IID_IUnknown failed: %08x\n", hr);
    refcount = IUnknown_AddRef(unk);
    ok(refcount == 2, "refcount == %u, expected 2\n", refcount);

    /* Not initialized */
    hr = IDirectSoundFullDuplex_QueryInterface(dsfd, &IID_IDirectSound8, (void**)&ds8);
    ok(hr == E_NOINTERFACE,
            "QueryInterface for IID_IDirectSound8 failed: %08x, expected E_NOINTERFACE\n", hr);
    hr = IDirectSoundFullDuplex_QueryInterface(dsfd, &IID_IDirectSoundCapture, (void**)&dsc);
    ok(hr == E_NOINTERFACE,
            "QueryInterface for IID_IDirectSoundCapture failed: %08x, expected E_NOINTERFACE\n", hr);

    init_format(&wfx, WAVE_FORMAT_PCM, 44100, 16, 1);
    ZeroMemory(&bufdesc, sizeof(bufdesc));
    bufdesc.dwSize = sizeof(bufdesc);
    bufdesc.dwBufferBytes = wfx.nAvgBytesPerSec;
    bufdesc.lpwfxFormat = &wfx;
    ZeroMemory(&cbufdesc, sizeof(cbufdesc));
    cbufdesc.dwSize = sizeof(cbufdesc);
    cbufdesc.dwBufferBytes = wfx.nAvgBytesPerSec;
    cbufdesc.lpwfxFormat = &wfx;
    hr = IDirectSoundFullDuplex_Initialize(dsfd, NULL, NULL, &cbufdesc, &bufdesc, get_hwnd(),
            DSSCL_EXCLUSIVE, NULL, NULL);
    ok(hr == E_INVALIDARG,
            "IDirectSoundFullDuplex_Initialize failed: %08x, expected E_INVALIDARG\n", hr);
    hr = IDirectSoundFullDuplex_Initialize(dsfd, NULL, NULL, &cbufdesc, &bufdesc, get_hwnd(),
            DSSCL_EXCLUSIVE, &dscb8, &dsb8);
    if (hr == DSERR_NODRIVER || hr == DSERR_INVALIDCALL) {
        skip("No driver\n");
        return;
    }
    ok(hr == S_OK, "IDirectSoundFullDuplex_Initialize failed: %08x\n", hr);

    /* IDirectSound and IDirectSound8 */
    hr = IDirectSoundFullDuplex_QueryInterface(dsfd, &IID_IDirectSound8, (void**)&ds8);
    ok(hr == S_OK, "QueryInterface for IID_IDirectSound8 failed: %08x\n", hr);
    refcount = IDirectSound8_AddRef(ds8);
    ok(refcount == 2, "refcount == %u, expected 2\n", refcount);
    hr = IDirectSoundFullDuplex_QueryInterface(dsfd, &IID_IDirectSound, (void**)&ds);
    ok(hr == S_OK, "QueryInterface for IID_IDirectSound failed: %08x\n", hr);
    refcount = IDirectSound8_AddRef(ds8);
    ok(refcount == 4, "refcount == %u, expected 4\n", refcount);
    refcount = IDirectSound_AddRef(ds);
    ok(refcount == 5, "refcount == %u, expected 5\n", refcount);
    hr = IDirectSound8_QueryInterface(ds8, &IID_IUnknown, (void**)&unk8);
    ok(hr == S_OK, "QueryInterface for IID_IUnknown failed: %08x\n", hr);
    ok(unk == unk8, "Got different IUnknown when QI'ing IDirectSoundFullDuplex and IDirectSound\n");
    refcount = IUnknown_AddRef(unk8);
    ok(refcount == 4, "refcount == %u, expected 4\n", refcount);
    refcount = IDirectSound_AddRef(ds);
    ok(refcount == 6, "refcount == %u, expected 6\n", refcount);
    refcount = IDirectSoundFullDuplex_AddRef(dsfd);
    ok(refcount == 3, "refcount == %u, expected 3\n", refcount);

    /* IDirectSoundCapture */
    hr = IDirectSoundFullDuplex_QueryInterface(dsfd, &IID_IDirectSoundCapture, (void**)&dsc);
    ok(hr == S_OK, "QueryInterface for IID_IDirectSoundCapture failed: %08x\n", hr);
    refcount = IDirectSoundCapture_AddRef(dsc);
    ok(refcount == 2, "refcount == %u, expected 2\n", refcount);
    refcount = IDirectSoundFullDuplex_AddRef(dsfd);
    ok(refcount == 4, "refcount == %u, expected 4\n", refcount);
    hr = IDirectSoundCapture_QueryInterface(ds8, &IID_IUnknown, (void**)&unk8);
    ok(hr == S_OK, "QueryInterface for IID_IUnknown failed: %08x\n", hr);
    ok(unk == unk8,
            "Got different IUnknown when QI'ing IDirectSoundFullDuplex and IDirectSoundCapture\n");
    refcount = IUnknown_AddRef(unk8);
    ok(refcount == 6, "refcount == %u, expected 6\n", refcount);

    IDirectSoundBuffer8_Release(dsb8);
    IDirectSoundCaptureBuffer8_Release(dscb8);
    while (IDirectSound8_Release(ds8));
    while (IDirectSoundCapture_Release(dsc));
    while (IDirectSoundFullDuplex_Release(dsfd));
    while (IUnknown_Release(unk));
}