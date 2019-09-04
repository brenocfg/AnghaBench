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
struct TYPE_5__ {int /*<<< orphan*/  marshal_data; int /*<<< orphan*/ * src_data; int /*<<< orphan*/ * cached_enum; } ;
typedef  TYPE_1__ ole_clipbrd ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CoMarshalInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDataObject_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDataObject_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDataObject ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSHCTX_LOCAL ; 
 int /*<<< orphan*/  MSHLFLAGS_TABLESTRONG ; 
 int /*<<< orphan*/  get_clipbrd_window (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_marshal_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_clipboard_formats (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT set_src_dataobject(ole_clipbrd *clipbrd, IDataObject *data)
{
    HRESULT hr;
    HWND wnd;

    if(FAILED(hr = get_clipbrd_window(clipbrd, &wnd))) return hr;

    if(clipbrd->src_data)
    {
        release_marshal_data(clipbrd->marshal_data);

        IDataObject_Release(clipbrd->src_data);
        clipbrd->src_data = NULL;
        HeapFree(GetProcessHeap(), 0, clipbrd->cached_enum);
        clipbrd->cached_enum = NULL;
    }

    if(data)
    {
        IUnknown *unk;

        IDataObject_AddRef(data);
        clipbrd->src_data = data;

        IDataObject_QueryInterface(data, &IID_IUnknown, (void**)&unk);
        hr = CoMarshalInterface(clipbrd->marshal_data, &IID_IDataObject, unk,
                                MSHCTX_LOCAL, NULL, MSHLFLAGS_TABLESTRONG);
        IUnknown_Release(unk); /* Don't hold a ref on IUnknown, we have one on IDataObject. */
        if(FAILED(hr)) return hr;
        hr = set_clipboard_formats(clipbrd, data);
    }
    return hr;
}