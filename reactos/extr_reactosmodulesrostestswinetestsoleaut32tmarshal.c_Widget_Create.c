#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int refs; TYPE_2__ IWidget_iface; int /*<<< orphan*/ * pDispatchUnknown; } ;
typedef  TYPE_1__ Widget ;
typedef  TYPE_2__ IWidget ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStdDispatch (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IID_IWidget ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Widget_VTable ; 
 int /*<<< orphan*/ * get_type_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_ole_success (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **)) ; 

__attribute__((used)) static IWidget *Widget_Create(void)
{
    Widget *This;
    ITypeInfo *pTypeInfo;
    HRESULT hr = E_FAIL;

    pTypeInfo = get_type_info(&IID_IWidget);
    if(!pTypeInfo)
        return NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    This->IWidget_iface.lpVtbl = &Widget_VTable;
    This->refs = 1;
    This->pDispatchUnknown = NULL;

    hr = CreateStdDispatch((IUnknown *)&This->IWidget_iface, This, pTypeInfo,
                           &This->pDispatchUnknown);
    ok_ole_success(hr, CreateStdDispatch);
    ITypeInfo_Release(pTypeInfo);

    if (SUCCEEDED(hr))
        return &This->IWidget_iface;
    else
    {
        HeapFree(GetProcessHeap(), 0, This);
        return NULL;
    }
}