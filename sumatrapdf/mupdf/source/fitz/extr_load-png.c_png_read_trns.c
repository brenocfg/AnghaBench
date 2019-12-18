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
struct info {int transparency; unsigned char* palette; int n; unsigned char* trns; int depth; scalar_t__ indexed; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
png_read_trns(fz_context *ctx, struct info *info, const unsigned char *p, unsigned int size)
{
	unsigned int i;

	info->transparency = 1;

	if (info->indexed)
	{
		if (size > 256)
		{
			fz_warn(ctx, "too many samples in transparency table");
			size = 256;
		}
		for (i = 0; i < size; i++)
			info->palette[i * 4 + 3] = p[i];
		/* Fill in any missing entries */
		for (; i < 256; i++)
			info->palette[i * 4 + 3] = 255;
	}
	else
	{
		if (size != info->n * 2)
			fz_throw(ctx, FZ_ERROR_GENERIC, "tRNS chunk is the wrong size");
		for (i = 0; i < info->n; i++)
			info->trns[i] = (p[i * 2] << 8 | p[i * 2 + 1]) & ((1 << info->depth) - 1);
	}
}