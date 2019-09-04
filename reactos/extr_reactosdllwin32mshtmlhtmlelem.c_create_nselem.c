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
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  nsIDOMElement ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  nsdoc; } ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 int /*<<< orphan*/  IID_nsIDOMHTMLElement ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIDOMElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIDOMElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_CreateElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

HRESULT create_nselem(HTMLDocumentNode *doc, const WCHAR *tag, nsIDOMHTMLElement **ret)
{
    nsIDOMElement *nselem;
    nsAString tag_str;
    nsresult nsres;

    if(!doc->nsdoc) {
        WARN("NULL nsdoc\n");
        return E_UNEXPECTED;
    }

    nsAString_InitDepend(&tag_str, tag);
    nsres = nsIDOMHTMLDocument_CreateElement(doc->nsdoc, &tag_str, &nselem);
    nsAString_Finish(&tag_str);
    if(NS_FAILED(nsres)) {
        ERR("CreateElement failed: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIDOMElement_QueryInterface(nselem, &IID_nsIDOMHTMLElement, (void**)ret);
    nsIDOMElement_Release(nselem);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIDOMHTMLElement iface: %08x\n", nsres);
        return E_FAIL;
    }

    return S_OK;
}