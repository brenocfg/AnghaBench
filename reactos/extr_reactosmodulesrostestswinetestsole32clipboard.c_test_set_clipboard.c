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
typedef  int /*<<< orphan*/ * LPDATAOBJECT ;
typedef  void* HRESULT ;
typedef  void* HGLOBAL ;

/* Variables and functions */
 void* CO_E_NOTINITIALIZED ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 void* DataObjectImpl_CreateComplex (int /*<<< orphan*/ **) ; 
 void* DataObjectImpl_CreateText (char*,int /*<<< orphan*/ **) ; 
 scalar_t__ FAILED (void*) ; 
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int GMEM_ZEROINIT ; 
 void* GetClipboardData (void*) ; 
 void* GlobalAlloc (int,int) ; 
 void* GlobalLock (void*) ; 
 int /*<<< orphan*/  GlobalUnlock (void*) ; 
 void* IDataObject_Release (int /*<<< orphan*/ *) ; 
 void* OleFlushClipboard () ; 
 void* OleInitialize (int /*<<< orphan*/ *) ; 
 void* OleIsCurrentClipboard (int /*<<< orphan*/ *) ; 
 void* OleSetClipboard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OleUninitialize () ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ *) ; 
 void* RegisterClipboardFormatA (char*) ; 
 void* S_FALSE ; 
 void* S_OK ; 
 void* SetClipboardData (void*,void*) ; 
 void* cf_another ; 
 void* cf_global ; 
 void* cf_onemore ; 
 void* cf_storage ; 
 void* cf_stream ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_cf_dataobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_complex_get_clipboard () ; 
 int /*<<< orphan*/  test_enum_fmtetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_get_clipboard () ; 
 int /*<<< orphan*/  test_no_cf_dataobject () ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_set_clipboard(void)
{
    HRESULT hr;
    ULONG ref;
    LPDATAOBJECT data1, data2, data_cmpl;
    HGLOBAL hblob, h;
    void *ptr;

    cf_stream = RegisterClipboardFormatA("stream format");
    cf_storage = RegisterClipboardFormatA("storage format");
    cf_global = RegisterClipboardFormatA("global format");
    cf_another = RegisterClipboardFormatA("another format");
    cf_onemore = RegisterClipboardFormatA("one more format");

    hr = DataObjectImpl_CreateText("data1", &data1);
    ok(hr == S_OK, "Failed to create data1 object: 0x%08x\n", hr);
    if(FAILED(hr))
        return;
    hr = DataObjectImpl_CreateText("data2", &data2);
    ok(hr == S_OK, "Failed to create data2 object: 0x%08x\n", hr);
    if(FAILED(hr))
        return;
    hr = DataObjectImpl_CreateComplex(&data_cmpl);
    ok(hr == S_OK, "Failed to create complex data object: 0x%08x\n", hr);
    if(FAILED(hr))
        return;

    hr = OleSetClipboard(data1);
    ok(hr == CO_E_NOTINITIALIZED, "OleSetClipboard should have failed with CO_E_NOTINITIALIZED instead of 0x%08x\n", hr);

    CoInitialize(NULL);
    hr = OleSetClipboard(data1);
    ok(hr == CO_E_NOTINITIALIZED, "OleSetClipboard failed with 0x%08x\n", hr);
    CoUninitialize();

    hr = OleInitialize(NULL);
    ok(hr == S_OK, "OleInitialize failed with error 0x%08x\n", hr);

    hr = OleSetClipboard(data1);
    ok(hr == S_OK, "failed to set clipboard to data1, hr = 0x%08x\n", hr);

    test_cf_dataobject(data1);

    hr = OleIsCurrentClipboard(data1);
    ok(hr == S_OK, "expected current clipboard to be data1, hr = 0x%08x\n", hr);
    hr = OleIsCurrentClipboard(data2);
    ok(hr == S_FALSE, "did not expect current clipboard to be data2, hr = 0x%08x\n", hr);
    hr = OleIsCurrentClipboard(NULL);
    ok(hr == S_FALSE, "expect S_FALSE, hr = 0x%08x\n", hr);

    test_get_clipboard();

    hr = OleSetClipboard(data2);
    ok(hr == S_OK, "failed to set clipboard to data2, hr = 0x%08x\n", hr);
    hr = OleIsCurrentClipboard(data1);
    ok(hr == S_FALSE, "did not expect current clipboard to be data1, hr = 0x%08x\n", hr);
    hr = OleIsCurrentClipboard(data2);
    ok(hr == S_OK, "expected current clipboard to be data2, hr = 0x%08x\n", hr);
    hr = OleIsCurrentClipboard(NULL);
    ok(hr == S_FALSE, "expect S_FALSE, hr = 0x%08x\n", hr);

    /* put a format directly onto the clipboard to show
       OleFlushClipboard doesn't empty the clipboard */
    hblob = GlobalAlloc(GMEM_DDESHARE|GMEM_MOVEABLE|GMEM_ZEROINIT, 10);
    ptr = GlobalLock( hblob );
    ok( ptr && ptr != hblob, "got fixed block %p / %p\n", ptr, hblob );
    GlobalUnlock( hblob );
    ok( OpenClipboard(NULL), "OpenClipboard failed\n" );
    h = SetClipboardData(cf_onemore, hblob);
    ok(h == hblob, "got %p\n", h);
    h = GetClipboardData(cf_onemore);
    ok(h == hblob, "got %p / %p\n", h, hblob);
    ptr = GlobalLock( h );
    ok( ptr && ptr != h, "got fixed block %p / %p\n", ptr, h );
    GlobalUnlock( hblob );
    ok( CloseClipboard(), "CloseClipboard failed\n" );

    hr = OleFlushClipboard();
    ok(hr == S_OK, "failed to flush clipboard, hr = 0x%08x\n", hr);
    hr = OleIsCurrentClipboard(data1);
    ok(hr == S_FALSE, "did not expect current clipboard to be data1, hr = 0x%08x\n", hr);
    hr = OleIsCurrentClipboard(data2);
    ok(hr == S_FALSE, "did not expect current clipboard to be data2, hr = 0x%08x\n", hr);
    hr = OleIsCurrentClipboard(NULL);
    ok(hr == S_FALSE, "expect S_FALSE, hr = 0x%08x\n", hr);

    /* format should survive the flush */
    ok( OpenClipboard(NULL), "OpenClipboard failed\n" );
    h = GetClipboardData(cf_onemore);
    ok(h == hblob, "got %p\n", h);
    ptr = GlobalLock( h );
    ok( ptr && ptr != h, "got fixed block %p / %p\n", ptr, h );
    GlobalUnlock( hblob );
    ok( CloseClipboard(), "CloseClipboard failed\n" );

    test_cf_dataobject(NULL);

    ok(OleSetClipboard(NULL) == S_OK, "failed to clear clipboard, hr = 0x%08x\n", hr);

    OpenClipboard(NULL);
    h = GetClipboardData(cf_onemore);
    ok(h == NULL, "got %p\n", h);
    CloseClipboard();

    trace("setting complex\n");
    hr = OleSetClipboard(data_cmpl);
    ok(hr == S_OK, "failed to set clipboard to complex data, hr = 0x%08x\n", hr);
    test_complex_get_clipboard();
    test_cf_dataobject(data_cmpl);
    test_enum_fmtetc(data_cmpl);

    ok(OleSetClipboard(NULL) == S_OK, "failed to clear clipboard, hr = 0x%08x\n", hr);

    test_no_cf_dataobject();
    test_enum_fmtetc(NULL);

    ref = IDataObject_Release(data1);
    ok(ref == 0, "expected data1 ref=0, got %d\n", ref);
    ref = IDataObject_Release(data2);
    ok(ref == 0, "expected data2 ref=0, got %d\n", ref);
    ref = IDataObject_Release(data_cmpl);
    ok(ref == 0, "expected data_cmpl ref=0, got %d\n", ref);

    OleUninitialize();
}