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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

void
fz_format_output_path(fz_context *ctx, char *path, size_t size, const char *fmt, int page)
{
	const char *s, *p;
	char num[40];
	int i, n;
	int z = 0;

	for (i = 0; page; page /= 10)
		num[i++] = '0' + page % 10;
	num[i] = 0;

	s = p = strchr(fmt, '%');
	if (p)
	{
		++p;
		while (*p >= '0' && *p <= '9')
			z = z * 10 + (*p++ - '0');
	}
	if (p && *p == 'd')
	{
		++p;
	}
	else
	{
		s = p = strrchr(fmt, '.');
		if (!p)
			s = p = fmt + strlen(fmt);
	}

	if (z < 1)
		z = 1;
	while (i < z && i < (int)sizeof num)
		num[i++] = '0';
	n = s - fmt;
	if (n + i + strlen(p) >= size)
		fz_throw(ctx, FZ_ERROR_GENERIC, "path name buffer overflow");
	memcpy(path, fmt, n);
	while (i > 0)
		path[n++] = num[--i];
	fz_strlcpy(path + n, p, size - n);
}