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
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ errno ; 
 int mkdir (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static BOOL
printercache_mkdir(char *base, char *printer)
{
	char *path;

	path = (char *) xmalloc(strlen(base) + sizeof("/.rdesktop/rdpdr/") + strlen(printer) + 1);

	sprintf(path, "%s/.rdesktop", base);
	if ((mkdir(path, 0700) == -1) && errno != EEXIST)
	{
		perror(path);
		xfree(path);
		return False;
	}

	strcat(path, "/rdpdr");
	if ((mkdir(path, 0700) == -1) && errno != EEXIST)
	{
		perror(path);
		xfree(path);
		return False;
	}

	strcat(path, "/");
	strcat(path, printer);
	if ((mkdir(path, 0700) == -1) && errno != EEXIST)
	{
		perror(path);
		xfree(path);
		return False;
	}

	xfree(path);
	return True;
}