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
struct info {unsigned char has_transparency; unsigned char transparent; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const unsigned char *
gif_read_gce(fz_context *ctx, struct info *info, const unsigned char *p, const unsigned char *end)
{
	if (end - p < 8)
		fz_throw(ctx, FZ_ERROR_GENERIC, "premature end in graphic control extension in gif image");
	if (p[2] != 0x04)
		fz_throw(ctx, FZ_ERROR_GENERIC, "out of range graphic control extension block size in gif image");

	info->has_transparency = p[3] & 0x1;
	if (info->has_transparency)
		info->transparent = p[6];

	return p + 8;
}