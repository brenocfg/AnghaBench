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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* pdfapp_usage (int /*<<< orphan*/ *) ; 
 char* pdfapp_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void winhelp(pdfapp_t *app)
{
	fprintf(stderr, "%s\n%s", pdfapp_version(app), pdfapp_usage(app));
}