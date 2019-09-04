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
typedef  int /*<<< orphan*/  IHTMLElement2 ;
typedef  int /*<<< orphan*/  IHTMLElement ;
typedef  int /*<<< orphan*/  IHTMLCurrentStyle ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLElement2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLElement2_get_currentStyle (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IHTMLElement2 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static IHTMLCurrentStyle *_get_current_style(unsigned line, IHTMLElement *elem)
{
    IHTMLCurrentStyle *cstyle;
    IHTMLElement2 *elem2;
    HRESULT hres;

    hres = IHTMLElement_QueryInterface(elem, &IID_IHTMLElement2, (void**)&elem2);
    ok(hres == S_OK, "Could not get IHTMLElement2 iface: %08x\n", hres);

    cstyle = NULL;
    hres = IHTMLElement2_get_currentStyle(elem2, &cstyle);
    ok(hres == S_OK, "get_currentStyle failed: %08x\n", hres);
    ok(cstyle != NULL, "cstyle = %p\n", cstyle);

    IHTMLElement2_Release(elem2);
    return cstyle;
}