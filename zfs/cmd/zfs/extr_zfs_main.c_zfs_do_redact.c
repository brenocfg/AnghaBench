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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
#define  E2BIG 134 
#define  EALREADY 133 
#define  EEXIST 132 
#define  EINVAL 131 
#define  ENAMETOOLONG 130 
#define  ENOENT 129 
#define  ENOTSUP 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 int lzc_redact (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_do_redact(int argc, char **argv)
{
	char *snap = NULL;
	char *bookname = NULL;
	char **rsnaps = NULL;
	int numrsnaps = 0;
	argv++;
	argc--;
	if (argc < 3) {
		(void) fprintf(stderr, gettext("too few arguments\n"));
		usage(B_FALSE);
	}

	snap = argv[0];
	bookname = argv[1];
	rsnaps = argv + 2;
	numrsnaps = argc - 2;

	nvlist_t *rsnapnv = fnvlist_alloc();

	for (int i = 0; i < numrsnaps; i++) {
		fnvlist_add_boolean(rsnapnv, rsnaps[i]);
	}

	int err = lzc_redact(snap, bookname, rsnapnv);
	fnvlist_free(rsnapnv);

	switch (err) {
	case 0:
		break;
	case ENOENT:
		(void) fprintf(stderr,
		    gettext("provided snapshot %s does not exist\n"), snap);
		break;
	case EEXIST:
		(void) fprintf(stderr, gettext("specified redaction bookmark "
		    "(%s) provided already exists\n"), bookname);
		break;
	case ENAMETOOLONG:
		(void) fprintf(stderr, gettext("provided bookmark name cannot "
		    "be used, final name would be too long\n"));
		break;
	case E2BIG:
		(void) fprintf(stderr, gettext("too many redaction snapshots "
		    "specified\n"));
		break;
	case EINVAL:
		(void) fprintf(stderr, gettext("redaction snapshot must be "
		    "descendent of snapshot being redacted\n"));
		break;
	case EALREADY:
		(void) fprintf(stderr, gettext("attempted to redact redacted "
		    "dataset or with respect to redacted dataset\n"));
		break;
	case ENOTSUP:
		(void) fprintf(stderr, gettext("redaction bookmarks feature "
		    "not enabled\n"));
		break;
	default:
		(void) fprintf(stderr, gettext("internal error: %s\n"),
		    strerror(errno));
	}

	return (err);
}