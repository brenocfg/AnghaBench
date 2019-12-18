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

__attribute__((used)) static const unsigned char *
pnm_read_number(fz_context *ctx, const unsigned char *p, const unsigned char *e, int *number)
{
	if (e - p < 1)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot parse number in pnm image");
	if (*p < '0' || *p > '9')
		fz_throw(ctx, FZ_ERROR_GENERIC, "expected numeric field in pnm image");

	while (p < e && *p >= '0' && *p <= '9')
	{
		if (number)
			*number = *number * 10 + *p - '0';
		p++;
	}

	return p;
}