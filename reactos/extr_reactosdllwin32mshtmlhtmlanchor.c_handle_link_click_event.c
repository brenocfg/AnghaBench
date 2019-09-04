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
typedef  scalar_t__ nsresult ;
typedef  int /*<<< orphan*/  nsIDOMMouseEvent ;
typedef  int /*<<< orphan*/  nsIDOMEvent ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  int INT16 ;
typedef  int /*<<< orphan*/  HTMLElement ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_nsIDOMMouseEvent ; 
 scalar_t__ NS_OK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  navigate_href (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  navigate_href_new_window (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 scalar_t__ nsIDOMEvent_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ nsIDOMMouseEvent_GetButton (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nsIDOMMouseEvent_Release (int /*<<< orphan*/ *) ; 

HRESULT handle_link_click_event(HTMLElement *element, nsAString *href_str, nsAString *target_str,
                                nsIDOMEvent *event, BOOL *prevent_default)
{
    nsIDOMMouseEvent *mouse_event;
    INT16 button;
    nsresult nsres;
    HRESULT hres;

    TRACE("CLICK\n");

    nsres = nsIDOMEvent_QueryInterface(event, &IID_nsIDOMMouseEvent, (void**)&mouse_event);
    assert(nsres == NS_OK);

    nsres = nsIDOMMouseEvent_GetButton(mouse_event, &button);
    assert(nsres == NS_OK);

    nsIDOMMouseEvent_Release(mouse_event);

    switch(button) {
    case 0:
        *prevent_default = TRUE;
        hres = navigate_href(element, href_str, target_str);
        break;
    case 1:
        *prevent_default = TRUE;
        hres = navigate_href_new_window(element, href_str, NULL);
        break;
    default:
        *prevent_default = FALSE;
        hres = S_OK;
    }

    nsAString_Finish(href_str);
    nsAString_Finish(target_str);
    return hres;
}