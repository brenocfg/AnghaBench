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
struct info {int xres; int yres; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int getuint (unsigned char const*) ; 

__attribute__((used)) static void
png_read_phys(fz_context *ctx, struct info *info, const unsigned char *p, unsigned int size)
{
	if (size != 9)
		fz_throw(ctx, FZ_ERROR_GENERIC, "pHYs chunk is the wrong size");
	if (p[8] == 1)
	{
		info->xres = (getuint(p) * 254 + 5000) / 10000;
		info->yres = (getuint(p + 4) * 254 + 5000) / 10000;
	}
}