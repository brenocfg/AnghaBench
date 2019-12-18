#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pagecount; int pageno; int histlen; int* hist; scalar_t__ issearching; } ;
typedef  TYPE_1__ pdfapp_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  pdfapp_showpage (TYPE_1__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winrepaint (TYPE_1__*) ; 

void pdfapp_gotopage(pdfapp_t *app, int number)
{
	app->issearching = 0;
	winrepaint(app);

	if (number < 1)
		number = 1;
	if (number > app->pagecount)
		number = app->pagecount;

	if (number == app->pageno)
		return;

	if (app->histlen + 1 == 256)
	{
		memmove(app->hist, app->hist + 1, sizeof(int) * 255);
		app->histlen --;
	}
	app->hist[app->histlen++] = app->pageno;
	app->pageno = number;
	pdfapp_showpage(app, 1, 1, 1, 0, 0);
}