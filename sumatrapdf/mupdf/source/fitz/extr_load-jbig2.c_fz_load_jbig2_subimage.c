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
struct info {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * jbig2_read_image (int /*<<< orphan*/ *,struct info*,unsigned char const*,size_t,int /*<<< orphan*/ ,int) ; 

fz_pixmap *
fz_load_jbig2_subimage(fz_context *ctx, const unsigned char *buf, size_t len, int subimage)
{
	struct info jbig2 = { 0 };
	return jbig2_read_image(ctx, &jbig2, buf, len, 0, subimage);
}