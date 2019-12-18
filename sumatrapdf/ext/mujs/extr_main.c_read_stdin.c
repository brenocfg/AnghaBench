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
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static char *read_stdin(void)
{
	int n = 0;
	int t = 512;
	char *s = NULL;

	for (;;) {
		char *ss = realloc(s, t);
		if (!ss) {
			free(s);
			fprintf(stderr, "cannot allocate storage for stdin contents\n");
			return NULL;
		}
		s = ss;
		n += fread(s + n, 1, t - n - 1, stdin);
		if (n < t - 1)
			break;
		t *= 2;
	}

	if (ferror(stdin)) {
		free(s);
		fprintf(stderr, "error reading stdin\n");
		return NULL;
	}

	s[n] = 0;
	return s;
}