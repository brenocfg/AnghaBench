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
typedef  int UINT ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INSUFFICIENT_BUFFER ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  GUID_MetadataFormatUnknown ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int S_OK ; 
 int WICMapGuidToShortName (int /*<<< orphan*/ *,int,unsigned char*,int*) ; 
 int WINCODEC_ERR_PROPERTYNOTFOUND ; 
 int /*<<< orphan*/  lstrcmpW (unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int wine_dbgstr_w (unsigned char*) ; 

__attribute__((used)) static void test_WICMapGuidToShortName(void)
{
    static const WCHAR unkW[] = { 'u','n','k',0 };
    static const WCHAR unknownW[] = { 'u','n','k','n','o','w','n',0 };
    HRESULT hr;
    UINT len;
    WCHAR name[16];

    name[0] = 0;
    len = 0xdeadbeef;
    hr = WICMapGuidToShortName(&GUID_MetadataFormatUnknown, 8, name, &len);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(len == 8, "got %u\n", len);
    ok(!lstrcmpW(name, unknownW), "got %s\n", wine_dbgstr_w(name));

    name[0] = 0;
    hr = WICMapGuidToShortName(&GUID_MetadataFormatUnknown, 8, name, NULL);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(!lstrcmpW(name, unknownW), "got %s\n", wine_dbgstr_w(name));

    len = 0xdeadbeef;
    hr = WICMapGuidToShortName(&GUID_MetadataFormatUnknown, 8, NULL, &len);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(len == 8, "got %u\n", len);

    len = 0xdeadbeef;
    hr = WICMapGuidToShortName(&GUID_MetadataFormatUnknown, 0, NULL, &len);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(len == 8, "got %u\n", len);

    hr = WICMapGuidToShortName(&GUID_MetadataFormatUnknown, 0, NULL, NULL);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = WICMapGuidToShortName(&GUID_MetadataFormatUnknown, 8, NULL, NULL);
    ok(hr == S_OK, "got %#x\n", hr);

    hr = WICMapGuidToShortName(&GUID_NULL, 0, NULL, NULL);
    ok(hr == WINCODEC_ERR_PROPERTYNOTFOUND, "got %#x\n", hr);

    name[0] = 0;
    len = 0xdeadbeef;
    hr = WICMapGuidToShortName(&GUID_MetadataFormatUnknown, 4, name, &len);
    ok(hr == HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), "got %#x\n", hr);
    ok(len == 0xdeadbeef, "got %u\n", len);
    ok(!lstrcmpW(name, unkW), "got %s\n", wine_dbgstr_w(name));

    name[0] = 0;
    len = 0xdeadbeef;
    hr = WICMapGuidToShortName(&GUID_MetadataFormatUnknown, 0, name, &len);
    ok(hr == E_INVALIDARG, "got %#x\n", hr);
    ok(len == 0xdeadbeef, "got %u\n", len);
    ok(!name[0], "got %s\n", wine_dbgstr_w(name));

    hr = WICMapGuidToShortName(NULL, 8, name, NULL);
    ok(hr == E_INVALIDARG, "got %#x\n", hr);
}