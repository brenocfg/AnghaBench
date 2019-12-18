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
struct TYPE_4__ {char* search; int pageno; int pagecount; int /*<<< orphan*/  winw; scalar_t__ issearching; } ;

/* Variables and functions */
 int /*<<< orphan*/  WhitePixel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetForeground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fillrect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ gapp ; 
 char* message ; 
 scalar_t__ showingmessage ; 
 scalar_t__ showingpage ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  windrawstring (TYPE_1__*,int,int,char*) ; 
 int /*<<< orphan*/  windrawstringxor (TYPE_1__*,int,int,char*) ; 
 int /*<<< orphan*/  xdpy ; 
 int /*<<< orphan*/  xgc ; 
 int /*<<< orphan*/  xscr ; 

__attribute__((used)) static void winblitstatusbar(pdfapp_t *app)
{
	if (gapp.issearching)
	{
		char buf[sizeof(gapp.search) + 50];
		sprintf(buf, "Search: %s", gapp.search);
		XSetForeground(xdpy, xgc, WhitePixel(xdpy, xscr));
		fillrect(0, 0, gapp.winw, 30);
		windrawstring(&gapp, 10, 20, buf);
	}
	else if (showingmessage)
	{
		XSetForeground(xdpy, xgc, WhitePixel(xdpy, xscr));
		fillrect(0, 0, gapp.winw, 30);
		windrawstring(&gapp, 10, 20, message);
	}
	else if (showingpage)
	{
		char buf[42];
		snprintf(buf, sizeof buf, "Page %d/%d", gapp.pageno, gapp.pagecount);
		windrawstringxor(&gapp, 10, 20, buf);
	}
}