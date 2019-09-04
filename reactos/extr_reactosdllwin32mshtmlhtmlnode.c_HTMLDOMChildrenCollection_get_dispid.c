#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  int UINT32 ;
struct TYPE_3__ {int /*<<< orphan*/  nslist; } ;
typedef  TYPE_1__ HTMLDOMChildrenCollection ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DispatchEx ;
typedef  int DWORD ;
typedef  scalar_t__ DISPID ;
typedef  int* BSTR ;

/* Variables and functions */
 scalar_t__ DISPID_CHILDCOL_0 ; 
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 TYPE_1__* impl_from_DispatchEx (int /*<<< orphan*/ *) ; 
 scalar_t__ isdigitW (int) ; 
 int /*<<< orphan*/  nsIDOMNodeList_GetLength (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static HRESULT HTMLDOMChildrenCollection_get_dispid(DispatchEx *dispex, BSTR name, DWORD flags, DISPID *dispid)
{
    HTMLDOMChildrenCollection *This = impl_from_DispatchEx(dispex);
    WCHAR *ptr;
    DWORD idx=0;
    UINT32 len = 0;

    for(ptr = name; *ptr && isdigitW(*ptr); ptr++)
        idx = idx*10 + (*ptr-'0');
    if(*ptr)
        return DISP_E_UNKNOWNNAME;

    nsIDOMNodeList_GetLength(This->nslist, &len);
    if(idx >= len)
        return DISP_E_UNKNOWNNAME;

    *dispid = DISPID_CHILDCOL_0 + idx;
    TRACE("ret %x\n", *dispid);
    return S_OK;
}