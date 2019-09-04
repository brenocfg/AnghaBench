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
struct TYPE_3__ {int int_refs; int total_refs; int /*<<< orphan*/  entry; int /*<<< orphan*/  gdiFont; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ HFONTItem ;
typedef  int /*<<< orphan*/  HFONT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OLEFontImpl_csHFONTLIST ; 
 int /*<<< orphan*/  OLEFontImpl_hFontList ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT add_hfontitem(HFONT hfont)
{
    HFONTItem *new_item = HeapAlloc(GetProcessHeap(), 0, sizeof(*new_item));

    if(!new_item) return E_OUTOFMEMORY;

    new_item->int_refs = 1;
    new_item->total_refs = 1;
    new_item->gdiFont = hfont;
    EnterCriticalSection(&OLEFontImpl_csHFONTLIST);
    list_add_tail(&OLEFontImpl_hFontList,&new_item->entry);
    LeaveCriticalSection(&OLEFontImpl_csHFONTLIST);
    return S_OK;
}