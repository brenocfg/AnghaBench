#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsIDOMNode ;
typedef  int /*<<< orphan*/  nsIDOMHTMLElement ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {TYPE_2__* doc; } ;
struct TYPE_7__ {TYPE_1__ node; int /*<<< orphan*/  nsdoc; } ;
typedef  int /*<<< orphan*/  HTMLElement ;
typedef  TYPE_2__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLElement_Create (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  create_nselem (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMHTMLElement_Release (int /*<<< orphan*/ *) ; 

HRESULT create_element(HTMLDocumentNode *doc, const WCHAR *tag, HTMLElement **ret)
{
    nsIDOMHTMLElement *nselem;
    HRESULT hres;

    /* Use owner doc if called on document fragment */
    if(!doc->nsdoc)
        doc = doc->node.doc;

    hres = create_nselem(doc, tag, &nselem);
    if(FAILED(hres))
        return hres;

    hres = HTMLElement_Create(doc, (nsIDOMNode*)nselem, TRUE, ret);
    nsIDOMHTMLElement_Release(nselem);
    return hres;
}