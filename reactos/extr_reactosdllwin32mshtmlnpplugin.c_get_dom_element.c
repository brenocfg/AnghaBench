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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
typedef  int /*<<< orphan*/  nsIPluginInstance ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsIDOMElement ;
struct TYPE_3__ {scalar_t__ ndata; } ;
typedef  TYPE_1__* NPP ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLElement ; 
 int /*<<< orphan*/  IID_nsIPluginInstance ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIDOMElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIPluginInstance_GetDOMElement (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIPluginInstance_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsISupports_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static nsIDOMHTMLElement *get_dom_element(NPP instance)
{
    nsISupports *instance_unk = (nsISupports*)instance->ndata;
    nsIPluginInstance *plugin_instance;
    nsIDOMHTMLElement *html_elem;
    nsIDOMElement *elem;
    nsresult nsres;

    nsres = nsISupports_QueryInterface(instance_unk, &IID_nsIPluginInstance, (void**)&plugin_instance);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIPluginInstance interface: %08x\n", nsres);
        return NULL;
    }

    nsres = nsIPluginInstance_GetDOMElement(plugin_instance, &elem);
    nsIPluginInstance_Release(plugin_instance);
    if(NS_FAILED(nsres)) {
        ERR("GetDOMElement failed: %08x\n", nsres);
        return NULL;
    }

    nsres = nsIDOMElement_QueryInterface(elem, &IID_nsIDOMHTMLElement, (void**)&html_elem);
    nsIDOMElement_Release(elem);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDOMHTMLElement iface: %08x\n", nsres);
        return NULL;
    }

    return html_elem;
}