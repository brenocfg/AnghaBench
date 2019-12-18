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
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_scale_pixmap_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,float,float,float,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_pixmap *
fz_scale_pixmap(fz_context *ctx, fz_pixmap *src, float x, float y, float w, float h, const fz_irect *clip)
{
	return fz_scale_pixmap_cached(ctx, src, x, y, w, h, clip, NULL, NULL);
}