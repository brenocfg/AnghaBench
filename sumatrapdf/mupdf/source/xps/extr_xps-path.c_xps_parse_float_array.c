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
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float fz_strtof (char*,char**) ; 

__attribute__((used)) static char *
xps_parse_float_array(fz_context *ctx, xps_document *doc, char *s, int num, float *x)
{
	int k = 0;

	if (s == NULL || *s == 0)
		return NULL;

	while (*s)
	{
		while (*s == 0x0d || *s == '\t' || *s == ' ' || *s == 0x0a)
			s++;
		x[k] = fz_strtof(s, &s);
		while (*s == 0x0d || *s == '\t' || *s == ' ' || *s == 0x0a)
			s++;
		if (*s == ',')
			s++;
		if (++k == num)
			break;
	}
	return s;
}