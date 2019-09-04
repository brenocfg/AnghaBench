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
struct TYPE_3__ {char* hostname; } ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 int mkdir (char*,int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int rename (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int write (int,unsigned char*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

void
save_licence(RDPCLIENT * This, unsigned char *data, int length)
{
	char *home, *path, *tmppath;
	int fd;

	home = getenv("HOME");
	if (home == NULL)
		return;

	path = (char *) xmalloc(strlen(home) + strlen(This->hostname) + sizeof("/.rdesktop/licence."));

	sprintf(path, "%s/.rdesktop", home);
	if ((mkdir(path, 0700) == -1) && errno != EEXIST)
	{
		perror(path);
		return;
	}

	/* write licence to licence.hostname.new, then atomically rename to licence.hostname */

	sprintf(path, "%s/.rdesktop/licence.%s", home, This->hostname);
	tmppath = (char *) xmalloc(strlen(path) + sizeof(".new"));
	strcpy(tmppath, path);
	strcat(tmppath, ".new");

	fd = open(tmppath, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror(tmppath);
		return;
	}

	if (write(fd, data, length) != length)
	{
		perror(tmppath);
		unlink(tmppath);
	}
	else if (rename(tmppath, path) == -1)
	{
		perror(path);
		unlink(tmppath);
	}

	close(fd);
	xfree(tmppath);
	xfree(path);
}