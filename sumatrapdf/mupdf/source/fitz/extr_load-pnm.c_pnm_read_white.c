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
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ iseol (unsigned char const) ; 
 scalar_t__ iswhite (unsigned char const) ; 
 scalar_t__ iswhiteeol (unsigned char const) ; 

__attribute__((used)) static const unsigned char *
pnm_read_white(fz_context *ctx, const unsigned char *p, const unsigned char *e, int single_line)
{
	if (e - p < 1)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot parse whitespace in pnm image");

	if (single_line)
	{
		if (!iswhiteeol(*p) && *p != '#')
			fz_throw(ctx, FZ_ERROR_GENERIC, "expected whitespace/comment in pnm image");
		while (p < e && iswhite(*p))
			p++;

		if (p < e && *p == '#')
			while (p < e && !iseol(*p))
				p++;
		if (p < e && iseol(*p))
			p++;
	}
	else
	{
		if (!iswhiteeol(*p) && *p != '#')
			fz_throw(ctx, FZ_ERROR_GENERIC, "expected whitespace in pnm image");
		while (p < e && iswhiteeol(*p))
			p++;

		while (p < e && *p == '#')
		{
			while (p < e && !iseol(*p))
				p++;

			if (p < e && iseol(*p))
				p++;

			while (p < e && iswhiteeol(*p))
				p++;

			if (p < e && iseol(*p))
				p++;
		}
	}

	return p;
}