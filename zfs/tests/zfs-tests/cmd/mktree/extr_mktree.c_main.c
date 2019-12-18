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

/* Variables and functions */
 scalar_t__ atoi (int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int mktree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ndir ; 
 scalar_t__ nfile ; 
 scalar_t__ nlevel ; 
 int /*<<< orphan*/ * optarg ; 
 int /*<<< orphan*/ * pbasedir ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	int c, ret;

	while ((c = getopt(argc, argv, "b:l:d:f:")) != -1) {
		switch (c) {
		case 'b':
			pbasedir = optarg;
			break;
		case 'l':
			nlevel = atoi(optarg);
			break;
		case 'd':
			ndir = atoi(optarg);
			break;
		case 'f':
			nfile = atoi(optarg);
			break;
		case '?':
			usage(argv[0]);
		}
	}
	if (nlevel < 0 || ndir < 0 || nfile < 0 || pbasedir == NULL) {
		usage(argv[0]);
	}

	ret = mktree(pbasedir, 1);

	return (ret);
}