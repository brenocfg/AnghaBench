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
struct TYPE_5__ {int /*<<< orphan*/  IBaseFilter_iface; } ;
struct TYPE_7__ {TYPE_1__ filter; } ;
struct TYPE_6__ {TYPE_3__ Parser; int /*<<< orphan*/ * oldindex; int /*<<< orphan*/ * streams; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ AVISplitterImpl ;

/* Variables and functions */
 int /*<<< orphan*/  AVISplitterImpl_Vtbl ; 
 int /*<<< orphan*/  AVISplitter_Disconnect ; 
 int /*<<< orphan*/  AVISplitter_Flush ; 
 int /*<<< orphan*/  AVISplitter_InputPin_PreConnect ; 
 int /*<<< orphan*/  AVISplitter_QueryAccept ; 
 int /*<<< orphan*/  AVISplitter_Sample ; 
 int /*<<< orphan*/  AVISplitter_done_process ; 
 int /*<<< orphan*/  AVISplitter_first_request ; 
 int /*<<< orphan*/  AVISplitter_seek ; 
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSID_AviSplitter ; 
 TYPE_2__* CoTaskMemAlloc (int) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Parser_Create (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

HRESULT AVISplitter_create(IUnknown * pUnkOuter, LPVOID * ppv)
{
    HRESULT hr;
    AVISplitterImpl * This;

    TRACE("(%p, %p)\n", pUnkOuter, ppv);

    *ppv = NULL;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    /* Note: This memory is managed by the transform filter once created */
    This = CoTaskMemAlloc(sizeof(AVISplitterImpl));

    This->streams = NULL;
    This->oldindex = NULL;

    hr = Parser_Create(&(This->Parser), &AVISplitterImpl_Vtbl, &CLSID_AviSplitter, AVISplitter_Sample, AVISplitter_QueryAccept, AVISplitter_InputPin_PreConnect, AVISplitter_Flush, AVISplitter_Disconnect, AVISplitter_first_request, AVISplitter_done_process, NULL, AVISplitter_seek, NULL);

    if (FAILED(hr))
        return hr;

    *ppv = &This->Parser.filter.IBaseFilter_iface;

    return hr;
}