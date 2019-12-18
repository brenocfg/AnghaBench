#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * member_0; } ;
struct unk_impl {int member_1; int ref; int /*<<< orphan*/ * inner_unk; int /*<<< orphan*/  IUnknown_iface; int /*<<< orphan*/ * member_2; TYPE_1__ member_0; } ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IPersistFile ;
typedef  int /*<<< orphan*/  IAVIStream ;
typedef  int /*<<< orphan*/  IAVIFile ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WAVFile ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int E_NOINTERFACE ; 
 int IAVIFile_AddRef (int /*<<< orphan*/ *) ; 
 int IAVIFile_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IAVIFile_Release (int /*<<< orphan*/ *) ; 
 int IAVIStream_AddRef (int /*<<< orphan*/ *) ; 
 int IAVIStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IAVIFile ; 
 int /*<<< orphan*/  IID_IAVIStream ; 
 int /*<<< orphan*/  IID_IAVIStreaming ; 
 int /*<<< orphan*/  IID_IPersistFile ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IPersistFile_AddRef (int /*<<< orphan*/ *) ; 
 int IPersistFile_Release (int /*<<< orphan*/ *) ; 
 int IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int IUnknown_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  unk_vtbl ; 

__attribute__((used)) static void test_COM_wavfile(void)
{
    struct unk_impl unk_obj = {{&unk_vtbl}, 19, NULL};
    IAVIFile *avif = NULL;
    IPersistFile *pf;
    IAVIStream *avis;
    IUnknown *unk;
    ULONG refcount;
    HRESULT hr;

    /* COM aggregation */
    hr = CoCreateInstance(&CLSID_WAVFile, &unk_obj.IUnknown_iface, CLSCTX_INPROC_SERVER,
            &IID_IUnknown, (void**)&unk_obj.inner_unk);
    ok(hr == S_OK, "COM aggregation failed: %08x, expected S_OK\n", hr);
    hr = IUnknown_QueryInterface(&unk_obj.IUnknown_iface, &IID_IAVIFile, (void**)&avif);
    ok(hr == S_OK, "QueryInterface for IID_IAVIFile failed: %08x\n", hr);
    refcount = IAVIFile_AddRef(avif);
    ok(refcount == unk_obj.ref, "WAVFile just pretends to support COM aggregation\n");
    refcount = IAVIFile_Release(avif);
    ok(refcount == unk_obj.ref, "WAVFile just pretends to support COM aggregation\n");
    hr = IAVIFile_QueryInterface(avif, &IID_IPersistFile, (void**)&pf);
    ok(hr == S_OK, "QueryInterface for IID_IPersistFile failed: %08x\n", hr);
    refcount = IPersistFile_Release(pf);
    ok(refcount == unk_obj.ref, "WAVFile just pretends to support COM aggregation\n");
    refcount = IAVIFile_Release(avif);
    ok(refcount == 19, "Outer ref count should be back at 19 but is %d\n", refcount);
    refcount = IUnknown_Release(unk_obj.inner_unk);
    ok(refcount == 0, "Inner ref count should be 0 but is %u\n", refcount);

    /* Invalid RIID */
    hr = CoCreateInstance(&CLSID_WAVFile, NULL, CLSCTX_INPROC_SERVER, &IID_IAVIStreaming,
            (void**)&avif);
    ok(hr == E_NOINTERFACE, "WAVFile create failed: %08x, expected E_NOINTERFACE\n", hr);

    /* Same refcount for all WAVFile interfaces */
    hr = CoCreateInstance(&CLSID_WAVFile, NULL, CLSCTX_INPROC_SERVER, &IID_IAVIFile, (void**)&avif);
    ok(hr == S_OK, "WAVFile create failed: %08x, expected S_OK\n", hr);
    refcount = IAVIFile_AddRef(avif);
    ok(refcount == 2, "refcount == %u, expected 2\n", refcount);

    hr = IAVIFile_QueryInterface(avif, &IID_IPersistFile, (void**)&pf);
    ok(hr == S_OK, "QueryInterface for IID_IPersistFile failed: %08x\n", hr);
    refcount = IPersistFile_AddRef(pf);
    ok(refcount == 4, "refcount == %u, expected 4\n", refcount);
    refcount = IPersistFile_Release(pf);

    hr = IAVIFile_QueryInterface(avif, &IID_IAVIStream, (void**)&avis);
    ok(hr == S_OK, "QueryInterface for IID_IAVIStream failed: %08x\n", hr);
    refcount = IAVIStream_AddRef(avis);
    ok(refcount == 5, "refcount == %u, expected 5\n", refcount);
    refcount = IAVIStream_Release(avis);

    hr = IAVIFile_QueryInterface(avif, &IID_IUnknown, (void**)&unk);
    ok(hr == S_OK, "QueryInterface for IID_IUnknown failed: %08x\n", hr);
    refcount = IUnknown_AddRef(unk);
    ok(refcount == 6, "refcount == %u, expected 6\n", refcount);
    refcount = IUnknown_Release(unk);

    while (IAVIFile_Release(avif));
}