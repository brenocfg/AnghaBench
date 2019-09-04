#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_10__ {int /*<<< orphan*/  const* attr_name; } ;
struct TYPE_9__ {int /*<<< orphan*/  event_target; } ;
struct TYPE_8__ {int /*<<< orphan*/  window; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  TYPE_2__ HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int EVENTID_LAST ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 TYPE_6__* event_info ; 
 int /*<<< orphan*/  get_elem_attr_value (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  get_node (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  node_release (TYPE_2__*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * script_parse_event (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_event_handler_disp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void check_event_attr(HTMLDocumentNode *doc, nsIDOMHTMLElement *nselem)
{
    const PRUnichar *attr_value;
    nsAString attr_value_str;
    IDispatch *disp;
    HTMLDOMNode *node;
    int i;
    nsresult nsres;
    HRESULT hres;

    for(i=0; i < EVENTID_LAST; i++) {
        nsres = get_elem_attr_value(nselem, event_info[i].attr_name, &attr_value_str, &attr_value);
        if(NS_SUCCEEDED(nsres)) {
            if(!*attr_value)
                continue;

            TRACE("%p.%s = %s\n", nselem, debugstr_w(event_info[i].attr_name), debugstr_w(attr_value));

            disp = script_parse_event(doc->window, attr_value);
            if(disp) {
                hres = get_node(doc, (nsIDOMNode*)nselem, TRUE, &node);
                if(SUCCEEDED(hres)) {
                    set_event_handler_disp(&node->event_target, i, disp);
                    node_release(node);
                }
                IDispatch_Release(disp);
            }
            nsAString_Finish(&attr_value_str);
        }
    }
}