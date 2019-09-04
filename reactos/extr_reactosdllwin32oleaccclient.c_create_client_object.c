#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; TYPE_5__ IAccessible_iface; scalar_t__ enum_pos; int /*<<< orphan*/  hwnd; TYPE_2__ IEnumVARIANT_iface; TYPE_1__ IOleWindow_iface; } ;
typedef  int /*<<< orphan*/  IID ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ Client ;

/* Variables and functions */
 int /*<<< orphan*/  ClientEnumVARIANTVtbl ; 
 int /*<<< orphan*/  ClientOleWindowVtbl ; 
 int /*<<< orphan*/  ClientVtbl ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IAccessible_QueryInterface (TYPE_5__*,int /*<<< orphan*/  const*,void**) ; 
 int /*<<< orphan*/  IAccessible_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 TYPE_3__* heap_alloc_zero (int) ; 

HRESULT create_client_object(HWND hwnd, const IID *iid, void **obj)
{
    Client *client;
    HRESULT hres;

    if(!IsWindow(hwnd))
        return E_FAIL;

    client = heap_alloc_zero(sizeof(Client));
    if(!client)
        return E_OUTOFMEMORY;

    client->IAccessible_iface.lpVtbl = &ClientVtbl;
    client->IOleWindow_iface.lpVtbl = &ClientOleWindowVtbl;
    client->IEnumVARIANT_iface.lpVtbl = &ClientEnumVARIANTVtbl;
    client->ref = 1;
    client->hwnd = hwnd;
    client->enum_pos = 0;

    hres = IAccessible_QueryInterface(&client->IAccessible_iface, iid, obj);
    IAccessible_Release(&client->IAccessible_iface);
    return hres;
}