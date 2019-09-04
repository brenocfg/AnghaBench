#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMWindow ;
typedef  int /*<<< orphan*/  nsIDOMDocument ;
struct TYPE_12__ {TYPE_2__* doc; } ;
struct TYPE_13__ {TYPE_3__ node; } ;
struct TYPE_15__ {TYPE_5__* content_window; TYPE_4__ element; } ;
struct TYPE_14__ {TYPE_6__* frame_element; } ;
struct TYPE_10__ {int /*<<< orphan*/  window; int /*<<< orphan*/  doc_obj; } ;
struct TYPE_11__ {TYPE_1__ basedoc; } ;
typedef  TYPE_5__ HTMLOuterWindow ;
typedef  TYPE_6__ HTMLFrameBase ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLOuterWindow_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__**) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  nsIDOMDocument_GetDefaultView (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nsIDOMWindow_Release (int /*<<< orphan*/ *) ; 
 TYPE_5__* nswindow_to_window (int /*<<< orphan*/ *) ; 

HRESULT set_frame_doc(HTMLFrameBase *frame, nsIDOMDocument *nsdoc)
{
    nsIDOMWindow *nswindow;
    HTMLOuterWindow *window;
    nsresult nsres;
    HRESULT hres = S_OK;

    if(frame->content_window)
        return S_OK;

    nsres = nsIDOMDocument_GetDefaultView(nsdoc, &nswindow);
    if(NS_FAILED(nsres) || !nswindow)
        return E_FAIL;

    window = nswindow_to_window(nswindow);
    if(!window)
        hres = HTMLOuterWindow_Create(frame->element.node.doc->basedoc.doc_obj, nswindow,
                frame->element.node.doc->basedoc.window, &window);
    nsIDOMWindow_Release(nswindow);
    if(FAILED(hres))
        return hres;

    frame->content_window = window;
    window->frame_element = frame;
    return S_OK;
}