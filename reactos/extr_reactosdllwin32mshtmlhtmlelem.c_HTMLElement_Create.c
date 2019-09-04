#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* constructor ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**) ;} ;
typedef  TYPE_2__ tag_desc_t ;
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsAString ;
struct TYPE_11__ {int /*<<< orphan*/ * vtbl; } ;
struct TYPE_13__ {TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  TYPE_3__ HTMLElement ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLElementImplVtbl ; 
 int /*<<< orphan*/  HTMLElement_Init (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTMLElement_dispex ; 
 int /*<<< orphan*/  HTMLGenericElement_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLElement ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 TYPE_2__* get_tag_desc (int /*<<< orphan*/  const*) ; 
 TYPE_3__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_GetTagName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**) ; 

HRESULT HTMLElement_Create(HTMLDocumentNode *doc, nsIDOMNode *nsnode, BOOL use_generic, HTMLElement **ret)
{
    nsIDOMHTMLElement *nselem;
    nsAString class_name_str;
    const PRUnichar *class_name;
    const tag_desc_t *tag;
    HTMLElement *elem;
    nsresult nsres;
    HRESULT hres;

    nsres = nsIDOMNode_QueryInterface(nsnode, &IID_nsIDOMHTMLElement, (void**)&nselem);
    if(NS_FAILED(nsres))
        return E_FAIL;

    nsAString_Init(&class_name_str, NULL);
    nsIDOMHTMLElement_GetTagName(nselem, &class_name_str);

    nsAString_GetData(&class_name_str, &class_name);

    tag = get_tag_desc(class_name);
    if(tag) {
        hres = tag->constructor(doc, nselem, &elem);
    }else if(use_generic) {
        hres = HTMLGenericElement_Create(doc, nselem, &elem);
    }else {
        elem = heap_alloc_zero(sizeof(HTMLElement));
        if(elem) {
            elem->node.vtbl = &HTMLElementImplVtbl;
            HTMLElement_Init(elem, doc, nselem, &HTMLElement_dispex);
            hres = S_OK;
        }else {
            hres = E_OUTOFMEMORY;
        }
    }

    TRACE("%s ret %p\n", debugstr_w(class_name), elem);

    nsIDOMHTMLElement_Release(nselem);
    nsAString_Finish(&class_name_str);
    if(FAILED(hres))
        return hres;

    *ret = elem;
    return S_OK;
}