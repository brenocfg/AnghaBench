#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  key_storable; } ;
typedef  TYPE_1__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_keep_key_storable_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_image *
fz_keep_image_store_key(fz_context *ctx, fz_image *image)
{
	return fz_keep_key_storable_key(ctx, &image->key_storable);
}