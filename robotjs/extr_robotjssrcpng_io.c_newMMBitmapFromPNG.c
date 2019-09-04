#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_struct ;
typedef  int /*<<< orphan*/  png_info ;
typedef  int png_byte ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_2__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  TYPE_1__ MMRGBColor ;
typedef  int /*<<< orphan*/  MMPNGReadError ;
typedef  int /*<<< orphan*/ * MMBitmapRef ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ADD_PADDING (int) ; 
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_GRAY_ALPHA ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int /*<<< orphan*/  PNG_INFO_tRNS ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/ * createMMBitmap (int*,int,int,int,int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  kPNGAccessError ; 
 int /*<<< orphan*/  kPNGGenericError ; 
 int /*<<< orphan*/  kPNGInvalidHeaderError ; 
 int /*<<< orphan*/  kPNGReadError ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int png_get_bit_depth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_color_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_image_height (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_get_image_width (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_get_rowbytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ png_get_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_init_io (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_jmpbuf (int /*<<< orphan*/ *) ; 
 int* png_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_read_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_row (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_expand_gray_1_2_4_to_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_gray_to_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_palette_to_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_sig_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_set_strip_16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_strip_alpha (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_tRNS_to_alpha (int /*<<< orphan*/ *) ; 
 scalar_t__ png_sig_cmp (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

MMBitmapRef newMMBitmapFromPNG(const char *path, MMPNGReadError *err)
{
	FILE *fp;
	uint8_t header[8];
	png_struct *png_ptr = NULL;
	png_info *info_ptr = NULL;
	png_byte bit_depth, color_type;
	uint8_t *row, *bitmapData;
	uint8_t bytesPerPixel;
	png_uint_32 width, height, y;
	uint32_t bytewidth;

	if ((fp = fopen(path, "rb")) == NULL) {
		if (err != NULL) *err = kPNGAccessError;
		return NULL;
	}

	/* Initialize error code to generic value. */
	if (err != NULL) *err = kPNGGenericError;

	/* Validate the PNG. */
	if (fread(header, 1, sizeof header, fp) == 0) {
		if (err != NULL) *err = kPNGReadError;
		goto bail;
	} else if (png_sig_cmp(header, 0, sizeof(header)) != 0) {
		if (err != NULL) *err = kPNGInvalidHeaderError;
		goto bail;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) goto bail;

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) goto bail;

	/* Set up error handling. */
	if (setjmp(png_jmpbuf(png_ptr))) {
		goto bail;
	}

	png_init_io(png_ptr, fp);

	/* Skip past the header. */
	png_set_sig_bytes(png_ptr, sizeof header);

	png_read_info(png_ptr, info_ptr);

	/* Convert different image types to common type to be read. */
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);

	/* Convert color palettes to RGB. */
	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}

	/* Convert PNG to bit depth of 8. */
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	} else if (bit_depth == 16) {
		png_set_strip_16(png_ptr);
	}

	/* Convert transparency chunk to alpha channel. */
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))  {
		png_set_tRNS_to_alpha(png_ptr);
	}

	/* Convert gray images to RGB. */
	if (color_type == PNG_COLOR_TYPE_GRAY ||
	    color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(png_ptr);
	}

	/* Ignore alpha for now. */
	if (color_type & PNG_COLOR_MASK_ALPHA) {
		png_set_strip_alpha(png_ptr);
	}

	/* Get image attributes. */
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	bytesPerPixel = 3; /* All images decompress to this size. */
	bytewidth = ADD_PADDING(width * bytesPerPixel); /* Align width. */

	/* Decompress the PNG row by row. */
	bitmapData = calloc(1, bytewidth * height);
	row = png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));
	if (bitmapData == NULL || row == NULL) goto bail;
	for (y = 0; y < height; ++y) {
		png_uint_32 x;
		const uint32_t rowOffset = y * bytewidth;
		uint8_t *rowptr = row;
		png_read_row(png_ptr, (png_byte *)row, NULL);

		for (x = 0; x < width; ++x) {
			const uint32_t colOffset = x * bytesPerPixel;
			MMRGBColor *color = (MMRGBColor *)(bitmapData + rowOffset + colOffset);
			color->red = *rowptr++;
			color->green = *rowptr++;
			color->blue = *rowptr++;
		}
	}
	free(row);

	/* Finish reading. */
	png_read_end(png_ptr, NULL);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);

	return createMMBitmap(bitmapData, width, height,
	                      bytewidth, bytesPerPixel * 8, bytesPerPixel);

bail:
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	return NULL;
}