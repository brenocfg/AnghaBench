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
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLIFrameElement ;
typedef  int /*<<< orphan*/  IHTMLFrameBase2 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLFrameBase2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLFrameBase2_get_contentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IHTMLIFrameElement_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLWindow2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLWindow2_get_document (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLFrameBase2 ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static IHTMLDocument2* get_iframe_doc(IHTMLIFrameElement *iframe)
{
    HRESULT hres;
    IHTMLFrameBase2 *base;
    IHTMLDocument2 *result = NULL;

    hres = IHTMLIFrameElement_QueryInterface(iframe, &IID_IHTMLFrameBase2, (void**)&base);
    ok(hres == S_OK, "QueryInterface(IID_IHTMLFrameBase2) failed: %08x\n", hres);
    if(hres == S_OK) {
        IHTMLWindow2 *window;

        hres = IHTMLFrameBase2_get_contentWindow(base, &window);
        ok(hres == S_OK, "get_contentWindow failed: %08x\n", hres);
        ok(window != NULL, "window == NULL\n");
        if(window) {
            hres = IHTMLWindow2_get_document(window, &result);
            ok(hres == S_OK, "get_document failed: %08x\n", hres);
            ok(result != NULL, "result == NULL\n");
            IHTMLWindow2_Release(window);
        }
    }
    if(base) IHTMLFrameBase2_Release(base);

    return result;
}