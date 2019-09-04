#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMEventTarget ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_5__ {int /*<<< orphan*/  nsIDOMEventListener_iface; TYPE_1__* xhr; } ;
typedef  TYPE_2__ XMLHttpReqEventListener ;
typedef  char WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/ * event_listener; int /*<<< orphan*/  nsxhr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_nsIDOMEventTarget ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  nsIDOMEventListener_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMEventTarget_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMEventTarget_RemoveEventListener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nsIXMLHttpRequest_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void detach_xhr_event_listener(XMLHttpReqEventListener *event_listener)
{
    nsIDOMEventTarget *event_target;
    nsAString str;
    nsresult nsres;

    static const WCHAR readystatechangeW[] =
        {'o','n','r','e','a','d','y','s','t','a','t','e','c','h','a','n','g','e',0};

    nsres = nsIXMLHttpRequest_QueryInterface(event_listener->xhr->nsxhr, &IID_nsIDOMEventTarget, (void**)&event_target);
    assert(nsres == NS_OK);

    nsAString_InitDepend(&str, readystatechangeW);
    nsres = nsIDOMEventTarget_RemoveEventListener(event_target, &str, &event_listener->nsIDOMEventListener_iface, FALSE);
    nsAString_Finish(&str);
    nsIDOMEventTarget_Release(event_target);

    event_listener->xhr->event_listener = NULL;
    event_listener->xhr = NULL;
    nsIDOMEventListener_Release(&event_listener->nsIDOMEventListener_iface);
}