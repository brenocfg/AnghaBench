#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_6__ {scalar_t__ l2factor; int /*<<< orphan*/  rect; } ;
typedef  TYPE_1__ fz_image_key ;
struct TYPE_7__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_pixmap_imp ; 
 int /*<<< orphan*/ * fz_find_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_image_store_type ; 
 int /*<<< orphan*/  update_ctm_for_subarea (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_pixmap *
fz_find_image_tile(fz_context *ctx, fz_image *image, fz_image_key *key, fz_matrix *ctm)
{
	fz_pixmap *tile;
	do
	{
		tile = fz_find_item(ctx, fz_drop_pixmap_imp, key, &fz_image_store_type);
		if (tile)
		{
			update_ctm_for_subarea(ctm, &key->rect, image->w, image->h);
			return tile;
		}
		key->l2factor--;
	}
	while (key->l2factor >= 0);
	return NULL;
}