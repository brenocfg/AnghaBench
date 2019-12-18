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
pnm_read_signature(fz_context *ctx, const unsigned char *p, const unsigned char *e, char *signature)
{
	if (e - p < 2)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot parse magic number in pnm image");
	if (p[0] != 'P' || p[1] < '1' || p[1] > '7')
		fz_throw(ctx, FZ_ERROR_GENERIC, "expected signature in pnm image");

	signature[0] = *p++;
	signature[1] = *p++;
	return p;
}