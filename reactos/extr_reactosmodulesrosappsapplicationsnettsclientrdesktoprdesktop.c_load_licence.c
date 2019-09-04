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
typedef  unsigned char uint8 ;
struct stat {int st_size; } ;
struct TYPE_3__ {char* hostname; } ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* getenv (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

int
load_licence(RDPCLIENT * This, unsigned char **data)
{
	char *home, *path;
	struct stat st;
	int fd, length;

	home = getenv("HOME");
	if (home == NULL)
		return -1;

	path = (char *) xmalloc(strlen(home) + strlen(This->hostname) + sizeof("/.rdesktop/licence."));
	sprintf(path, "%s/.rdesktop/licence.%s", home, This->hostname);

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return -1;

	if (fstat(fd, &st))
	{
		close(fd);
		return -1;
	}

	*data = (uint8 *) xmalloc(st.st_size);
	length = read(fd, *data, st.st_size);
	close(fd);
	xfree(path);
	return length;
}