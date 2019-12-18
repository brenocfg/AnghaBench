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
struct info {unsigned char* palette; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
png_read_plte(fz_context *ctx, struct info *info, const unsigned char *p, unsigned int size)
{
	int n = size / 3;
	int i;

	if (n > 256)
	{
		fz_warn(ctx, "too many samples in palette");
		n = 256;
	}

	for (i = 0; i < n; i++)
	{
		info->palette[i * 4] = p[i * 3];
		info->palette[i * 4 + 1] = p[i * 3 + 1];
		info->palette[i * 4 + 2] = p[i * 3 + 2];
	}

	/* Fill in any missing palette entries */
	for (; i < 256; i++)
	{
		info->palette[i * 4] = 0;
		info->palette[i * 4 + 1] = 0;
		info->palette[i * 4 + 2] = 0;
	}
}