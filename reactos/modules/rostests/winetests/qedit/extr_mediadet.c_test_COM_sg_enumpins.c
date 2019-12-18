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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IEnumPins ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_SampleGrabber ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int IBaseFilter_EnumPins (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 int IEnumPins_AddRef (int /*<<< orphan*/ *) ; 
 int IEnumPins_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IEnumPins_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBaseFilter ; 
 int /*<<< orphan*/  IID_IEnumPins ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int IUnknown_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_COM_sg_enumpins(void)
{
    IBaseFilter *bf;
    IEnumPins *pins, *pins2;
    IUnknown *unk;
    ULONG refcount;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, &IID_IBaseFilter,
            (void**)&bf);
    ok(hr == S_OK, "SampleGrabber create failed: %08x, expected S_OK\n", hr);
    hr = IBaseFilter_EnumPins(bf, &pins);
    ok(hr == S_OK, "EnumPins create failed: %08x, expected S_OK\n", hr);

    /* Same refcount for all EnumPins interfaces */
    refcount = IEnumPins_AddRef(pins);
    ok(refcount == 2, "refcount == %u, expected 2\n", refcount);
    hr = IEnumPins_QueryInterface(pins, &IID_IEnumPins, (void**)&pins2);
    ok(hr == S_OK, "QueryInterface for IID_IEnumPins failed: %08x\n", hr);
    ok(pins == pins2, "QueryInterface for self failed (%p != %p)\n", pins, pins2);
    IEnumPins_Release(pins2);

    hr = IEnumPins_QueryInterface(pins, &IID_IUnknown, (void**)&unk);
    ok(hr == S_OK, "QueryInterface for IID_IUnknown failed: %08x\n", hr);
    refcount = IUnknown_AddRef(unk);
    ok(refcount == 4, "refcount == %u, expected 4\n", refcount);
    refcount = IUnknown_Release(unk);

    while (IEnumPins_Release(pins));
    IBaseFilter_Release(bf);
}