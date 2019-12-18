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
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_load_jbig2_subimage (int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

fz_pixmap *
fz_load_jbig2(fz_context *ctx, const unsigned char *buf, size_t len)
{
	return fz_load_jbig2_subimage(ctx, buf, len, 0);
}