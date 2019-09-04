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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 char* getenv (char*) ; 
 scalar_t__ rmdir (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ unlink (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static BOOL
printercache_unlink_blob(char *printer)
{
	char *path;
	char *home;

	if (printer == NULL)
		return False;

	home = getenv("HOME");
	if (home == NULL)
		return False;

	path = (char *) xmalloc(strlen(home) + sizeof("/.rdesktop/rdpdr/") + strlen(printer) +
				sizeof("/AutoPrinterCacheData") + 1);

	sprintf(path, "%s/.rdesktop/rdpdr/%s/AutoPrinterCacheData", home, printer);

	if (unlink(path) < 0)
	{
		xfree(path);
		return False;
	}

	sprintf(path, "%s/.rdesktop/rdpdr/%s", home, printer);

	if (rmdir(path) < 0)
	{
		xfree(path);
		return False;
	}

	xfree(path);
	return True;
}