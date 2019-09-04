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
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMEvent ;
typedef  int /*<<< orphan*/  eventid_t ;
struct TYPE_5__ {int /*<<< orphan*/  IHTMLEventObj_iface; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_1__ HTMLEventObj ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IHTMLEventObj_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* create_event () ; 
 int /*<<< orphan*/  fire_event_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  node_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_event_info (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fire_event(HTMLDocumentNode *doc, eventid_t eid, BOOL set_event, nsIDOMNode *target, nsIDOMEvent *nsevent,
        IDispatch *script_this)
{
    HTMLEventObj *event_obj = NULL;
    HTMLDOMNode *node;
    HRESULT hres;

    if(set_event) {
        hres = get_node(doc, target, TRUE, &node);
        if(FAILED(hres))
            return;

        event_obj = create_event();
        node_release(node);
        if(!event_obj)
            return;

        hres = set_event_info(event_obj, node, eid, nsevent);
        if(FAILED(hres)) {
            IHTMLEventObj_Release(&event_obj->IHTMLEventObj_iface);
            return;
        }
    }

    fire_event_obj(doc, eid, event_obj, target, script_this);

    if(event_obj)
        IHTMLEventObj_Release(&event_obj->IHTMLEventObj_iface);
}