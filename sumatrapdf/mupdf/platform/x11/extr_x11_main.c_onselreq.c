#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  atomlist ;
struct TYPE_4__ {scalar_t__ property; int /*<<< orphan*/  time; scalar_t__ target; scalar_t__ selection; int /*<<< orphan*/  requestor; int /*<<< orphan*/  display; int /*<<< orphan*/  send_event; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ xselection; } ;
typedef  TYPE_2__ XEvent ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Time ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  SelectionNotify ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ XA_STRING ; 
 scalar_t__ XA_TARGETS ; 
 scalar_t__ XA_TIMESTAMP ; 
 scalar_t__ XA_UTF8_STRING ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ advance_scheduled ; 
 scalar_t__ copylatin1 ; 
 scalar_t__ copyutf8 ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  xdpy ; 

__attribute__((used)) static void onselreq(Window requestor, Atom selection, Atom target, Atom property, Time time)
{
	XEvent nevt;

	advance_scheduled = 0;

	if (property == None)
		property = target;

	nevt.xselection.type = SelectionNotify;
	nevt.xselection.send_event = True;
	nevt.xselection.display = xdpy;
	nevt.xselection.requestor = requestor;
	nevt.xselection.selection = selection;
	nevt.xselection.target = target;
	nevt.xselection.property = property;
	nevt.xselection.time = time;

	if (target == XA_TARGETS)
	{
		Atom atomlist[4];
		atomlist[0] = XA_TARGETS;
		atomlist[1] = XA_TIMESTAMP;
		atomlist[2] = XA_STRING;
		atomlist[3] = XA_UTF8_STRING;
		XChangeProperty(xdpy, requestor, property, target,
			32, PropModeReplace,
			(unsigned char *)atomlist, sizeof(atomlist)/sizeof(Atom));
	}

	else if (target == XA_STRING)
	{
		XChangeProperty(xdpy, requestor, property, target,
			8, PropModeReplace,
			(unsigned char *)copylatin1, strlen(copylatin1));
	}

	else if (target == XA_UTF8_STRING)
	{
		XChangeProperty(xdpy, requestor, property, target,
			8, PropModeReplace,
			(unsigned char *)copyutf8, strlen(copyutf8));
	}

	else
	{
		nevt.xselection.property = None;
	}

	XSendEvent(xdpy, requestor, False, 0, &nevt);
}