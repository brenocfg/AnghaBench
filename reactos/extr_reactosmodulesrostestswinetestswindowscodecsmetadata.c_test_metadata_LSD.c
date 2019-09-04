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
struct TYPE_6__ {char member_0; char member_1; char member_2; char member_3; char member_4; char member_5; unsigned char member_6; char member_7; char member_8; char member_9; char member_10; char member_11; char member_12; char member_13; char member_14; char member_15; float member_16; char member_17; char member_18; char member_19; int /*<<< orphan*/  member_20; } ;
struct TYPE_5__ {char member_0; char member_1; char member_2; char member_3; char member_4; char member_5; } ;
struct test_data {int member_0; int member_2; TYPE_2__ member_5; int /*<<< orphan*/ * member_4; TYPE_1__ member_3; int /*<<< orphan*/  member_1; } ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int QuadPart; } ;
typedef  int /*<<< orphan*/  LSD_data ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IWICPersistStream ;
typedef  int /*<<< orphan*/  IWICMetadataReader ;
typedef  int /*<<< orphan*/  IWICMetadataHandlerInfo ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct test_data const*) ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WICLSDMetadataReader ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  GUID_MetadataFormatLSD ; 
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
#define  VT_BOOL 131 
#define  VT_UI1 130 
#define  VT_UI2 129 
#define  VT_VECTOR 128 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  compare_metadata (int /*<<< orphan*/ *,struct test_data const*,scalar_t__) ; 
 int /*<<< orphan*/ * create_stream (char const*,int) ; 
 scalar_t__ lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_metadata_LSD(void)
{
    static const WCHAR LSD_name[] = {'L','o','g','i','c','a','l',' ','S','c','r','e','e','n',' ','D','e','s','c','r','i','p','t','o','r',' ','R','e','a','d','e','r',0};
    static const char LSD_data[] = "hello world!\x1\x2\x3\x4\xab\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf";
    static const struct test_data td[9] =
    {
        { VT_UI1|VT_VECTOR, 0, 6, {'w','o','r','l','d','!'}, NULL, { 'S','i','g','n','a','t','u','r','e',0 } },
        { VT_UI2, 0, 0, { 0x201 }, NULL, { 'W','i','d','t','h',0 } },
        { VT_UI2, 0, 0, { 0x403 }, NULL, { 'H','e','i','g','h','t',0 } },
        { VT_BOOL, 0, 0, { 1 }, NULL, { 'G','l','o','b','a','l','C','o','l','o','r','T','a','b','l','e','F','l','a','g',0 } },
        { VT_UI1, 0, 0, { 2 }, NULL, { 'C','o','l','o','r','R','e','s','o','l','u','t','i','o','n',0 } },
        { VT_BOOL, 0, 0, { 1 }, NULL, { 'S','o','r','t','F','l','a','g',0 } },
        { VT_UI1, 0, 0, { 3 }, NULL, { 'G','l','o','b','a','l','C','o','l','o','r','T','a','b','l','e','S','i','z','e',0 } },
        { VT_UI1, 0, 0, { 6 }, NULL, { 'B','a','c','k','g','r','o','u','n','d','C','o','l','o','r','I','n','d','e','x',0 } },
        { VT_UI1, 0, 0, { 7 }, NULL, { 'P','i','x','e','l','A','s','p','e','c','t','R','a','t','i','o',0 } }
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

    hr = CoCreateInstance(&CLSID_WICLSDMetadataReader, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IWICMetadataReader, (void **)&reader);
    ok(hr == S_OK || broken(hr == E_NOINTERFACE || hr == REGDB_E_CLASSNOTREG) /* before Win7 */,
       "CoCreateInstance error %#x\n", hr);

    stream = create_stream(LSD_data, sizeof(LSD_data));

    if (SUCCEEDED(hr))
    {
        pos.QuadPart = 6;
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
        ok(IsEqualGUID(&format, &GUID_MetadataFormatLSD), "wrong format %s\n", wine_dbgstr_guid(&format));

        hr = IWICMetadataReader_GetMetadataHandlerInfo(reader, &info);
        ok(hr == S_OK, "GetMetadataHandlerInfo error %#x\n", hr);

        hr = IWICMetadataHandlerInfo_GetCLSID(info, &id);
        ok(hr == S_OK, "GetCLSID error %#x\n", hr);
        ok(IsEqualGUID(&id, &CLSID_WICLSDMetadataReader), "wrong CLSID %s\n", wine_dbgstr_guid(&id));

        hr = IWICMetadataHandlerInfo_GetFriendlyName(info, 64, name, &dummy);
        ok(hr == S_OK, "GetFriendlyName error %#x\n", hr);
        ok(lstrcmpW(name, LSD_name) == 0, "wrong LSD reader name %s\n", wine_dbgstr_w(name));

        IWICMetadataHandlerInfo_Release(info);
        IWICMetadataReader_Release(reader);
    }

    IStream_Release(stream);
}