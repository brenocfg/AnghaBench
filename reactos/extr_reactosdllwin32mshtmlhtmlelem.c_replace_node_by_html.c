#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMRange ;
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLDocument ;
typedef  int /*<<< orphan*/  nsIDOMDocumentFragment ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_InitDepend (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nsIDOMDocumentFragment_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMHTMLDocument_CreateRange (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_GetParentNode (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMNode_ReplaceChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMRange_CreateContextualFragment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMRange_Release (int /*<<< orphan*/ *) ; 

HRESULT replace_node_by_html(nsIDOMHTMLDocument *nsdoc, nsIDOMNode *nsnode, const WCHAR *html)
{
    nsIDOMDocumentFragment *nsfragment;
    nsIDOMNode *nsparent;
    nsIDOMRange *range;
    nsAString html_str;
    nsresult nsres;
    HRESULT hres = S_OK;

    nsres = nsIDOMHTMLDocument_CreateRange(nsdoc, &range);
    if(NS_FAILED(nsres)) {
        ERR("CreateRange failed: %08x\n", nsres);
        return E_FAIL;
    }

    nsAString_InitDepend(&html_str, html);
    nsIDOMRange_CreateContextualFragment(range, &html_str, &nsfragment);
    nsIDOMRange_Release(range);
    nsAString_Finish(&html_str);
    if(NS_FAILED(nsres)) {
        ERR("CreateContextualFragment failed: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIDOMNode_GetParentNode(nsnode, &nsparent);
    if(NS_SUCCEEDED(nsres) && nsparent) {
        nsIDOMNode *nstmp;

        nsres = nsIDOMNode_ReplaceChild(nsparent, (nsIDOMNode*)nsfragment, nsnode, &nstmp);
        nsIDOMNode_Release(nsparent);
        if(NS_FAILED(nsres)) {
            ERR("ReplaceChild failed: %08x\n", nsres);
            hres = E_FAIL;
        }else if(nstmp) {
            nsIDOMNode_Release(nstmp);
        }
    }else {
        ERR("GetParentNode failed: %08x\n", nsres);
        hres = E_FAIL;
    }

    nsIDOMDocumentFragment_Release(nsfragment);
    return hres;
}