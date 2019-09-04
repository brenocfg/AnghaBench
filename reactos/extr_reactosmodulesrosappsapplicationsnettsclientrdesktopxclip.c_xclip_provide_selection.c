#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_9__ {scalar_t__ requestor; int /*<<< orphan*/  time; int /*<<< orphan*/  property; int /*<<< orphan*/  target; int /*<<< orphan*/  selection; } ;
typedef  TYPE_2__ XSelectionRequestEvent ;
struct TYPE_8__ {int /*<<< orphan*/  time; int /*<<< orphan*/  property; int /*<<< orphan*/  target; int /*<<< orphan*/  selection; scalar_t__ requestor; int /*<<< orphan*/  send_event; scalar_t__ serial; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_1__ xselection; } ;
typedef  TYPE_3__ XEvent ;
struct TYPE_11__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_4__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_CLIPBOARD (char*) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  NoEventMask ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  SelectionNotify ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  XGetAtomName (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
xclip_provide_selection(RDPCLIENT * This, XSelectionRequestEvent * req, Atom type, unsigned int format, uint8 * data,
			uint32 length)
{
	XEvent xev;

	DEBUG_CLIPBOARD(("xclip_provide_selection: requestor=0x%08x, target=%s, property=%s, length=%u\n", (unsigned) req->requestor, XGetAtomName(This->display, req->target), XGetAtomName(This->display, req->property), (unsigned) length));

	XChangeProperty(This->display, req->requestor, req->property,
			type, format, PropModeReplace, data, length);

	xev.xselection.type = SelectionNotify;
	xev.xselection.serial = 0;
	xev.xselection.send_event = True;
	xev.xselection.requestor = req->requestor;
	xev.xselection.selection = req->selection;
	xev.xselection.target = req->target;
	xev.xselection.property = req->property;
	xev.xselection.time = req->time;
	XSendEvent(This->display, req->requestor, False, NoEventMask, &xev);
}