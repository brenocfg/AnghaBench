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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 char* getenv (char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printercache_mkdir (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
printercache_save_blob(char *printer_name, uint8 * data, uint32 length)
{
	char *home, *path;
	int fd;

	if (printer_name == NULL)
		return;

	home = getenv("HOME");
	if (home == NULL)
		return;

	if (!printercache_mkdir(home, printer_name))
		return;

	path = (char *) xmalloc(strlen(home) + sizeof("/.rdesktop/rdpdr/") + strlen(printer_name) +
				sizeof("/AutoPrinterCacheData") + 1);
	sprintf(path, "%s/.rdesktop/rdpdr/%s/AutoPrinterCacheData", home, printer_name);

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror(path);
		xfree(path);
		return;
	}

	if (write(fd, data, length) != length)
	{
		perror(path);
		unlink(path);
	}

	close(fd);
	xfree(path);
}