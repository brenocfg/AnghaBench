#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t png_uint_32 ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_12__ {size_t const width; int height; int bytesPerPixel; size_t bytewidth; int /*<<< orphan*/ * imageBuffer; } ;
struct TYPE_11__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_10__ {int row_count; int free_row_pointers; int /*<<< orphan*/ ** row_pointers; int /*<<< orphan*/ * info_ptr; int /*<<< orphan*/ * png_ptr; } ;
typedef  TYPE_1__* PNGWriteInfoRef ;
typedef  int /*<<< orphan*/  PNGWriteInfo ;
typedef  TYPE_2__ MMRGBColor ;
typedef  TYPE_3__* MMBitmapRef ;

/* Variables and functions */
 size_t ADD_PADDING (size_t const) ; 
 TYPE_2__* MMRGBColorRefAtPoint (TYPE_3__*,size_t,size_t) ; 
 scalar_t__ MMRGB_IS_BGR ; 
 int /*<<< orphan*/  PNG_COLOR_TYPE_RGB ; 
 int /*<<< orphan*/  PNG_COMPRESSION_TYPE_DEFAULT ; 
 int /*<<< orphan*/  PNG_FILTER_TYPE_DEFAULT ; 
 int /*<<< orphan*/  PNG_INTERLACE_NONE ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_write_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_destroy_write_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  png_jmpbuf (int /*<<< orphan*/ *) ; 
 void* png_malloc (int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  png_set_IHDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_bgr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_rows (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PNGWriteInfoRef createPNGWriteInfo(MMBitmapRef bitmap)
{
	PNGWriteInfoRef info = malloc(sizeof(PNGWriteInfo));
	png_uint_32 y;

	if (info == NULL) return NULL;
	info->png_ptr = NULL;
	info->info_ptr = NULL;
	info->row_pointers = NULL;

	assert(bitmap != NULL);

	/* Initialize the write struct. */
	info->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
	                                        NULL, NULL, NULL);
	if (info->png_ptr == NULL) goto bail;

	/* Set up error handling. */
	if (setjmp(png_jmpbuf(info->png_ptr))) {
		png_destroy_write_struct(&(info->png_ptr), &(info->info_ptr));
		goto bail;
	}

	/* Initialize the info struct. */
	info->info_ptr = png_create_info_struct(info->png_ptr);
	if (info->info_ptr == NULL) {
		png_destroy_write_struct(&(info->png_ptr), NULL);
		goto bail;
	}

	/* Set image attributes. */
	png_set_IHDR(info->png_ptr,
	             info->info_ptr,
	             (png_uint_32)bitmap->width,
	             (png_uint_32)bitmap->height,
	             8,
	             PNG_COLOR_TYPE_RGB,
	             PNG_INTERLACE_NONE,
	             PNG_COMPRESSION_TYPE_DEFAULT,
	             PNG_FILTER_TYPE_DEFAULT);

	info->row_count = bitmap->height;
	info->row_pointers = png_malloc(info->png_ptr,
	                                sizeof(png_byte *) * info->row_count);

	if (bitmap->bytesPerPixel == 3) {
		/* No alpha channel; image data can be copied directly. */
		for (y = 0; y < info->row_count; ++y) {
			info->row_pointers[y] = bitmap->imageBuffer + (bitmap->bytewidth * y);
		}
		info->free_row_pointers = false;

		/* Convert BGR to RGB if necessary. */
		if (MMRGB_IS_BGR) {
			png_set_bgr(info->png_ptr);
		}
	} else {
		/* Ignore alpha channel; copy image data row by row. */
		const size_t bytesPerPixel = 3;
		const size_t bytewidth = ADD_PADDING(bitmap->width * bytesPerPixel);

		for (y = 0; y < info->row_count; ++y) {
			png_uint_32 x;
			png_byte *row_ptr = png_malloc(info->png_ptr, bytewidth);
			info->row_pointers[y] = row_ptr;
			for (x = 0; x < bitmap->width; ++x) {
				MMRGBColor *color = MMRGBColorRefAtPoint(bitmap, x, y);
				row_ptr[0] = color->red;
				row_ptr[1] = color->green;
				row_ptr[2] = color->blue;

				row_ptr += bytesPerPixel;
			}
		}
		info->free_row_pointers = true;
	}

	png_set_rows(info->png_ptr, info->info_ptr, info->row_pointers);
	return info;

bail:
	if (info != NULL) free(info);
	return NULL;
}