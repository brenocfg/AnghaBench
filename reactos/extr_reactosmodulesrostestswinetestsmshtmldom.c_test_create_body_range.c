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
typedef  int /*<<< orphan*/  IHTMLTxtRange ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IHTMLBodyElement ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLBodyElement_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLBodyElement_createTextRange (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLBodyElement ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * doc_get_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static IHTMLTxtRange *test_create_body_range(IHTMLDocument2 *doc)
{
    IHTMLBodyElement *body;
    IHTMLTxtRange *range;
    IHTMLElement *elem;
    HRESULT hres;

    elem = doc_get_body(doc);
    hres = IHTMLElement_QueryInterface(elem, &IID_IHTMLBodyElement, (void**)&body);
    ok(hres == S_OK, "QueryInterface failed: %08x\n", hres);
    IHTMLElement_Release(elem);

    hres = IHTMLBodyElement_createTextRange(body, &range);
    IHTMLBodyElement_Release(body);
    ok(hres == S_OK, "createTextRange failed: %08x\n", hres);

    return range;
}