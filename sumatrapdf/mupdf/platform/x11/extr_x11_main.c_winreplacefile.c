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
typedef  int /*<<< orphan*/  pdfapp_t ;

/* Variables and functions */
 int /*<<< orphan*/  pdfapp_warn (int /*<<< orphan*/ *,char*) ; 
 int rename (char*,char*) ; 

void winreplacefile(pdfapp_t *app, char *source, char *target)
{
	if (rename(source, target) == -1)
		pdfapp_warn(app, "unable to rename file");
}