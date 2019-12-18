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
typedef  int /*<<< orphan*/  zed_strings_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 int zed_strings_count (int /*<<< orphan*/ *) ; 
 char* zed_strings_first (int /*<<< orphan*/ *) ; 
 char* zed_strings_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char **
_zed_exec_create_env(zed_strings_t *zsp)
{
	int num_ptrs;
	int buflen;
	char *buf;
	char **pp;
	char *p;
	const char *q;
	int i;
	int len;

	num_ptrs = zed_strings_count(zsp) + 1;
	buflen = num_ptrs * sizeof (char *);
	for (q = zed_strings_first(zsp); q; q = zed_strings_next(zsp))
		buflen += strlen(q) + 1;

	buf = calloc(1, buflen);
	if (!buf)
		return (NULL);

	pp = (char **)buf;
	p = buf + (num_ptrs * sizeof (char *));
	i = 0;
	for (q = zed_strings_first(zsp); q; q = zed_strings_next(zsp)) {
		pp[i] = p;
		len = strlen(q) + 1;
		memcpy(p, q, len);
		p += len;
		i++;
	}
	pp[i] = NULL;
	assert(buf + buflen == p);
	return ((char **)buf);
}