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
typedef  int /*<<< orphan*/  fz_halftone ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_bitmap ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_new_bitmap_from_pixmap_band (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

fz_bitmap *fz_new_bitmap_from_pixmap(fz_context *ctx, fz_pixmap *pix, fz_halftone *ht)
{
	return fz_new_bitmap_from_pixmap_band(ctx, pix, ht, 0);
}