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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMDocument ;
struct TYPE_5__ {int /*<<< orphan*/  nsframe; } ;
struct TYPE_4__ {TYPE_2__ framebase; } ;
typedef  TYPE_1__ HTMLFrameElement ;
typedef  int /*<<< orphan*/  HTMLDOMNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 TYPE_1__* impl_from_HTMLDOMNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLFrameElement_GetContentDocument (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_frame_doc (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT HTMLFrameElement_bind_to_tree(HTMLDOMNode *iface)
{
    HTMLFrameElement *This = impl_from_HTMLDOMNode(iface);
    nsIDOMDocument *nsdoc;
    nsresult nsres;
    HRESULT hres;

    nsres = nsIDOMHTMLFrameElement_GetContentDocument(This->framebase.nsframe, &nsdoc);
    if(NS_FAILED(nsres) || !nsdoc) {
        ERR("GetContentDocument failed: %08x\n", nsres);
        return E_FAIL;
    }

    hres = set_frame_doc(&This->framebase, nsdoc);
    nsIDOMDocument_Release(nsdoc);
    return hres;
}