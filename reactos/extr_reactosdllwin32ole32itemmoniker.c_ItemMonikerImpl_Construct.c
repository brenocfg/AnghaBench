#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {void* itemDelimiter; void* itemName; int /*<<< orphan*/ * pMarshal; scalar_t__ ref; TYPE_2__ IROTData_iface; TYPE_1__ IMoniker_iface; } ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  int /*<<< orphan*/  const* LPCOLESTR ;
typedef  TYPE_3__ ItemMonikerImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_ItemMonikerImpl ; 
 int /*<<< orphan*/  VT_ROTDataImpl ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lstrcpyW (void*,int /*<<< orphan*/  const*) ; 
 int lstrlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT ItemMonikerImpl_Construct(ItemMonikerImpl* This, LPCOLESTR lpszDelim,LPCOLESTR lpszItem)
{

    int sizeStr1=lstrlenW(lpszItem), sizeStr2;
    static const OLECHAR emptystr[1];
    LPCOLESTR	delim;

    TRACE("(%p,%s,%s)\n",This,debugstr_w(lpszDelim),debugstr_w(lpszItem));

    /* Initialize the virtual function table. */
    This->IMoniker_iface.lpVtbl = &VT_ItemMonikerImpl;
    This->IROTData_iface.lpVtbl = &VT_ROTDataImpl;
    This->ref          = 0;
    This->pMarshal     = NULL;

    This->itemName=HeapAlloc(GetProcessHeap(),0,sizeof(WCHAR)*(sizeStr1+1));
    if (!This->itemName)
	return E_OUTOFMEMORY;
    lstrcpyW(This->itemName,lpszItem);

    if (!lpszDelim)
	FIXME("lpszDelim is NULL. Using empty string which is possibly wrong.\n");

    delim = lpszDelim ? lpszDelim : emptystr;

    sizeStr2=lstrlenW(delim);
    This->itemDelimiter=HeapAlloc(GetProcessHeap(),0,sizeof(WCHAR)*(sizeStr2+1));
    if (!This->itemDelimiter) {
	HeapFree(GetProcessHeap(),0,This->itemName);
	return E_OUTOFMEMORY;
    }
    lstrcpyW(This->itemDelimiter,delim);
    return S_OK;
}