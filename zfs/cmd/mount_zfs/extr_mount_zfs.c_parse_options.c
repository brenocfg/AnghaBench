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
 int ENOMEM ; 
 int /*<<< orphan*/  MNT_LINE_MAX ; 
 unsigned long MS_REMOUNT ; 
 unsigned long ZS_ZFSUTIL ; 
 int /*<<< orphan*/  free (char*) ; 
 int parse_option (char*,unsigned long*,unsigned long*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_options(char *mntopts, unsigned long *mntflags, unsigned long *zfsflags,
    int sloppy, char *badopt, char *mtabopt)
{
	int error = 0, quote = 0, flag = 0, count = 0;
	char *ptr, *opt, *opts;

	opts = strdup(mntopts);
	if (opts == NULL)
		return (ENOMEM);

	*mntflags = 0;
	opt = NULL;

	/*
	 * Scan through all mount options which must be comma delimited.
	 * We must be careful to notice regions which are double quoted
	 * and skip commas in these regions.  Each option is then checked
	 * to determine if it is a known option.
	 */
	for (ptr = opts; ptr && !flag; ptr++) {
		if (opt == NULL)
			opt = ptr;

		if (*ptr == '"')
			quote = !quote;

		if (quote)
			continue;

		if (*ptr == '\0')
			flag = 1;

		if ((*ptr == ',') || (*ptr == '\0')) {
			*ptr = '\0';

			error = parse_option(opt, mntflags, zfsflags, sloppy);
			if (error) {
				strcpy(badopt, opt);
				goto out;

			}

			if (!(*mntflags & MS_REMOUNT) &&
			    !(*zfsflags & ZS_ZFSUTIL)) {
				if (count > 0)
					strlcat(mtabopt, ",", MNT_LINE_MAX);

				strlcat(mtabopt, opt, MNT_LINE_MAX);
				count++;
			}

			opt = NULL;
		}
	}

out:
	free(opts);
	return (error);
}