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
struct timeval {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (char*,int,...) ; 
 int /*<<< orphan*/  O_CREAT ; 
 int PATH_MAX ; 
 int close (int) ; 
 int errno ; 
 int files ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 int nth ; 
 int open (char*,int /*<<< orphan*/ ,int) ; 
 char* path ; 
 int post_hook (char*) ; 
 size_t snprintf (char*,size_t,char*,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 double timeval_sub_seconds (struct timeval*,struct timeval*) ; 
 int unlink (char*) ; 

__attribute__((used)) static int
create_files(void)
{
	int i, rc;
	char *file = NULL;
	struct timeval start, stop;
	double seconds;
	size_t fsize;

	fsize = PATH_MAX;
	file = malloc(fsize);
	if (file == NULL) {
		rc = ENOMEM;
		ERROR("Error %d: malloc(%d) bytes for file name\n", rc,
		    PATH_MAX);
		goto out;
	}

	(void) gettimeofday(&start, NULL);

	for (i = 1; i <= files; i++) {
		if (snprintf(file, fsize, "%s/file-%d", path, i) >= fsize) {
			rc = EINVAL;
			ERROR("Error %d: path too long\n", rc);
			goto out;
		}

		if (nth && ((i % nth) == 0))
			fprintf(stdout, "create: %s\n", file);

		rc = unlink(file);
		if ((rc == -1) && (errno != ENOENT)) {
			ERROR("Error %d: unlink(%s)\n", errno, file);
			rc = errno;
			goto out;
		}

		rc = open(file, O_CREAT, 0644);
		if (rc == -1) {
			ERROR("Error %d: open(%s, O_CREATE, 0644)\n",
			    errno, file);
			rc = errno;
			goto out;
		}

		rc = close(rc);
		if (rc == -1) {
			ERROR("Error %d: close(%d)\n", errno, rc);
			rc = errno;
			goto out;
		}
	}

	(void) gettimeofday(&stop, NULL);
	seconds = timeval_sub_seconds(&stop, &start);
	fprintf(stdout, "create:   %f seconds %f creates/second\n",
	    seconds, files / seconds);

	rc = post_hook("post");
out:
	if (file)
		free(file);

	return (rc);
}