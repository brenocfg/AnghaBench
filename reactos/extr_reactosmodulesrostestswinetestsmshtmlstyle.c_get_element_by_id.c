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
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static IHTMLElement *get_element_by_id(IHTMLDocument2 *doc, const char *id)
{
    HRESULT hres;
    IHTMLDocument3 *doc3;
    IHTMLElement *result;
    BSTR idW = a2bstr(id);

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument3, (void**)&doc3);
    ok(hres == S_OK, "QueryInterface(IID_IHTMLDocument3) failed: %08x\n", hres);

    hres = IHTMLDocument3_getElementById(doc3, idW, &result);
    ok(hres == S_OK, "getElementById failed: %08x\n", hres);
    ok(result != NULL, "result == NULL\n");
    SysFreeString(idW);

    IHTMLDocument3_Release(doc3);
    return result;
}