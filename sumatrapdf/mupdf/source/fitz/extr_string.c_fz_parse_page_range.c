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
 int fz_clampi (int,int,int) ; 
 int strtol (char const*,char**,int) ; 

const char *fz_parse_page_range(fz_context *ctx, const char *s, int *a, int *b, int n)
{
	if (!s || !s[0])
		return NULL;

	if (s[0] == ',')
		s += 1;

	if (s[0] == 'N')
	{
		*a = n;
		s += 1;
	}
	else
		*a = strtol(s, (char**)&s, 10);

	if (s[0] == '-')
	{
		if (s[1] == 'N')
		{
			*b = n;
			s += 2;
		}
		else
			*b = strtol(s+1, (char**)&s, 10);
	}
	else
		*b = *a;

	*a = fz_clampi(*a, 1, n);
	*b = fz_clampi(*b, 1, n);

	return s;
}