#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int default_resolution; int resolution; } ;
typedef  TYPE_1__ pdfapp_t ;

/* Variables and functions */

void pdfapp_setresolution(pdfapp_t *app, int res)
{
	app->default_resolution = res;
	app->resolution = res;
}