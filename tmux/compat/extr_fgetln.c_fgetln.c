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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BUFSIZ ; 
 int EINVAL ; 
 int EOF ; 
 char* calloc (int,size_t) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 char* reallocarray (char*,int,size_t) ; 

char *
fgetln(FILE *fp, size_t *len)
{
	static char *buf = NULL;
	static size_t bufsz = 0;
	size_t r = 0;
	char *p;
	int c, e;

	if (!fp || !len) {
		errno = EINVAL;
		return NULL;
	}
	if (!buf) {
		if (!(buf = calloc(1, BUFSIZ)))
			return NULL;
		bufsz = BUFSIZ;
	}
	while ((c = getc(fp)) != EOF) {
		buf[r++] = c;
		if (r == bufsz) {
			if (!(p = reallocarray(buf, 2, bufsz))) {
				e = errno;
				free(buf);
				errno = e;
				buf = NULL, bufsz = 0;
				return NULL;
			}
			buf = p, bufsz = 2 * bufsz;
		}
		if (c == '\n')
			break;
	}
	return (*len = r) ? buf : NULL;
}