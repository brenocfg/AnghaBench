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
typedef  scalar_t__ eventid_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HTMLDocumentNode ;
typedef  int /*<<< orphan*/  EventTarget ;

/* Variables and functions */
 scalar_t__ EVENTID_LAST ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ attr_to_eid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  set_event_handler_disp (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

void bind_target_event(HTMLDocumentNode *doc, EventTarget *event_target, const WCHAR *event, IDispatch *disp)
{
    eventid_t eid;

    TRACE("(%p %p %s %p)\n", doc, event_target, debugstr_w(event), disp);

    eid = attr_to_eid(event);
    if(eid == EVENTID_LAST) {
        WARN("Unsupported event %s\n", debugstr_w(event));
        return;
    }

    set_event_handler_disp(event_target, eid, disp);
}