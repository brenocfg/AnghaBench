#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cBuffers; int cbBuffer; int cbAlign; scalar_t__ cbPrefix; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IMemAllocator ;
typedef  int /*<<< orphan*/  IMediaSample ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ ALLOCATOR_PROPERTIES ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_MemoryAllocator ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IMemAllocator ; 
 int /*<<< orphan*/  IMediaSample_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMemAllocator_Commit (int /*<<< orphan*/ *) ; 
 scalar_t__ IMemAllocator_Decommit (int /*<<< orphan*/ *) ; 
 scalar_t__ IMemAllocator_GetBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMemAllocator_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMemAllocator_SetProperties (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void CommitDecommitTest(void)
{
    IMemAllocator* pMemAllocator;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_MemoryAllocator, NULL, CLSCTX_INPROC_SERVER, &IID_IMemAllocator, (LPVOID*)&pMemAllocator);
    ok(hr==S_OK, "Unable to create memory allocator %x\n", hr);

    if (hr == S_OK)
    {
        ALLOCATOR_PROPERTIES RequestedProps;
        ALLOCATOR_PROPERTIES ActualProps;

        IMediaSample *sample = NULL, *sample2 = NULL;

        RequestedProps.cBuffers = 2;
        RequestedProps.cbBuffer = 65536;
        RequestedProps.cbAlign = 1;
        RequestedProps.cbPrefix = 0;

	hr = IMemAllocator_SetProperties(pMemAllocator, &RequestedProps, &ActualProps);
	ok(hr==S_OK, "SetProperties returned: %x\n", hr);

	hr = IMemAllocator_Commit(pMemAllocator);
	ok(hr==S_OK, "Commit returned: %x\n", hr);
	hr = IMemAllocator_Commit(pMemAllocator);
	ok(hr==S_OK, "Commit returned: %x\n", hr);

        hr = IMemAllocator_GetBuffer(pMemAllocator, &sample, NULL, NULL, 0);
        ok(hr==S_OK, "Could not get a buffer: %x\n", hr);

	hr = IMemAllocator_Decommit(pMemAllocator);
	ok(hr==S_OK, "Decommit returned: %x\n", hr);
	hr = IMemAllocator_Decommit(pMemAllocator);
	ok(hr==S_OK, "Cecommit returned: %x\n", hr);

        /* Decommit and recommit while holding a sample */
        if (sample)
        {
            hr = IMemAllocator_Commit(pMemAllocator);
            ok(hr==S_OK, "Commit returned: %x\n", hr);

            hr = IMemAllocator_GetBuffer(pMemAllocator, &sample2, NULL, NULL, 0);
            ok(hr==S_OK, "Could not get a buffer: %x\n", hr);
            IMediaSample_Release(sample);
            if (sample2)
                IMediaSample_Release(sample2);

            hr = IMemAllocator_Decommit(pMemAllocator);
            ok(hr==S_OK, "Cecommit returned: %x\n", hr);
        }
        IMemAllocator_Release(pMemAllocator);
    }
}