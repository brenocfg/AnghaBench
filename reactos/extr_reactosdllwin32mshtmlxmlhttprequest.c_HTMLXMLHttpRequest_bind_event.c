#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMEventTarget ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  char WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_2__ nsIDOMEventListener_iface; TYPE_1__* xhr; } ;
struct TYPE_6__ {TYPE_4__* event_listener; int /*<<< orphan*/  nsxhr; } ;
typedef  TYPE_1__ HTMLXMLHttpRequest ;
typedef  int /*<<< orphan*/  DispatchEx ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int EVENTID_READYSTATECHANGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_nsIDOMEventTarget ; 
 scalar_t__ NS_FAILED (scalar_t__) ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XMLHttpReqEventListenerVtbl ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* heap_alloc (int) ; 
 TYPE_1__* impl_from_DispatchEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ nsIDOMEventTarget_AddEventListener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsIDOMEventTarget_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIXMLHttpRequest_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void HTMLXMLHttpRequest_bind_event(DispatchEx *dispex, int eid)
{
    HTMLXMLHttpRequest *This = impl_from_DispatchEx(dispex);
    nsIDOMEventTarget *nstarget;
    nsAString type_str;
    nsresult nsres;

    static const WCHAR readystatechangeW[] = {'r','e','a','d','y','s','t','a','t','e','c','h','a','n','g','e',0};

    TRACE("(%p)\n", This);

    assert(eid == EVENTID_READYSTATECHANGE);

    if(This->event_listener)
        return;

    This->event_listener = heap_alloc(sizeof(*This->event_listener));
    if(!This->event_listener)
        return;

    This->event_listener->nsIDOMEventListener_iface.lpVtbl = &XMLHttpReqEventListenerVtbl;
    This->event_listener->ref = 1;
    This->event_listener->xhr = This;

    nsres = nsIXMLHttpRequest_QueryInterface(This->nsxhr, &IID_nsIDOMEventTarget, (void**)&nstarget);
    assert(nsres == NS_OK);

    nsAString_InitDepend(&type_str, readystatechangeW);
    nsres = nsIDOMEventTarget_AddEventListener(nstarget, &type_str, &This->event_listener->nsIDOMEventListener_iface, FALSE, TRUE, 2);
    nsAString_Finish(&type_str);
    nsIDOMEventTarget_Release(nstarget);
    if(NS_FAILED(nsres))
        ERR("AddEventListener failed: %08x\n", nsres);
}