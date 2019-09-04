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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  kGlobChars ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,int) ; 

int
MakeArgv(char *line, int *cargc, const char **cargv, int cargcmax, char *dbuf, size_t dbufsize, int *noglobargv, int readlineHacks)
{
	int c;
	int retval;
	char *dlim;
	char *dcp;
	char *scp;
	char *arg;

	*cargc = 0;
	scp = line;
	dlim = dbuf + dbufsize - 1;
	dcp = dbuf;

	for (*cargc = 0; *cargc < cargcmax; ) {
		/* Eat preceding junk. */
		for ( ; ; scp++) {
			c = *scp;
			if (c == '\0')
				goto done;
			if (isspace(c))
				continue;
			if ((c == ';') || (c == '\n')) {
				scp++;
				goto done;
			}
			break;
		}

		arg = dcp;
		cargv[*cargc] = arg;
		noglobargv[*cargc] = 0;
		(*cargc)++;

		/* Special hack so that "!cmd" is always split into "!" "cmd" */
		if ((*cargc == 1) && (*scp == '!')) {
			if (scp[1] == '!') {
				scp[1] = '\0';
			} else if ((scp[1] != '\0') && (!isspace((int) scp[1]))) {
				cargv[0] = "!";
				scp++;
				arg = dcp;
				cargv[*cargc] = arg;
				noglobargv[*cargc] = 0;
				(*cargc)++;
			}
		}

		/* Add characters to the new argument. */
		for ( ; ; ) {
			c = *scp;
			if (c == '\0')
				break;
			if (isspace(c))
				break;
			if ((c == ';') || (c == '\n')) {
				break;
			}

			scp++;

			if (c == '\'') {
				for ( ; ; ) {
					c = *scp++;
					if (c == '\0') {
						if (readlineHacks != 0)
							break;
						/* Syntax error */
						(void) fprintf(stderr, "Error: Unbalanced quotes.\n");
						return (-1);
					}
					if (c == '\'')
						break;

					/* Add char. */
					if (dcp >= dlim)
						goto toolong;
					*dcp++ = c;

					if (strchr(kGlobChars, c) != NULL) {
						/* User quoted glob characters,
						 * so mark this argument for
						 * noglob.
						 */
						noglobargv[*cargc - 1] = 1;
					}
				}
			} else if (c == '"') {
				for ( ; ; ) {
					c = *scp++;
					if (c == '\0') {
						if (readlineHacks != 0)
							break;
						/* Syntax error */
						(void) fprintf(stderr, "Error: Unbalanced quotes.\n");
						return (-1);
					}
					if (c == '"')
						break;

					/* Add char. */
					if (dcp >= dlim)
						goto toolong;
					*dcp++ = c;

					if (strchr(kGlobChars, c) != NULL) {
						/* User quoted glob characters,
						 * so mark this argument for
						 * noglob.
						 */
						noglobargv[*cargc - 1] = 1;
					}
				}
			} else
#if defined(WIN32) || defined(_WINDOWS)
				if (c == '|') {
#else
				if (c == '\\') {
#endif
				/* Add next character, verbatim. */
				c = *scp++;
				if (c == '\0')
					break;

				/* Add char. */
				if (dcp >= dlim)
					goto toolong;
				*dcp++ = c;
			} else {
				/* Add char. */
				if (dcp >= dlim)
					goto toolong;
				*dcp++ = c;
			}
		}

		*dcp++ = '\0';
	}

	(void) fprintf(stderr, "Error: Argument list too long.\n");
	*cargc = 0;
	cargv[*cargc] = NULL;
	return (-1);

done:
	retval = (int) (scp - line);
	cargv[*cargc] = NULL;
	return (retval);

toolong:
	(void) fprintf(stderr, "Error: Line too long.\n");
	*cargc = 0;
	cargv[*cargc] = NULL;
	return (-1);
}