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
typedef  int /*<<< orphan*/  IWMWriter ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IWMWriter ; 
 scalar_t__ IWMWriter_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IWMWriter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ WMCreateWriterPriv (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_WMCreateWriterPriv(void)
{
    IWMWriter *writer, *writer2;
    HRESULT hr;

    hr = WMCreateWriterPriv(&writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IWMWriter_QueryInterface(writer, &IID_IWMWriter, (void**)&writer2);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    IWMWriter_Release(writer);
    IWMWriter_Release(writer2);
}