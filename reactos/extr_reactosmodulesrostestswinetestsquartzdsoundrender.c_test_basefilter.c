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
typedef  void* ULONG ;
typedef  void IPin ;
typedef  int /*<<< orphan*/  IEnumPins ;
typedef  int /*<<< orphan*/  IBaseFilter ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_POINTER ; 
 scalar_t__ IBaseFilter_EnumPins (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumPins_Next (int /*<<< orphan*/ *,int,void**,void**) ; 
 void* IEnumPins_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBaseFilter ; 
 int /*<<< orphan*/  IPin_Release (void*) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,void*) ; 
 int /*<<< orphan*/  pDSRender ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_pin (void*) ; 

__attribute__((used)) static void test_basefilter(void)
{
    IEnumPins *pin_enum = NULL;
    IBaseFilter *base = NULL;
    IPin *pins[2];
    ULONG ref;
    HRESULT hr;

    IUnknown_QueryInterface(pDSRender, &IID_IBaseFilter, (void **)&base);
    if (base == NULL)
    {
        /* test_query_interface handles this case */
        skip("No IBaseFilter\n");
        return;
    }

    hr = IBaseFilter_EnumPins(base, NULL);
    ok(hr == E_POINTER, "hr = %08x and not E_POINTER\n", hr);

    hr= IBaseFilter_EnumPins(base, &pin_enum);
    ok(hr == S_OK, "hr = %08x and not S_OK\n", hr);

    hr = IEnumPins_Next(pin_enum, 1, NULL, NULL);
    ok(hr == E_POINTER, "hr = %08x and not E_POINTER\n", hr);

    hr = IEnumPins_Next(pin_enum, 2, pins, NULL);
    ok(hr == E_INVALIDARG, "hr = %08x and not E_INVALIDARG\n", hr);

    pins[0] = (void *)0xdead;
    pins[1] = (void *)0xdeed;

    hr = IEnumPins_Next(pin_enum, 2, pins, &ref);
    ok(hr == S_FALSE, "hr = %08x instead of S_FALSE\n", hr);
    ok(pins[0] != (void *)0xdead && pins[0] != NULL, "pins[0] = %p\n", pins[0]);
    if (pins[0] != (void *)0xdead && pins[0] != NULL)
    {
        test_pin(pins[0]);
        IPin_Release(pins[0]);
    }

    ok(pins[1] == (void *)0xdeed, "pins[1] = %p\n", pins[1]);

    ref = IEnumPins_Release(pin_enum);
    ok(ref == 0, "ref is %u and not 0!\n", ref);

    IBaseFilter_Release(base);
}