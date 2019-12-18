#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdfapp_t ;
struct TYPE_4__ {int function; } ;
typedef  TYPE_1__ XGCValues ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GCFunction ; 
 int GXxor ; 
 int /*<<< orphan*/  WhitePixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XChangeGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  XDrawString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGetGCValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xdpy ; 
 int /*<<< orphan*/  xgc ; 
 int /*<<< orphan*/  xwin ; 

__attribute__((used)) static void windrawstringxor(pdfapp_t *app, int x, int y, char *s)
{
	int prevfunction;
	XGCValues xgcv;

	XGetGCValues(xdpy, xgc, GCFunction, &xgcv);
	prevfunction = xgcv.function;
	xgcv.function = GXxor;
	XChangeGC(xdpy, xgc, GCFunction, &xgcv);

	XSetForeground(xdpy, xgc, WhitePixel(xdpy, DefaultScreen(xdpy)));

	XDrawString(xdpy, xwin, xgc, x, y, s, strlen(s));
	XFlush(xdpy);

	XGetGCValues(xdpy, xgc, GCFunction, &xgcv);
	xgcv.function = prevfunction;
	XChangeGC(xdpy, xgc, GCFunction, &xgcv);
}