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
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLDocument3 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument3_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument3_getElementById (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLDocument3 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 

__attribute__((used)) static IHTMLElement *get_doc_elem_by_id(IHTMLDocument2 *doc, const char *id)
{
    IHTMLDocument3 *doc3;
    IHTMLElement *elem;
    BSTR tmp;
    HRESULT hres;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument3, (void**)&doc3);
    ok(hres == S_OK, "Could not get IHTMLDocument3 iface: %08x\n", hres);

    tmp = a2bstr(id);
    hres = IHTMLDocument3_getElementById(doc3, tmp, &elem);
    SysFreeString(tmp);
    ok(hres == S_OK, "getElementById(%s) failed: %08x\n", id, hres);

    IHTMLDocument3_Release(doc3);

    return elem;
}