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
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static BOOL
printercache_rename_blob(char *printer, char *new_printer)
{
	char *printer_path;
	char *new_printer_path;
	int printer_maxlen;

	char *home;

	if (printer == NULL)
		return False;

	home = getenv("HOME");
	if (home == NULL)
		return False;

	printer_maxlen =
		(strlen(printer) >
		 strlen(new_printer) ? strlen(printer) : strlen(new_printer)) + strlen(home) +
		sizeof("/.rdesktop/rdpdr/") + 1;

	printer_path = (char *) xmalloc(printer_maxlen);
	new_printer_path = (char *) xmalloc(printer_maxlen);

	sprintf(printer_path, "%s/.rdesktop/rdpdr/%s", home, printer);
	sprintf(new_printer_path, "%s/.rdesktop/rdpdr/%s", home, new_printer);

	printf("%s,%s\n", printer_path, new_printer_path);
	if (rename(printer_path, new_printer_path) < 0)
	{
		xfree(printer_path);
		xfree(new_printer_path);
		return False;
	}

	xfree(printer_path);
	xfree(new_printer_path);
	return True;
}