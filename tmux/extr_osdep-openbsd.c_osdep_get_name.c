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
typedef  size_t u_int ;
struct stat {scalar_t__ st_rdev; } ;
struct kinfo_proc {int /*<<< orphan*/  p_comm; scalar_t__ p_tdev; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int CTL_KERN ; 
 scalar_t__ ENOMEM ; 
 int KERN_PROC ; 
 int KERN_PROC_PGRP ; 
 struct kinfo_proc* cmp_procs (struct kinfo_proc*,struct kinfo_proc*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct kinfo_proc*) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 struct kinfo_proc* realloc (struct kinfo_proc*,size_t) ; 
 int stat (char*,struct stat*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int sysctl (int*,int /*<<< orphan*/ ,struct kinfo_proc*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tcgetpgrp (int) ; 

char *
osdep_get_name(int fd, char *tty)
{
	int		 mib[6] = { CTL_KERN, KERN_PROC, KERN_PROC_PGRP, 0,
				    sizeof(struct kinfo_proc), 0 };
	struct stat	 sb;
	size_t		 len;
	struct kinfo_proc *buf, *newbuf, *bestp;
	u_int		 i;
	char		*name;

	buf = NULL;

	if (stat(tty, &sb) == -1)
		return (NULL);
	if ((mib[3] = tcgetpgrp(fd)) == -1)
		return (NULL);

retry:
	if (sysctl(mib, nitems(mib), NULL, &len, NULL, 0) == -1)
		goto error;
	len = (len * 5) / 4;

	if ((newbuf = realloc(buf, len)) == NULL)
		goto error;
	buf = newbuf;

	mib[5] = (int)(len / sizeof(struct kinfo_proc));
	if (sysctl(mib, nitems(mib), buf, &len, NULL, 0) == -1) {
		if (errno == ENOMEM)
			goto retry;
		goto error;
	}

	bestp = NULL;
	for (i = 0; i < len / sizeof (struct kinfo_proc); i++) {
		if ((dev_t)buf[i].p_tdev != sb.st_rdev)
			continue;
		if (bestp == NULL)
			bestp = &buf[i];
		else
			bestp = cmp_procs(&buf[i], bestp);
	}

	name = NULL;
	if (bestp != NULL)
		name = strdup(bestp->p_comm);

	free(buf);
	return (name);

error:
	free(buf);
	return (NULL);
}