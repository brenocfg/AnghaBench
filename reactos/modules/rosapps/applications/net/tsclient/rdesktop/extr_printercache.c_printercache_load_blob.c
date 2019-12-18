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
struct stat {int st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* getenv (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

int
printercache_load_blob(char *printer_name, uint8 ** data)
{
	char *home, *path;
	struct stat st;
	int fd, length;

	if (printer_name == NULL)
		return 0;

	*data = NULL;

	home = getenv("HOME");
	if (home == NULL)
		return 0;

	path = (char *) xmalloc(strlen(home) + sizeof("/.rdesktop/rdpdr/") + strlen(printer_name) +
				sizeof("/AutoPrinterCacheData") + 1);
	sprintf(path, "%s/.rdesktop/rdpdr/%s/AutoPrinterCacheData", home, printer_name);

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		xfree(path);
		return 0;
	}

	if (fstat(fd, &st))
	{
		xfree(path);
		close(fd);
		return 0;
	}

	*data = (uint8 *) xmalloc(st.st_size);
	length = read(fd, *data, st.st_size);
	close(fd);
	xfree(path);
	return length;
}