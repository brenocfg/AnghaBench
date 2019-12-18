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
struct info {int dummy; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 unsigned char const* gif_read_subblocks (int /*<<< orphan*/ *,struct info*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const unsigned char*
gif_read_pte(fz_context *ctx, struct info *info, const unsigned char *p, const unsigned char *end)
{
	if (end - p < 15)
		fz_throw(ctx, FZ_ERROR_GENERIC, "premature end in plain text extension in gif image");
	if (p[2] != 0x0c)
		fz_throw(ctx, FZ_ERROR_GENERIC, "out of range plain text extension block size in gif image");
	return gif_read_subblocks(ctx, info, p + 15, end, NULL);
}