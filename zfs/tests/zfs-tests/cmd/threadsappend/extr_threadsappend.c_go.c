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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  outfd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void *
go(void *data)
{
	int ret, i = 0, n = *(int *)data;
	char buf[8192] = {0};
	(void) memset(buf, n, sizeof (buf));

	for (i = 0; i < 80; i++) {
		ret = write(outfd, buf, sizeof (buf));
		if (ret != sizeof (buf))
			perror("write");
	}
	return (NULL);
}