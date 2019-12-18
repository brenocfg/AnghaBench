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
struct info {int gct_entries; int /*<<< orphan*/  gct; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static const unsigned char *
gif_read_gct(fz_context *ctx, struct info *info, const unsigned char *p, const unsigned char *end)
{
	if (end - p < info->gct_entries * 3)
		fz_throw(ctx, FZ_ERROR_GENERIC, "premature end in global color table in gif image");

	info->gct = fz_malloc(ctx, info->gct_entries * 3);
	memmove(info->gct, p, info->gct_entries * 3);

	return p + info->gct_entries * 3;
}