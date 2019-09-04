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
struct TYPE_5__ {size_t row_count; int /*<<< orphan*/  info_ptr; int /*<<< orphan*/  png_ptr; struct TYPE_5__** row_pointers; scalar_t__ free_row_pointers; } ;
typedef  TYPE_1__* PNGWriteInfoRef ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  png_destroy_write_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_free (int /*<<< orphan*/ ,TYPE_1__**) ; 

__attribute__((used)) static void destroyPNGWriteInfo(PNGWriteInfoRef info)
{
	assert(info != NULL);
	if (info->row_pointers != NULL) {
		if (info->free_row_pointers) {
			size_t y;
			for (y = 0; y < info->row_count; ++y) {
				free(info->row_pointers[y]);
			}
		}
		png_free(info->png_ptr, info->row_pointers);
	}

	png_destroy_write_struct(&(info->png_ptr), &(info->info_ptr));
	free(info);
}