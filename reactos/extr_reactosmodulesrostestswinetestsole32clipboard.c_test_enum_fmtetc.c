#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cfFormat; scalar_t__ dwAspect; scalar_t__ lindex; scalar_t__ tymed; int /*<<< orphan*/ * ptd; } ;
typedef  int /*<<< orphan*/  IEnumFORMATETC ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ FORMATETC ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DATADIR_GET ; 
 int /*<<< orphan*/  DATADIR_SET ; 
 scalar_t__ DataObjectImpl_EnumFormatEtc_calls ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IDataObject_EnumFormatEtc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumFORMATETC_Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IEnumFORMATETC_Next (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumFORMATETC_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumFORMATETC_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumFORMATETC_Skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ OleGetClipboard (int /*<<< orphan*/ **) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  dump_fmtetc (TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_enum_fmtetc(IDataObject *src)
{
    HRESULT hr;
    IDataObject *data;
    IEnumFORMATETC *enum_fmt, *src_enum;
    FORMATETC fmt, src_fmt;
    DWORD count = 0;

    hr = OleGetClipboard(&data);
    ok(hr == S_OK, "OleGetClipboard failed with error 0x%08x\n", hr);

    hr = IDataObject_EnumFormatEtc(data, DATADIR_SET, &enum_fmt);
    ok(hr == E_NOTIMPL ||
       broken(hr == E_INVALIDARG), /* win98 (not win98SE) */
       "got %08x\n", hr);

    DataObjectImpl_EnumFormatEtc_calls = 0;
    hr = IDataObject_EnumFormatEtc(data, DATADIR_GET, &enum_fmt);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(DataObjectImpl_EnumFormatEtc_calls == 0, "EnumFormatEtc was called\n");
    if (FAILED(hr))
    {
        skip("EnumFormatEtc failed, skipping tests.\n");
        return;
    }

    if(src) IDataObject_EnumFormatEtc(src, DATADIR_GET, &src_enum);

    while((hr = IEnumFORMATETC_Next(enum_fmt, 1, &fmt, NULL)) == S_OK)
    {
        ok(src != NULL, "shouldn't be here\n");
        hr = IEnumFORMATETC_Next(src_enum, 1, &src_fmt, NULL);
        ok(hr == S_OK, "%d: got %08x\n", count, hr);
        trace("%d: %s\n", count, dump_fmtetc(&fmt));
        ok(fmt.cfFormat == src_fmt.cfFormat, "%d: %04x %04x\n", count, fmt.cfFormat, src_fmt.cfFormat);
        ok(fmt.dwAspect == src_fmt.dwAspect, "%d: %08x %08x\n", count, fmt.dwAspect, src_fmt.dwAspect);
        ok(fmt.lindex == src_fmt.lindex, "%d: %08x %08x\n", count, fmt.lindex, src_fmt.lindex);
        ok(fmt.tymed == src_fmt.tymed, "%d: %08x %08x\n", count, fmt.tymed, src_fmt.tymed);
        if(fmt.ptd)
        {
            ok(src_fmt.ptd != NULL, "%d: expected non-NULL\n", count);
            CoTaskMemFree(fmt.ptd);
            CoTaskMemFree(src_fmt.ptd);
        }
        count++;
    }

    ok(hr == S_FALSE, "%d: got %08x\n", count, hr);

    if(src)
    {
        hr = IEnumFORMATETC_Next(src_enum, 1, &src_fmt, NULL);
        ok(hr == S_FALSE, "%d: got %08x\n", count, hr);
        IEnumFORMATETC_Release(src_enum);
    }

    hr = IEnumFORMATETC_Reset(enum_fmt);
    ok(hr == S_OK, "got %08x\n", hr);

    if(src) /* Exercise the enumerator a bit */
    {
        IEnumFORMATETC *clone;
        FORMATETC third_fmt;

        hr = IEnumFORMATETC_Next(enum_fmt, 1, &third_fmt, NULL);
        ok(hr == S_OK, "got %08x\n", hr);
        hr = IEnumFORMATETC_Next(enum_fmt, 1, &third_fmt, NULL);
        ok(hr == S_OK, "got %08x\n", hr);
        hr = IEnumFORMATETC_Next(enum_fmt, 1, &third_fmt, NULL);
        ok(hr == S_OK, "got %08x\n", hr);

        hr = IEnumFORMATETC_Reset(enum_fmt);
        ok(hr == S_OK, "got %08x\n", hr);
        hr = IEnumFORMATETC_Skip(enum_fmt, 2);
        ok(hr == S_OK, "got %08x\n", hr);

        hr = IEnumFORMATETC_Clone(enum_fmt, &clone);
        ok(hr == S_OK, "got %08x\n", hr);
        hr = IEnumFORMATETC_Next(enum_fmt, 1, &fmt, NULL);
        ok(hr == S_OK, "got %08x\n", hr);
        ok(fmt.cfFormat == third_fmt.cfFormat, "formats don't match\n");
        hr = IEnumFORMATETC_Next(clone, 1, &fmt, NULL);
        ok(hr == S_OK, "got %08x\n", hr);
        ok(fmt.cfFormat == third_fmt.cfFormat, "formats don't match\n");
        IEnumFORMATETC_Release(clone);
    }

    IEnumFORMATETC_Release(enum_fmt);
    IDataObject_Release(data);
}