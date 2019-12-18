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
struct TYPE_5__ {int /*<<< orphan*/  docpath; } ;
typedef  TYPE_1__ pdfapp_t ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  fz_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdfapp_close (TYPE_1__*) ; 
 int /*<<< orphan*/  pdfapp_open (TYPE_1__*,char*,int) ; 

void pdfapp_reloadfile(pdfapp_t *app)
{
	char filename[PATH_MAX];
	fz_strlcpy(filename, app->docpath, PATH_MAX);
	pdfapp_close(app);
	pdfapp_open(app, filename, 1);
}