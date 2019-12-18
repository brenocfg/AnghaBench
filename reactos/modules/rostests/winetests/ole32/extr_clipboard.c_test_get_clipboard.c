#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dwAspect; int lindex; } ;
typedef  int /*<<< orphan*/  STGMEDIUM ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ FORMATETC ;

/* Variables and functions */
 int /*<<< orphan*/  CF_RIFF ; 
 int /*<<< orphan*/  CF_TEXT ; 
 void* DVASPECT_THUMBNAIL ; 
 scalar_t__ DV_E_CLIPFORMAT ; 
 scalar_t__ DV_E_FORMATETC ; 
 scalar_t__ DV_E_TYMED ; 
 int DataObjectImpl_GetData_calls ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDataObject_GetData (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IDataObject_QueryGetData (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitFormatEtc (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OleGetClipboard (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ReleaseStgMedium (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TYMED_FILE ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  expect_DataObjectImpl_QueryGetData ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_get_clipboard(void)
{
    HRESULT hr;
    IDataObject *data_obj;
    FORMATETC fmtetc;
    STGMEDIUM stgmedium;

    hr = OleGetClipboard(NULL);
    ok(hr == E_INVALIDARG, "OleGetClipboard(NULL) should return E_INVALIDARG instead of 0x%08x\n", hr);

    hr = OleGetClipboard(&data_obj);
    ok(hr == S_OK, "OleGetClipboard failed with error 0x%08x\n", hr);

    /* test IDataObject_QueryGetData */

    /* clipboard's IDataObject_QueryGetData shouldn't defer to our IDataObject_QueryGetData */
    expect_DataObjectImpl_QueryGetData = FALSE;

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_HGLOBAL);
    hr = IDataObject_QueryGetData(data_obj, &fmtetc);
    ok(hr == S_OK, "IDataObject_QueryGetData failed with error 0x%08x\n", hr);

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_HGLOBAL);
    fmtetc.dwAspect = 0xdeadbeef;
    hr = IDataObject_QueryGetData(data_obj, &fmtetc);
    ok(hr == DV_E_FORMATETC, "IDataObject_QueryGetData should have failed with DV_E_FORMATETC instead of 0x%08x\n", hr);

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_HGLOBAL);
    fmtetc.dwAspect = DVASPECT_THUMBNAIL;
    hr = IDataObject_QueryGetData(data_obj, &fmtetc);
    ok(hr == DV_E_FORMATETC, "IDataObject_QueryGetData should have failed with DV_E_FORMATETC instead of 0x%08x\n", hr);

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_HGLOBAL);
    fmtetc.lindex = 256;
    hr = IDataObject_QueryGetData(data_obj, &fmtetc);
    ok(hr == DV_E_FORMATETC || broken(hr == S_OK),
        "IDataObject_QueryGetData should have failed with DV_E_FORMATETC instead of 0x%08x\n", hr);

    InitFormatEtc(fmtetc, CF_RIFF, TYMED_HGLOBAL);
    hr = IDataObject_QueryGetData(data_obj, &fmtetc);
    ok(hr == DV_E_CLIPFORMAT, "IDataObject_QueryGetData should have failed with DV_E_CLIPFORMAT instead of 0x%08x\n", hr);

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_FILE);
    hr = IDataObject_QueryGetData(data_obj, &fmtetc);
    ok(hr == S_OK, "IDataObject_QueryGetData failed with error 0x%08x\n", hr);

    expect_DataObjectImpl_QueryGetData = TRUE;

    /* test IDataObject_GetData */

    DataObjectImpl_GetData_calls = 0;

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_HGLOBAL);
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == S_OK, "IDataObject_GetData failed with error 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_HGLOBAL);
    fmtetc.dwAspect = 0xdeadbeef;
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == S_OK, "IDataObject_GetData failed with error 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_HGLOBAL);
    fmtetc.dwAspect = DVASPECT_THUMBNAIL;
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == S_OK, "IDataObject_GetData failed with error 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_HGLOBAL);
    fmtetc.lindex = 256;
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == DV_E_FORMATETC || broken(hr == S_OK), "IDataObject_GetData should have failed with DV_E_FORMATETC instead of 0x%08x\n", hr);
    if (hr == S_OK)
    {
        /* undo the unexpected success */
        DataObjectImpl_GetData_calls--;
        ReleaseStgMedium(&stgmedium);
    }

    InitFormatEtc(fmtetc, CF_RIFF, TYMED_HGLOBAL);
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == DV_E_FORMATETC, "IDataObject_GetData should have failed with DV_E_FORMATETC instead of 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    InitFormatEtc(fmtetc, CF_TEXT, TYMED_FILE);
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == DV_E_TYMED, "IDataObject_GetData should have failed with DV_E_TYMED instead of 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    ok(DataObjectImpl_GetData_calls == 6, "DataObjectImpl_GetData should have been called 6 times instead of %d times\n", DataObjectImpl_GetData_calls);

    IDataObject_Release(data_obj);
}