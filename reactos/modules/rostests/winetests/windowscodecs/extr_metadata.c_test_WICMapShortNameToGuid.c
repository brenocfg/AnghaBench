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
typedef  unsigned char WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GUID_MetadataFormatUnknown ; 
 int /*<<< orphan*/  GUID_MetadataFormatXMP ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ WICMapShortNameToGuid (unsigned char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ WINCODEC_ERR_PROPERTYNOTFOUND ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_WICMapShortNameToGuid(void)
{
    static const WCHAR unkW[] = { 'u','n','k',0 };
    static const WCHAR xmpW[] = { 'x','m','p',0 };
    static const WCHAR XmPW[] = { 'X','m','P',0 };
    static const WCHAR unknownW[] = { 'u','n','k','n','o','w','n',0 };
    HRESULT hr;
    GUID guid;

    hr = WICMapShortNameToGuid(NULL, NULL);
    ok(hr == E_INVALIDARG, "got %#x\n", hr);

    hr = WICMapShortNameToGuid(NULL, &guid);
    ok(hr == E_INVALIDARG, "got %#x\n", hr);

    hr = WICMapShortNameToGuid(unknownW, NULL);
    ok(hr == E_INVALIDARG, "got %#x\n", hr);

    hr = WICMapShortNameToGuid(unkW, &guid);
    ok(hr == WINCODEC_ERR_PROPERTYNOTFOUND, "got %#x\n", hr);

    hr = WICMapShortNameToGuid(unknownW, &guid);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(IsEqualGUID(&guid, &GUID_MetadataFormatUnknown), "got %s\n", wine_dbgstr_guid(&guid));

    hr = WICMapShortNameToGuid(xmpW, &guid);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(IsEqualGUID(&guid, &GUID_MetadataFormatXMP), "got %s\n", wine_dbgstr_guid(&guid));

    guid = GUID_NULL;
    hr = WICMapShortNameToGuid(XmPW, &guid);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(IsEqualGUID(&guid, &GUID_MetadataFormatXMP), "got %s\n", wine_dbgstr_guid(&guid));
}