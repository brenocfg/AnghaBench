#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  size_t eventid_t ;
typedef  int UINT16 ;
struct TYPE_25__ {int /*<<< orphan*/  IHTMLDocument2_iface; int /*<<< orphan*/  cp_container; } ;
struct TYPE_24__ {TYPE_2__* vtbl; int /*<<< orphan*/  IHTMLDOMNode_iface; int /*<<< orphan*/ * cp_container; int /*<<< orphan*/  event_target; } ;
struct TYPE_19__ {int /*<<< orphan*/  event_target; } ;
struct TYPE_23__ {TYPE_9__ basedoc; TYPE_1__ node; int /*<<< orphan*/  nsdoc; TYPE_3__* window; } ;
struct TYPE_22__ {int /*<<< orphan*/ * nsevent; scalar_t__ cancel_bubble; scalar_t__ prevent_default; int /*<<< orphan*/  IHTMLEventObj_iface; } ;
struct TYPE_21__ {int /*<<< orphan*/ * event; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* handle_event ) (TYPE_6__*,size_t,int /*<<< orphan*/ *,scalar_t__*) ;} ;
struct TYPE_18__ {int flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  IHTMLEventObj ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_3__ HTMLInnerWindow ;
typedef  TYPE_4__ HTMLEventObj ;
typedef  TYPE_5__ HTMLDocumentNode ;
typedef  TYPE_6__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
#define  DOCUMENT_NODE 129 
#define  ELEMENT_NODE 128 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int EVENT_BUBBLE ; 
 int EVENT_FORWARDBODY ; 
 int EVENT_HASDEFAULTHANDLERS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  call_event_handlers (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 TYPE_15__* event_info ; 
 int /*<<< orphan*/  get_node (TYPE_5__*,int /*<<< orphan*/ *,scalar_t__,TYPE_6__**) ; 
 int /*<<< orphan*/  htmldoc_addref (TYPE_9__*) ; 
 int /*<<< orphan*/  htmldoc_release (TYPE_9__*) ; 
 int /*<<< orphan*/  node_release (TYPE_6__*) ; 
 int /*<<< orphan*/  nsIDOMEvent_PreventDefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_GetBody (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_GetNodeType (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nsIDOMNode_GetParentNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,size_t,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void fire_event_obj(HTMLDocumentNode *doc, eventid_t eid, HTMLEventObj *event_obj,
        nsIDOMNode *target, IDispatch *script_this)
{
    IHTMLEventObj *prev_event;
    nsIDOMNode *parent, *nsnode;
    BOOL prevent_default = FALSE;
    HTMLInnerWindow *window;
    HTMLDOMNode *node;
    UINT16 node_type;
    nsresult nsres;
    HRESULT hres;

    TRACE("(%p) %s\n", doc, debugstr_w(event_info[eid].name));

    window = doc->window;
    if(!window) {
        WARN("NULL window\n");
        return;
    }

    htmldoc_addref(&doc->basedoc);

    prev_event = window->event;
    window->event = event_obj ? &event_obj->IHTMLEventObj_iface : NULL;

    nsIDOMNode_GetNodeType(target, &node_type);
    nsnode = target;
    nsIDOMNode_AddRef(nsnode);

    switch(node_type) {
    case ELEMENT_NODE:
        do {
            hres = get_node(doc, nsnode, FALSE, &node);
            if(SUCCEEDED(hres) && node) {
                call_event_handlers(doc, event_obj, &node->event_target, node->cp_container, eid,
                        script_this ? script_this : (IDispatch*)&node->IHTMLDOMNode_iface);
                node_release(node);
            }

            if(!(event_info[eid].flags & EVENT_BUBBLE) || (event_obj && event_obj->cancel_bubble))
                break;

            nsIDOMNode_GetParentNode(nsnode, &parent);
            nsIDOMNode_Release(nsnode);
            nsnode = parent;
            if(!nsnode)
                break;

            nsIDOMNode_GetNodeType(nsnode, &node_type);
        }while(node_type == ELEMENT_NODE);

        if(!(event_info[eid].flags & EVENT_BUBBLE) || (event_obj && event_obj->cancel_bubble))
            break;

    case DOCUMENT_NODE:
        if(event_info[eid].flags & EVENT_FORWARDBODY) {
            nsIDOMHTMLElement *nsbody;
            nsresult nsres;

            nsres = nsIDOMHTMLDocument_GetBody(doc->nsdoc, &nsbody);
            if(NS_SUCCEEDED(nsres) && nsbody) {
                hres = get_node(doc, (nsIDOMNode*)nsbody, FALSE, &node);
                if(SUCCEEDED(hres) && node) {
                    call_event_handlers(doc, event_obj, &node->event_target, node->cp_container, eid,
                            script_this ? script_this : (IDispatch*)&node->IHTMLDOMNode_iface);
                    node_release(node);
                }
                nsIDOMHTMLElement_Release(nsbody);
            }else {
                ERR("Could not get body: %08x\n", nsres);
            }
        }

        call_event_handlers(doc, event_obj, &doc->node.event_target, &doc->basedoc.cp_container, eid,
                script_this ? script_this : (IDispatch*)&doc->basedoc.IHTMLDocument2_iface);
        break;

    default:
        FIXME("unimplemented node type %d\n", node_type);
    }

    if(nsnode)
        nsIDOMNode_Release(nsnode);

    if(event_obj && event_obj->prevent_default)
        prevent_default = TRUE;
    window->event = prev_event;

    if(!prevent_default && (event_info[eid].flags & EVENT_HASDEFAULTHANDLERS)) {
        nsIDOMNode_AddRef(target);
        nsnode = target;

        do {
            hres = get_node(doc, nsnode, TRUE, &node);
            if(FAILED(hres))
                break;

            if(node) {
                if(node->vtbl->handle_event)
                    hres = node->vtbl->handle_event(node, eid, event_obj ? event_obj->nsevent : NULL, &prevent_default);
                node_release(node);
                if(FAILED(hres) || prevent_default || (event_obj && event_obj->cancel_bubble))
                    break;
            }

            nsres = nsIDOMNode_GetParentNode(nsnode, &parent);
            if(NS_FAILED(nsres))
                break;

            nsIDOMNode_Release(nsnode);
            nsnode = parent;
        } while(nsnode);

        if(nsnode)
            nsIDOMNode_Release(nsnode);
    }

    if(prevent_default && event_obj && event_obj->nsevent) {
        TRACE("calling PreventDefault\n");
        nsIDOMEvent_PreventDefault(event_obj->nsevent);
    }

    htmldoc_release(&doc->basedoc);
}