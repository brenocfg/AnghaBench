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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLWindow2 ;
typedef  int /*<<< orphan*/  IHTMLFrameBase2 ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLFrameBase2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLFrameBase2_get_contentWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IHTMLFrameBase2 ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static IHTMLWindow2 *_get_frame_content_window(unsigned line, IUnknown *elem)
{
    IHTMLFrameBase2 *base2;
    IHTMLWindow2 *window;
    HRESULT hres;

    hres = IUnknown_QueryInterface(elem, &IID_IHTMLFrameBase2, (void**)&base2);
    ok(hres == S_OK, "Could not get IHTMFrameBase2 iface: %08x\n", hres);

    window = NULL;
    hres = IHTMLFrameBase2_get_contentWindow(base2, &window);
    IHTMLFrameBase2_Release(base2);
    ok(hres == S_OK, "get_contentWindow failed: %08x\n", hres);
    ok(window != NULL, "contentWindow = NULL\n");

    return window;
}