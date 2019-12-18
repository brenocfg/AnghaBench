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
struct TYPE_4__ {int /*<<< orphan*/  docpath; } ;
typedef  TYPE_1__ pdfapp_t ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  fz_cleanname (char*) ; 
 int /*<<< orphan*/  fz_dirname (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  winopenuri (TYPE_1__*,char*) ; 

__attribute__((used)) static void pdfapp_gotouri(pdfapp_t *app, char *uri)
{
	char buf[PATH_MAX];

	/* Relative file:// URI, make it absolute! */
	if (!strncmp(uri, "file://", 7) && uri[7] != '/')
	{
		char buf_base[PATH_MAX];
		char buf_cwd[PATH_MAX];
		fz_dirname(buf_base, app->docpath, sizeof buf_base);
		getcwd(buf_cwd, sizeof buf_cwd);
		fz_snprintf(buf, sizeof buf, "file://%s/%s/%s", buf_cwd, buf_base, uri+7);
		fz_cleanname(buf+7);
		uri = buf;
	}

	winopenuri(app, uri);
}