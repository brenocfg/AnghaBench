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
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_atoi (char const*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,char const*) ; 
 char* strchr (char const*,char) ; 
 char* strrchr (char const*,char) ; 

int
pdf_resolve_link(fz_context *ctx, pdf_document *doc, const char *uri, float *xp, float *yp)
{
	if (uri && uri[0] == '#')
	{
		int page = fz_atoi(uri + 1) - 1;
		if (xp || yp)
		{
			const char *x = strchr(uri, ',');
			const char *y = strrchr(uri, ',');
			if (x && y)
			{
				if (xp) *xp = fz_atoi(x + 1);
				if (yp) *yp = fz_atoi(y + 1);
			}
		}
		return page;
	}
	fz_warn(ctx, "unknown link uri '%s'", uri);
	return -1;
}