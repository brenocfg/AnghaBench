#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char member_0; char member_1; char member_2; char member_3; char member_4; char member_5; char member_6; char member_7; char member_8; float member_9; char member_10; char member_11; char member_12; char member_13; char member_14; char member_15; char member_16; char member_17; char member_18; char member_19; char member_20; int /*<<< orphan*/  member_21; } ;
struct TYPE_5__ {int member_0; } ;
struct test_data {TYPE_2__ member_5; int /*<<< orphan*/ * member_4; TYPE_1__ member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  const member_0; } ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int QuadPart; } ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IWICPersistStream ;
typedef  int /*<<< orphan*/  IWICMetadataReader ;
typedef  int /*<<< orphan*/  IWICMetadataHandlerInfo ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  GCE_data ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct test_data const*) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WICGCEMetadataReader ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  GUID_MetadataFormatGCE ; 
 int /*<<< orphan*/  IID_IWICMetadataReader ; 
 int /*<<< orphan*/  IID_IWICPersistStream ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IStream_Seek (int /*<<< orphan*/ *,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IWICMetadataHandlerInfo_GetCLSID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICMetadataHandlerInfo_GetFriendlyName (int /*<<< orphan*/ *,int,char*,scalar_t__*) ; 
 int /*<<< orphan*/  IWICMetadataHandlerInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICMetadataReader_GetCount (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IWICMetadataReader_GetMetadataFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICMetadataReader_GetMetadataHandlerInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICMetadataReader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICPersistStream_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICPersistStream_Release (int /*<<< orphan*/ *) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ REGDB_E_CLASSNOTREG ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
#define  VT_BOOL 130 
#define  VT_UI1 129 
#define  VT_UI2 128 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  compare_metadata (int /*<<< orphan*/ *,struct test_data const*,scalar_t__) ; 
 int /*<<< orphan*/ * create_stream (char const*,int) ; 
 scalar_t__ lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_metadata_GCE(void)
{
    static const WCHAR GCE_name[] = {'G','r','a','p','h','i','c',' ','C','o','n','t','r','o','l',' ','E','x','t','e','n','s','i','o','n',' ','R','e','a','d','e','r',0};
    static const char GCE_data[] = "hello world!\xa\x2\x3\x4\x5\x6\x7\x8\xed\xa\xb\xc\xd\xe\xf";
    static const struct test_data td[5] =
    {
        { VT_UI1, 0, 0, { 2 }, NULL, { 'D','i','s','p','o','s','a','l',0 } },
        { VT_BOOL, 0, 0, { 1 }, NULL, { 'U','s','e','r','I','n','p','u','t','F','l','a','g',0 } },
        { VT_BOOL, 0, 0, { 0 }, NULL, { 'T','r','a','n','s','p','a','r','e','n','c','y','F','l','a','g',0 } },
        { VT_UI2, 0, 0, { 0x302 }, NULL, { 'D','e','l','a','y',0 } },
        { VT_UI1, 0, 0, { 4 }, NULL, { 'T','r','a','n','s','p','a','r','e','n','t','C','o','l','o','r','I','n','d','e','x',0 } }
    };
    LARGE_INTEGER pos;
    HRESULT hr;
    IStream *stream;
    IWICPersistStream *persist;
    IWICMetadataReader *reader;
    IWICMetadataHandlerInfo *info;
    WCHAR name[64];
    UINT count, dummy;
    GUID format;
    CLSID id;

    hr = CoCreateInstance(&CLSID_WICGCEMetadataReader, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IWICMetadataReader, (void **)&reader);
    ok(hr == S_OK || broken(hr == E_NOINTERFACE || hr == REGDB_E_CLASSNOTREG) /* before Win7 */,
       "CoCreateInstance error %#x\n", hr);

    stream = create_stream(GCE_data, sizeof(GCE_data));

    if (SUCCEEDED(hr))
    {
        pos.QuadPart = 12;
        hr = IStream_Seek(stream, pos, SEEK_SET, NULL);
        ok(hr == S_OK, "IStream_Seek error %#x\n", hr);

        hr = IUnknown_QueryInterface(reader, &IID_IWICPersistStream, (void **)&persist);
        ok(hr == S_OK, "QueryInterface error %#x\n", hr);

        hr = IWICPersistStream_Load(persist, stream);
        ok(hr == S_OK, "Load error %#x\n", hr);

        IWICPersistStream_Release(persist);
    }

    if (SUCCEEDED(hr))
    {
        hr = IWICMetadataReader_GetCount(reader, &count);
        ok(hr == S_OK, "GetCount error %#x\n", hr);
        ok(count == ARRAY_SIZE(td), "unexpected count %u\n", count);

        compare_metadata(reader, td, count);

        hr = IWICMetadataReader_GetMetadataFormat(reader, &format);
        ok(hr == S_OK, "GetMetadataFormat error %#x\n", hr);
        ok(IsEqualGUID(&format, &GUID_MetadataFormatGCE), "wrong format %s\n", wine_dbgstr_guid(&format));

        hr = IWICMetadataReader_GetMetadataHandlerInfo(reader, &info);
        ok(hr == S_OK, "GetMetadataHandlerInfo error %#x\n", hr);

        hr = IWICMetadataHandlerInfo_GetCLSID(info, &id);
        ok(hr == S_OK, "GetCLSID error %#x\n", hr);
        ok(IsEqualGUID(&id, &CLSID_WICGCEMetadataReader), "wrong CLSID %s\n", wine_dbgstr_guid(&id));

        hr = IWICMetadataHandlerInfo_GetFriendlyName(info, 64, name, &dummy);
        ok(hr == S_OK, "GetFriendlyName error %#x\n", hr);
        ok(lstrcmpW(name, GCE_name) == 0, "wrong GCE reader name %s\n", wine_dbgstr_w(name));

        IWICMetadataHandlerInfo_Release(info);
        IWICMetadataReader_Release(reader);
    }

    IStream_Release(stream);
}