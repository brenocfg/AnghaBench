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
struct TYPE_4__ {float resolution; float imgw; scalar_t__ winw; } ;
typedef  TYPE_1__ pdfapp_t ;

/* Variables and functions */
 float MAXRES ; 
 float MINRES ; 
 int /*<<< orphan*/  pdfapp_showpage (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pdfapp_autozoom_horizontal(pdfapp_t *app)
{
	app->resolution *= (float) app->winw / app->imgw;
	if (app->resolution > MAXRES)
		app->resolution = MAXRES;
	else if (app->resolution < MINRES)
		app->resolution = MINRES;
	pdfapp_showpage(app, 0, 1, 1, 0, 0);
}