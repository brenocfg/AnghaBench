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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IID_IBaseFilter ; 
 int /*<<< orphan*/  IID_IKsPropertySet ; 
 int /*<<< orphan*/  IID_IMediaPosition ; 
 int /*<<< orphan*/  IID_IMediaSeeking ; 
 int /*<<< orphan*/  IID_IQualProp ; 
 int /*<<< orphan*/  IID_IQualityControl ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pAviSplitter ; 

__attribute__((used)) static void test_query_interface(void)
{
    HRESULT hr;
    ULONG ref;
    IUnknown *iface= NULL;

#define TEST_INTERFACE(riid,expected) do { \
    hr = IUnknown_QueryInterface(pAviSplitter, &riid, (void**)&iface); \
    ok( hr == expected, #riid" should %s got %08X\n", expected==S_OK ? "exist" : "not be present", GetLastError() ); \
    if (hr == S_OK) { \
        ref = IUnknown_Release(iface); \
        ok(ref == 1, "Reference is %u, expected 1\n", ref); \
    } \
    iface = NULL; \
    } while(0)

    TEST_INTERFACE(IID_IBaseFilter,S_OK);
    TEST_INTERFACE(IID_IMediaSeeking,E_NOINTERFACE);
    TEST_INTERFACE(IID_IKsPropertySet,E_NOINTERFACE);
    TEST_INTERFACE(IID_IMediaPosition,E_NOINTERFACE);
    TEST_INTERFACE(IID_IQualityControl,E_NOINTERFACE);
    TEST_INTERFACE(IID_IQualProp,E_NOINTERFACE);
#undef TEST_INTERFACE
}