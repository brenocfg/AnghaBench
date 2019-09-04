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
typedef  int /*<<< orphan*/  guid ;
typedef  int /*<<< orphan*/  abbuffer ;
typedef  int WICPixelFormatNumericRepresentation ;
typedef  int WICComponentType ;
typedef  int WCHAR ;
typedef  int ULONG ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IWICPixelFormatInfo2 ;
typedef  int /*<<< orphan*/  IWICPixelFormatInfo ;
typedef  int /*<<< orphan*/  IWICComponentInfo ;
typedef  int HRESULT ;
typedef  int GUID ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int E_INVALIDARG ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  GUID_VendorMicrosoft ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGRA ; 
 int /*<<< orphan*/  IID_IWICPixelFormatInfo ; 
 int /*<<< orphan*/  IID_IWICPixelFormatInfo2 ; 
 int IWICComponentInfo_GetAuthor (int /*<<< orphan*/ *,int,int*,int*) ; 
 int IWICComponentInfo_GetCLSID (int /*<<< orphan*/ *,int*) ; 
 int IWICComponentInfo_GetComponentType (int /*<<< orphan*/ *,int*) ; 
 int IWICComponentInfo_GetFriendlyName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int IWICComponentInfo_GetSigningStatus (int /*<<< orphan*/ *,int*) ; 
 int IWICComponentInfo_GetSpecVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int IWICComponentInfo_GetVendorGUID (int /*<<< orphan*/ *,int*) ; 
 int IWICComponentInfo_GetVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int IWICComponentInfo_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IWICComponentInfo_Release (int /*<<< orphan*/ *) ; 
 int IWICPixelFormatInfo2_GetNumericRepresentation (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICPixelFormatInfo2_Release (int /*<<< orphan*/ *) ; 
 int IWICPixelFormatInfo2_SupportsTransparency (int /*<<< orphan*/ *,int*) ; 
 int IWICPixelFormatInfo_GetBitsPerPixel (int /*<<< orphan*/ *,int*) ; 
 int IWICPixelFormatInfo_GetChannelCount (int /*<<< orphan*/ *,int*) ; 
 int IWICPixelFormatInfo_GetChannelMask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int*) ; 
 int IWICPixelFormatInfo_GetFormatGUID (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICPixelFormatInfo_Release (int /*<<< orphan*/ *) ; 
 int IsEqualGUID (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int WICComponentSigned ; 
 int WICPixelFormat ; 
 int WICPixelFormatNumericRepresentationUnsignedInteger ; 
 int WINCODEC_ERR_INSUFFICIENTBUFFER ; 
 scalar_t__ broken (int) ; 
 int get_component_info (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int wine_dbgstr_guid (int*) ; 

__attribute__((used)) static void test_pixelformat_info(void)
{
    IWICComponentInfo *info;
    IWICPixelFormatInfo *pixelformat_info;
    IWICPixelFormatInfo2 *pixelformat_info2;
    HRESULT hr;
    ULONG len, known_len;
    WCHAR value[256];
    GUID guid;
    WICComponentType componenttype;
    WICPixelFormatNumericRepresentation numericrepresentation;
    DWORD signing;
    UINT uiresult;
    BYTE abbuffer[256];
    BOOL supportstransparency;

    hr = get_component_info(&GUID_WICPixelFormat32bppBGRA, &info);
    ok(hr == S_OK, "CreateComponentInfo failed, hr=%x\n", hr);

    if (FAILED(hr))
        return;

    hr = IWICComponentInfo_GetAuthor(info, 0, NULL, 0);
    ok(hr == E_INVALIDARG, "GetAuthor failed, hr=%x\n", hr);

    len = 0xdeadbeef;
    hr = IWICComponentInfo_GetAuthor(info, 0, NULL, &len);
    ok(hr == S_OK, "GetAuthor failed, hr=%x\n", hr);
    ok(len < 255 && len > 0, "invalid length 0x%x\n", len);
    known_len = len;

    memset(value, 0xaa, 256 * sizeof(WCHAR));
    hr = IWICComponentInfo_GetAuthor(info, len-1, value, NULL);
    ok(hr == E_INVALIDARG, "GetAuthor failed, hr=%x\n", hr);
    ok(value[0] == 0xaaaa, "string modified\n");

    len = 0xdeadbeef;
    memset(value, 0xaa, 256 * sizeof(WCHAR));
    hr = IWICComponentInfo_GetAuthor(info, known_len-1, value, &len);
    ok(hr == WINCODEC_ERR_INSUFFICIENTBUFFER, "GetAuthor failed, hr=%x\n", hr);
    ok(len == known_len, "got length of 0x%x, expected 0x%x\n", len, known_len);
    ok(value[known_len-1] == 0xaaaa, "string modified past given length\n");
    ok(value[0] == 0xaaaa, "string modified\n");

    len = 0xdeadbeef;
    memset(value, 0xaa, 256 * sizeof(WCHAR));
    hr = IWICComponentInfo_GetAuthor(info, known_len, value, &len);
    ok(hr == S_OK, "GetAuthor failed, hr=%x\n", hr);
    ok(len == known_len, "got length of 0x%x, expected 0x%x\n", len, known_len);
    ok(value[known_len-1] == 0, "string not terminated at expected length\n");
    ok(value[known_len-2] != 0xaaaa, "string not modified at given length\n");

    len = 0xdeadbeef;
    memset(value, 0xaa, 256 * sizeof(WCHAR));
    hr = IWICComponentInfo_GetAuthor(info, known_len+1, value, &len);
    ok(hr == S_OK, "GetAuthor failed, hr=%x\n", hr);
    ok(len == known_len, "got length of 0x%x, expected 0x%x\n", len, known_len);
    ok(value[known_len] == 0xaaaa, "string modified past end\n");
    ok(value[known_len-1] == 0, "string not terminated at expected length\n");
    ok(value[known_len-2] != 0xaaaa, "string not modified at given length\n");

    hr = IWICComponentInfo_GetCLSID(info, NULL);
    ok(hr == E_INVALIDARG, "GetCLSID failed, hr=%x\n", hr);

    memset(&guid, 0xaa, sizeof(guid));
    hr = IWICComponentInfo_GetCLSID(info, &guid);
    ok(hr == S_OK, "GetCLSID failed, hr=%x\n", hr);
    ok(IsEqualGUID(&guid, &GUID_WICPixelFormat32bppBGRA), "unexpected CLSID %s\n", wine_dbgstr_guid(&guid));

    hr = IWICComponentInfo_GetComponentType(info, NULL);
    ok(hr == E_INVALIDARG, "GetComponentType failed, hr=%x\n", hr);

    hr = IWICComponentInfo_GetComponentType(info, &componenttype);
    ok(hr == S_OK, "GetComponentType failed, hr=%x\n", hr);
    ok(componenttype == WICPixelFormat, "unexpected component type 0x%x\n", componenttype);

    len = 0xdeadbeef;
    hr = IWICComponentInfo_GetFriendlyName(info, 0, NULL, &len);
    ok(hr == S_OK, "GetFriendlyName failed, hr=%x\n", hr);
    ok(len < 255 && len > 0, "invalid length 0x%x\n", len);

    hr = IWICComponentInfo_GetSigningStatus(info, NULL);
    ok(hr == E_INVALIDARG, "GetSigningStatus failed, hr=%x\n", hr);

    hr = IWICComponentInfo_GetSigningStatus(info, &signing);
    ok(hr == S_OK, "GetSigningStatus failed, hr=%x\n", hr);
    ok(signing == WICComponentSigned, "unexpected signing status 0x%x\n", signing);

    len = 0xdeadbeef;
    hr = IWICComponentInfo_GetSpecVersion(info, 0, NULL, &len);
    ok(hr == S_OK, "GetSpecVersion failed, hr=%x\n", hr);
    ok(len == 0, "invalid length 0x%x\n", len); /* spec version does not apply to pixel formats */

    memset(&guid, 0xaa, sizeof(guid));
    hr = IWICComponentInfo_GetVendorGUID(info, &guid);
    ok(hr == S_OK, "GetVendorGUID failed, hr=%x\n", hr);
    ok(IsEqualGUID(&guid, &GUID_VendorMicrosoft) ||
       broken(IsEqualGUID(&guid, &GUID_NULL)) /* XP */, "unexpected GUID %s\n", wine_dbgstr_guid(&guid));

    len = 0xdeadbeef;
    hr = IWICComponentInfo_GetVersion(info, 0, NULL, &len);
    ok(hr == S_OK, "GetVersion failed, hr=%x\n", hr);
    ok(len == 0, "invalid length 0x%x\n", len); /* version does not apply to pixel formats */

    hr = IWICComponentInfo_QueryInterface(info, &IID_IWICPixelFormatInfo, (void**)&pixelformat_info);
    ok(hr == S_OK, "QueryInterface failed, hr=%x\n", hr);

    if (SUCCEEDED(hr))
    {
        hr = IWICPixelFormatInfo_GetBitsPerPixel(pixelformat_info, NULL);
        ok(hr == E_INVALIDARG, "GetBitsPerPixel failed, hr=%x\n", hr);

        hr = IWICPixelFormatInfo_GetBitsPerPixel(pixelformat_info, &uiresult);
        ok(hr == S_OK, "GetBitsPerPixel failed, hr=%x\n", hr);
        ok(uiresult == 32, "unexpected bpp %i\n", uiresult);

        hr = IWICPixelFormatInfo_GetChannelCount(pixelformat_info, &uiresult);
        ok(hr == S_OK, "GetChannelCount failed, hr=%x\n", hr);
        ok(uiresult == 4, "unexpected channel count %i\n", uiresult);

        hr = IWICPixelFormatInfo_GetChannelMask(pixelformat_info, 0, 0, NULL, NULL);
        ok(hr == E_INVALIDARG, "GetChannelMask failed, hr=%x\n", hr);

        uiresult = 0xdeadbeef;
        hr = IWICPixelFormatInfo_GetChannelMask(pixelformat_info, 0, 0, NULL, &uiresult);
        ok(hr == S_OK, "GetChannelMask failed, hr=%x\n", hr);
        ok(uiresult == 4, "unexpected length %i\n", uiresult);

        memset(abbuffer, 0xaa, sizeof(abbuffer));
        hr = IWICPixelFormatInfo_GetChannelMask(pixelformat_info, 0, known_len, abbuffer, NULL);
        ok(hr == E_INVALIDARG, "GetChannelMask failed, hr=%x\n", hr);
        ok(abbuffer[0] == 0xaa, "buffer modified\n");

        uiresult = 0xdeadbeef;
        memset(abbuffer, 0xaa, sizeof(abbuffer));
        hr = IWICPixelFormatInfo_GetChannelMask(pixelformat_info, 0, 3, abbuffer, &uiresult);
        ok(hr == E_INVALIDARG, "GetChannelMask failed, hr=%x\n", hr);
        ok(abbuffer[0] == 0xaa, "buffer modified\n");
        ok(uiresult == 4, "unexpected length %i\n", uiresult);

        memset(abbuffer, 0xaa, sizeof(abbuffer));
        hr = IWICPixelFormatInfo_GetChannelMask(pixelformat_info, 0, 4, abbuffer, &uiresult);
        ok(hr == S_OK, "GetChannelMask failed, hr=%x\n", hr);
        ok(*((ULONG*)abbuffer) == 0xff, "unexpected mask 0x%x\n", *((ULONG*)abbuffer));
        ok(uiresult == 4, "unexpected length %i\n", uiresult);

        memset(abbuffer, 0xaa, sizeof(abbuffer));
        hr = IWICPixelFormatInfo_GetChannelMask(pixelformat_info, 0, 5, abbuffer, &uiresult);
        ok(hr == S_OK, "GetChannelMask failed, hr=%x\n", hr);
        ok(*((ULONG*)abbuffer) == 0xff, "unexpected mask 0x%x\n", *((ULONG*)abbuffer));
        ok(abbuffer[4] == 0xaa, "buffer modified past actual length\n");
        ok(uiresult == 4, "unexpected length %i\n", uiresult);

        memset(&guid, 0xaa, sizeof(guid));
        hr = IWICPixelFormatInfo_GetFormatGUID(pixelformat_info, &guid);
        ok(hr == S_OK, "GetFormatGUID failed, hr=%x\n", hr);
        ok(IsEqualGUID(&guid, &GUID_WICPixelFormat32bppBGRA), "unexpected GUID %s\n", wine_dbgstr_guid(&guid));

        IWICPixelFormatInfo_Release(pixelformat_info);
    }

    hr = IWICComponentInfo_QueryInterface(info, &IID_IWICPixelFormatInfo2, (void**)&pixelformat_info2);

    if (FAILED(hr))
        win_skip("IWICPixelFormatInfo2 not supported\n");
    else
    {
        hr = IWICPixelFormatInfo2_GetNumericRepresentation(pixelformat_info2, NULL);
        ok(hr == E_INVALIDARG, "GetNumericRepresentation failed, hr=%x\n", hr);

        numericrepresentation = 0xdeadbeef;
        hr = IWICPixelFormatInfo2_GetNumericRepresentation(pixelformat_info2, &numericrepresentation);
        ok(hr == S_OK, "GetNumericRepresentation failed, hr=%x\n", hr);
        ok(numericrepresentation == WICPixelFormatNumericRepresentationUnsignedInteger, "unexpected numeric representation %i\n", numericrepresentation);

        hr = IWICPixelFormatInfo2_SupportsTransparency(pixelformat_info2, NULL);
        ok(hr == E_INVALIDARG, "SupportsTransparency failed, hr=%x\n", hr);

        supportstransparency = 0xdeadbeef;
        hr = IWICPixelFormatInfo2_SupportsTransparency(pixelformat_info2, &supportstransparency);
        ok(hr == S_OK, "SupportsTransparency failed, hr=%x\n", hr);
        ok(supportstransparency == 1, "unexpected value %i\n", supportstransparency);

        IWICPixelFormatInfo2_Release(pixelformat_info2);
    }

    IWICComponentInfo_Release(info);
}