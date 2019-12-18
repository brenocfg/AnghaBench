#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct io_data {size_t size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  info_ptr; int /*<<< orphan*/  png_ptr; } ;
typedef  TYPE_1__* PNGWriteInfoRef ;
typedef  int /*<<< orphan*/ * MMBitmapRef ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_TRANSFORM_IDENTITY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* createPNGWriteInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroyPNGWriteInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  png_append_data ; 
 int /*<<< orphan*/  png_set_write_fn (int /*<<< orphan*/ ,struct io_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_write_png (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint8_t *createPNGData(MMBitmapRef bitmap, size_t *len)
{
	PNGWriteInfoRef info = NULL;
	struct io_data data = {NULL, 0, 0};

	assert(bitmap != NULL);
	assert(len != NULL);

	if ((info = createPNGWriteInfo(bitmap)) == NULL) return NULL;

	png_set_write_fn(info->png_ptr, &data, &png_append_data, NULL);
	png_write_png(info->png_ptr, info->info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	destroyPNGWriteInfo(info);

	*len = data.size;
	return data.buffer;
}