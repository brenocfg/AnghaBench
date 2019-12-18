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

size_t fz_deflate_bound(fz_context *ctx, size_t size)
{
	/* Copied from zlib to account for size_t vs uLong */
	return size + (size >> 12) + (size >> 14) + (size >> 25) + 13;
}