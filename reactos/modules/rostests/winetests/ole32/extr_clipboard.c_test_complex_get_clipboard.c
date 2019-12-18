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
typedef  int /*<<< orphan*/  STGMEDIUM ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  FORMATETC ;

/* Variables and functions */
 int /*<<< orphan*/  CF_ENHMETAFILE ; 
 int /*<<< orphan*/  CF_METAFILEPICT ; 
 scalar_t__ DV_E_TYMED ; 
 int DataObjectImpl_GetData_calls ; 
 scalar_t__ IDataObject_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitFormatEtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OleGetClipboard (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ReleaseStgMedium (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TYMED_ENHMF ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 int /*<<< orphan*/  TYMED_MFPICT ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_complex_get_clipboard(void)
{
    HRESULT hr;
    IDataObject *data_obj;
    FORMATETC fmtetc;
    STGMEDIUM stgmedium;

    hr = OleGetClipboard(&data_obj);
    ok(hr == S_OK, "OleGetClipboard failed with error 0x%08x\n", hr);

    DataObjectImpl_GetData_calls = 0;

    InitFormatEtc(fmtetc, CF_METAFILEPICT, TYMED_MFPICT);
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == S_OK, "IDataObject_GetData failed with error 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    InitFormatEtc(fmtetc, CF_METAFILEPICT, TYMED_HGLOBAL);
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == DV_E_TYMED, "IDataObject_GetData failed with error 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    InitFormatEtc(fmtetc, CF_ENHMETAFILE, TYMED_HGLOBAL);
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == DV_E_TYMED, "IDataObject_GetData failed with error 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    InitFormatEtc(fmtetc, CF_ENHMETAFILE, TYMED_ENHMF);
    hr = IDataObject_GetData(data_obj, &fmtetc, &stgmedium);
    ok(hr == S_OK, "IDataObject_GetData failed with error 0x%08x\n", hr);
    if(SUCCEEDED(hr)) ReleaseStgMedium(&stgmedium);

    ok(DataObjectImpl_GetData_calls == 5,
            "DataObjectImpl_GetData called 5 times instead of %d times\n",
            DataObjectImpl_GetData_calls);
    IDataObject_Release(data_obj);
}