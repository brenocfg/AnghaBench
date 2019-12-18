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
struct io_data {int size; int allocedSize; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  png_struct ;
typedef  int png_size_t ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct io_data* png_get_io_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

void png_append_data(png_struct *png_ptr,
                     png_byte *new_data,
                     png_size_t length)
{
	struct io_data *data = png_get_io_ptr(png_ptr);
	data->size += length;

	/* Allocate or grow buffer. */
	if (data->buffer == NULL) {
		data->allocedSize = data->size;
		data->buffer = png_malloc(png_ptr, data->allocedSize);
		assert(data->buffer != NULL);
	} else if (data->allocedSize < data->size) {
		do {
			/* Double size each time to avoid calls to realloc. */
			data->allocedSize <<= 1;
		} while (data->allocedSize < data->size);

		data->buffer = realloc(data->buffer, data->allocedSize);
	}

	/* Copy new bytes to end of buffer. */
	memcpy(data->buffer + data->size - length, new_data, length);
}